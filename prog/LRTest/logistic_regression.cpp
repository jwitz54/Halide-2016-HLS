#include "Halide.h"
#include "fileio.hpp"
#include <stdlib.h>
#include <iostream>
#include <math.h>
//#include <ctime>
//#include "HalideBuffer.h"

#define NUM_FEATURES      1024
// #define NUM_SAMPLES       5000
// #define DATA_SET_SIZE     5120000
// #define NUM_TRAINING      4500

#define NUM_SAMPLES       2000
#define DATA_SET_SIZE     2048000

using namespace Halide;

// void array_to_image(uint8_t* in_ptr, uint8_t* out_ptr, const int M, const int N) {

//     Buffer<uint8_t> in(Buffer(UInt(8), N, M, 0, 0, in_ptr));
//     Buffer<uint8_t> out(Buffer(UInt(8), N, M, 0, 0, out_ptr));

//     Var x,y;
//     Func copy;
//     copy(x,y) = in(x,y);
//     copy.realize(out);
// }

int main(){
	// Output file that saves the test bench results
    std::ofstream outfile;
    //outfile.open("out.dat");
    outfile.open("out.dat", std::ofstream::out | std::ofstream::app);

    // Initialize options to default values
    std::string path_to_data(".");

    // Read data from files and insert into variables
    std::string str_points_filepath(
        path_to_data + std::string("/shuffledfeats.dat"));
    std::string str_labels_filepath(
        path_to_data + std::string("/shuffledlabels.dat"));

    const char* points_filepath = str_points_filepath.c_str();
    const char* labels_filepath = str_labels_filepath.c_str();

    // Model variables
    float data_points[DATA_SET_SIZE]; // Data points
    float labels[NUM_SAMPLES]; // Labels
    float parameter_vector[NUM_FEATURES]; // Model parameters

    // Read data from files and insert into variables
    if(readData(NUM_SAMPLES * NUM_FEATURES, points_filepath, data_points)
        != (NUM_SAMPLES * NUM_FEATURES))
            return EXIT_FAILURE;

    if(readData(NUM_SAMPLES, labels_filepath, labels)
        != NUM_SAMPLES)
            return EXIT_FAILURE;

	// Turn into usable Buffers
	Buffer<float> parameter_vector_im(NUM_FEATURES);
    for (int i = 0; i<NUM_FEATURES; i++){
        //parameter_vector_im(i) = parameter_vector[i];
        parameter_vector_im(i) = .5;
    }

	Buffer<float> data_vector_im(NUM_FEATURES, NUM_SAMPLES);
    for(int i=0; i<NUM_SAMPLES; i++){
        for(int j=0; j<NUM_FEATURES; j++) {
            data_vector_im(j,i) = data_points[j + i*NUM_FEATURES];
        }
    }
    Buffer<float> labels_im(NUM_SAMPLES);
    for(int i=0; i<NUM_SAMPLES; i++) {
        labels_im(i) = labels[i];
    }
            
    Var x("x");Var y("y"); 
    // Baseline, no scheduling
    // Define dot function (using 2 steps)
    Func dotVec("dot vector");
    dotVec(x,y) = parameter_vector_im(x) * data_vector_im(x,y); 

    Func dotSum("dot sum");
    RDom r(0, NUM_FEATURES);
    dotSum(y) += dotVec(r, y);// Sum function for FPGA

    // Define logistic regression function
    Func logisticRegression("logisticRegression");
    logisticRegression(y) = 1/(1 + exp(-dotSum(y)));

    // Adjust parameter 
    Func parameterUpdate("parameterUpdate");
    parameterUpdate(x, y) = (logisticRegression(y) - labels_im(y)) * data_vector_im(x, y); // 0 is temp

    // Set new parameter vector
    Func parameterOut("parameterOut");
    parameterOut(x) = parameter_vector_im(x);
    RDom r2(0, NUM_SAMPLES);
    parameterOut(x) += parameterUpdate(x, r2); 

    // Scheduling (CPU)
    //dotVec.parallel(y);
    //logisticRegression.parallel(y);
    //parameterUpdate.vectorize(x, 16);
    //parameterUpdate.parallel(y);

    // Time and realize (CPU)
    //double time;
    //clock_t start = std::clock();
    //time = (std::clock() - start) / (double) CLOCKS_PER_SEC; 
    //printf("Baseline: %f\n", time);
    parameterOut.compile_to_c("lr.cpp", {}, "parameterOut");
    parameterOut.compile_to_header("lr.h", {}, "parameterOut");

}
