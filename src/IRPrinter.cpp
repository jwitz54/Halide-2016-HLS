#include <iostream>
#include <sstream>

#include "IRPrinter.h"
#include "IROperator.h"
#include "Module.h"

namespace Halide {

using std::ostream;
using std::vector;
using std::string;
using std::ostringstream;

ostream &operator<<(ostream &out, const Type &type) {
    switch (type.code()) {
    case Type::Int:
        out << "int";
        break;
    case Type::UInt:
        out << "uint";
        break;
    case Type::Float:
        out << "float";
        break;
    case Type::Handle:
        out << "handle";
        break;
    case Type::TestInt:
        out << "test_int";
        break;
    }
    out << type.bits();
    if (type.lanes() > 1) out << 'x' << type.lanes();
    return out;
}

ostream &operator<<(ostream &stream, const Expr &ir) {
    if (!ir.defined()) {
        stream << "(undefined)";
    } else {
        Internal::IRPrinter p(stream);
        p.print(ir);
    }
    return stream;
}

ostream &operator <<(ostream &stream, const Internal::BufferPtr &buffer) {
    return stream << "buffer " << buffer.name() << " = {...}\n";
}

ostream &operator<<(ostream &stream, const Module &m) {
    stream << "Target = " << m.target().to_string() << "\n";
    for (const auto &b : m.buffers()) {
        stream << b << "\n";
    }
    for (const auto &f : m.functions()) {
        stream << f << "\n";
    }
    return stream;
}

ostream &operator<<(ostream &out, const DeviceAPI &api) {
    switch (api) {
    case DeviceAPI::Host:
    case DeviceAPI::None:
        break;
    case DeviceAPI::Default_GPU:
        out << "<Default_GPU>";
        break;
    case DeviceAPI::CUDA:
        out << "<CUDA>";
        break;
    case DeviceAPI::OpenCL:
        out << "<OpenCL>";
        break;
    case DeviceAPI::OpenGLCompute:
        out << "<OpenGLCompute>";
        break;
    case DeviceAPI::GLSL:
        out << "<GLSL>";
        break;
    case DeviceAPI::Renderscript:
        out << "<Renderscript>";
        break;
    case DeviceAPI::Metal:
        out << "<Metal>";
        break;
    case DeviceAPI::Hexagon:
        out << "<Hexagon>";
        break;
    }
    return out;
}

namespace Internal {

void IRPrinter::test() {
    Type i32 = Int(32);
    Type f32 = Float(32);
    Expr x = Variable::make(Int(32), "x");
    Expr y = Variable::make(Int(32), "y");
    ostringstream expr_source;
    expr_source << (x + 3) * (y / 2 + 17);
    internal_assert(expr_source.str() == "((x + 3)*((y/2) + 17))");

    Stmt store = Store::make("buf", (x * 17) / (x - 3), y - 1,  Parameter());
    Stmt for_loop = For::make("x", -2, y + 2, ForType::Parallel, DeviceAPI::Host, store);
    vector<Expr> args(1); args[0] = x % 3;
    Expr call = Call::make(i32, "buf", args, Call::Extern);
    Stmt store2 = Store::make("out", call + 1, x, Parameter());
    Stmt for_loop2 = For::make("x", 0, y, ForType::Vectorized , DeviceAPI::Host, store2);

    Stmt producer = ProducerConsumer::make("buf", true, for_loop);
    Stmt consumer = ProducerConsumer::make("buf", false, for_loop2);
    Stmt pipeline = Block::make(producer, consumer);

    Stmt assertion = AssertStmt::make(y >= 3, Call::make(Int(32), "halide_error_param_too_small_i64",
                                                         {string("y"), y, 3}, Call::Extern));
    Stmt block = Block::make(assertion, pipeline);
    Stmt let_stmt = LetStmt::make("y", 17, block);
    Stmt allocate = Allocate::make("buf", f32, {1023}, const_true(), let_stmt);

    ostringstream source;
    source << allocate;
    std::string correct_source = \
        "allocate buf[float32 * 1023]\n"
        "let y = 17\n"
        "assert((y >= 3), halide_error_param_too_small_i64(\"y\", y, 3))\n"
        "produce buf {\n"
        "  parallel (x, -2, (y + 2)) {\n"
        "    buf[(y - 1)] = ((x*17)/(x - 3))\n"
        "  }\n"
        "}\n"
        "vectorized (x, 0, y) {\n"
        "  out[x] = (buf((x % 3)) + 1)\n"
        "}\n";

    if (source.str() != correct_source) {
        internal_error << "Correct output:\n" << correct_source
                       << "Actual output:\n" << source.str();

    }
    std::cout << "IRPrinter test passed\n";
}

ostream &operator<<(ostream &out, const ForType &type) {
    switch (type) {
    case ForType::Serial:
        out << "for";
        break;
    case ForType::Parallel:
        out << "parallel";
        break;
    case ForType::Unrolled:
        out << "unrolled";
        break;
    case ForType::Vectorized:
        out << "vectorized";
        break;
    }
    return out;
}

ostream &operator<<(ostream &stream, const Stmt &ir) {
    if (!ir.defined()) {
        stream << "(undefined)\n";
    } else {
        Internal::IRPrinter p(stream);
        p.print(ir);
    }
    return stream;
}


ostream &operator <<(ostream &stream, const LoweredFunc &function) {
    stream << function.linkage << " func " << function.name << " (";
    for (size_t i = 0; i < function.args.size(); i++) {
        stream << function.args[i].name;
        if (i + 1 < function.args.size()) {
            stream << ", ";
        }
    }
    stream << ") {\n";
    stream << function.body;
    stream << "}\n\n";
    return stream;
}


std::ostream &operator<<(std::ostream &out, const LoweredFunc::LinkageType &type) {
    switch (type) {
    case LoweredFunc::External:
        out << "external";
        break;
    case LoweredFunc::Internal:
        out << "internal";
        break;
    }
    return out;
}

IRPrinter::IRPrinter(ostream &s) : stream(s), indent(0) {
    s.setf(std::ios::fixed, std::ios::floatfield);
}

void IRPrinter::print(Expr ir) {
    ir.accept(this);
}

void IRPrinter::print(Stmt ir) {
    ir.accept(this);
}


void IRPrinter::do_indent() {
    for (int i = 0; i < indent; i++) stream << ' ';
}

void IRPrinter::visit(const IntImm *op) {
    if (op->type == Int(32)) {
        stream << op->value;
    } else {
        stream << "(" << op->type << ")" << op->value;
    }
}

void IRPrinter::visit(const UIntImm *op) {
    stream << "(" << op->type << ")" << op->value;
}

void IRPrinter::visit(const FloatImm *op) {
  switch (op->type.bits()) {
    case 64:
        stream << op->value;
        break;
    case 32:
        stream << op->value << 'f';
        break;
    case 16:
        stream << op->value << 'h';
        break;
    default:
        internal_error << "Bad bit-width for float: " << op->type << "\n";
    }
}

void IRPrinter::visit(const StringImm *op) {
    stream << '"';
    for (size_t i = 0; i < op->value.size(); i++) {
        unsigned char c = op->value[i];
        if (c >= ' ' && c <= '~' && c != '\\' && c != '"') {
            stream << c;
        } else {
            stream << '\\';
            switch (c) {
            case '"':
                stream << '"';
                break;
            case '\\':
                stream << '\\';
                break;
            case '\t':
                stream << 't';
                break;
            case '\r':
                stream << 'r';
                break;
            case '\n':
                stream << 'n';
                break;
            default:
                string hex_digits = "0123456789ABCDEF";
                stream << 'x' << hex_digits[c >> 4] << hex_digits[c & 0xf];
            }
        }
    }
    stream << '"';
}

void IRPrinter::visit(const TestIntImm *op) {
    stream << "(" << op->type << ")" << op->value;
}

void IRPrinter::visit(const Cast *op) {
    stream << op->type << '(';
    print(op->value);
    stream << ')';
}

void IRPrinter::visit(const Variable *op) {
    // omit the type
    // stream << op->name << "." << op->type;
    stream << op->name;
}

void IRPrinter::visit(const Add *op) {
    stream << '(';
    print(op->a);
    stream << " + ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const Sub *op) {
    stream << '(';
    print(op->a);
    stream << " - ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const Mul *op) {
    stream << '(';
    print(op->a);
    stream << "*";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const Div *op) {
    stream << '(';
    print(op->a);
    stream << "/";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const Mod *op) {
    stream << '(';
    print(op->a);
    stream << " % ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const Min *op) {
    stream << "min(";
    print(op->a);
    stream << ", ";
    print(op->b);
    stream << ")";
}

void IRPrinter::visit(const Max *op) {
    stream << "max(";
    print(op->a);
    stream << ", ";
    print(op->b);
    stream << ")";
}

void IRPrinter::visit(const EQ *op) {
    stream << '(';
    print(op->a);
    stream << " == ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const NE *op) {
    stream << '(';
    print(op->a);
    stream << " != ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const LT *op) {
    stream << '(';
    print(op->a);
    stream << " < ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const LE *op) {
    stream << '(';
    print(op->a);
    stream << " <= ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const GT *op) {
    stream << '(';
    print(op->a);
    stream << " > ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const GE *op) {
    stream << '(';
    print(op->a);
    stream << " >= ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const And *op) {
    stream << '(';
    print(op->a);
    stream << " && ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const Or *op) {
    stream << '(';
    print(op->a);
    stream << " || ";
    print(op->b);
    stream << ')';
}

void IRPrinter::visit(const Not *op) {
    stream << '!';
    print(op->a);
}

void IRPrinter::visit(const Select *op) {
    stream << "select(";
    print(op->condition);
    stream << ", ";
    print(op->true_value);
    stream << ", ";
    print(op->false_value);
    stream << ")";
}

void IRPrinter::visit(const Load *op) {
    stream << op->name << "[";
    print(op->index);
    stream << "]";
}

void IRPrinter::visit(const Ramp *op) {
    stream << "ramp(";
    print(op->base);
    stream << ", ";
    print(op->stride);
    stream << ", " << op->lanes << ")";
}

void IRPrinter::visit(const Broadcast *op) {
    stream << "x" << op->lanes << "(";
    print(op->value);
    stream << ")";
}

void IRPrinter::visit(const Call *op) {
    // Special-case some intrinsics for readability
    if (op->is_intrinsic(Call::extract_buffer_host)) {
        print(op->args[0]);
        stream << ".host";
        return;
    } else if (op->is_intrinsic(Call::extract_buffer_min)) {
        print(op->args[0]);
        stream << ".min[" << op->args[1] << "]";
        return;
    } else if (op->is_intrinsic(Call::extract_buffer_max)) {
        print(op->args[0]);
        stream << ".max[" << op->args[1] << "]";
        return;
    }

    // TODO: Print indication of C vs C++?
    stream << op->name << "(";
    for (size_t i = 0; i < op->args.size(); i++) {
        print(op->args[i]);
        if (i < op->args.size() - 1) {
            stream << ", ";
        }
    }
    stream << ")";
}

void IRPrinter::visit(const Let *op) {
    stream << "(let " << op->name << " = ";
    print(op->value);
    stream << " in ";
    print(op->body);
    stream << ")";
}

void IRPrinter::visit(const LetStmt *op) {
    do_indent();
    stream << "let " << op->name << " = ";
    print(op->value);
    stream << '\n';

    print(op->body);
}

void IRPrinter::visit(const AssertStmt *op) {
    do_indent();
    stream << "assert(";
    print(op->condition);
    stream << ", ";
    print(op->message);
    stream << ")\n";
}

void IRPrinter::visit(const ProducerConsumer *op) {
    if (op->is_producer) {
        do_indent();
        stream << "produce " << op->name << " {\n";
        indent += 2;
        print(op->body);
        indent -= 2;
        do_indent();
        stream << "}\n";
    } else {
        print(op->body);
    }

}

void IRPrinter::visit(const For *op) {

    do_indent();
    stream << op->for_type << op->device_api << " (" << op->name << ", ";
    print(op->min);
    stream << ", ";
    print(op->extent);
    stream << ") {\n";

    indent += 2;
    print(op->body);
    indent -= 2;

    do_indent();
    stream << "}\n";
}

void IRPrinter::visit(const Store *op) {
    do_indent();
    stream << op->name << "[";
    print(op->index);
    stream << "] = ";
    print(op->value);
    stream << '\n';
}

void IRPrinter::visit(const Provide *op) {
    do_indent();
    stream << op->name << "(";
    for (size_t i = 0; i < op->args.size(); i++) {
        print(op->args[i]);
        if (i < op->args.size() - 1) stream << ", ";
    }
    stream << ") = ";
    if (op->values.size() > 1) {
        stream << "{";
    }
    for (size_t i = 0; i < op->values.size(); i++) {
        if (i > 0) {
            stream << ", ";
        }
        print(op->values[i]);
    }
    if (op->values.size() > 1) {
        stream << "}";
    }

    stream << '\n';
}

void IRPrinter::visit(const Allocate *op) {
    do_indent();
    stream << "allocate " << op->name << "[" << op->type;
    for (size_t i = 0; i < op->extents.size(); i++) {
        stream  << " * ";
        print(op->extents[i]);
    }
    stream << "]";
    if (!is_one(op->condition)) {
        stream << " if ";
        print(op->condition);
    }
    if (op->new_expr.defined()) {
        stream << "\n custom_new { " << op->new_expr << " }";
    }
    if (!op->free_function.empty()) {
        stream << "\n custom_delete { " << op->free_function << "(<args>); }";
    }
    stream << "\n";
    print(op->body);
}

void IRPrinter::visit(const Free *op) {
    do_indent();
    stream << "free " << op->name;
    stream << '\n';
}

void IRPrinter::visit(const Realize *op) {
    do_indent();
    stream << "realize " << op->name << "(";
    for (size_t i = 0; i < op->bounds.size(); i++) {
        stream << "[";
        print(op->bounds[i].min);
        stream << ", ";
        print(op->bounds[i].extent);
        stream << "]";
        if (i < op->bounds.size() - 1) stream << ", ";
    }
    stream << ")";
    if (!is_one(op->condition)) {
        stream << " if ";
        print(op->condition);
    }
    stream << " {\n";

    indent += 2;
    print(op->body);
    indent -= 2;

    do_indent();
    stream << "}\n";
}

void IRPrinter::visit(const Block *op) {
    print(op->first);
    if (op->rest.defined()) print(op->rest);
}

void IRPrinter::visit(const IfThenElse *op) {
    do_indent();
    while (1) {
        stream << "if (" << op->condition << ") {\n";
        indent += 2;
        print(op->then_case);
        indent -= 2;

        if (!op->else_case.defined()) {
            break;
        }

        if (const IfThenElse *nested_if = op->else_case.as<IfThenElse>()) {
            do_indent();
            stream << "} else ";
            op = nested_if;
        } else {
            do_indent();
            stream << "} else {\n";
            indent += 2;
            print(op->else_case);
            indent -= 2;
            break;
        }
    }

    do_indent();
    stream << "}\n";

}

void IRPrinter::visit(const Evaluate *op) {
    do_indent();
    print(op->value);
    stream << "\n";
}

}}
