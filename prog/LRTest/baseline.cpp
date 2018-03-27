#include "fileio.hpp"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "cblas.h"
#include <time.h>

//#include <ctime>
//#include "HalideBuffer.h"

#define NUM_FEATURES      1024
// #define NUM_SAMPLES       5000
// #define DATA_SET_SIZE     5120000
// #define NUM_TRAINING      4500

#define NUM_SAMPLES       2000
#define DATA_SET_SIZE     2048000


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
    std::string path_to_data("/work/zhang/users/gaa54/Spam-Filter/data");

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

    for (int i = 0; i<NUM_FEATURES; i++){
        parameter_vector[i] = .5;
    }

    double time;
    clock_t start = clock();
    for (size_t i = 0; i < NUM_SAMPLES; i++){
        float dot = 0;
        for (size_t j = 0; j < NUM_FEATURES; j++) {
             dot += parameter_vector[j] * data_points[i * NUM_FEATURES + j];
        }

        float sigma = 1/(1 + exp(dot)); 
         
        for (int j = 0; j<NUM_FEATURES; j++){
            parameter_vector[j] = parameter_vector[j] + (sigma - labels[i]) * data_points[i * NUM_FEATURES + j];
        }

    }
    time = (clock() - start) / (double) CLOCKS_PER_SEC; 
    printf("Baseline: %f\n", time);
}
