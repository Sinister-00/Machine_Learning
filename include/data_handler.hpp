#ifndef __DATA_HANDLER_H__
#define __DATA_HANDLER_H__
#include <fstream>
#include <stdint.h> // for uint8_t
#include "data.hpp"
#include <vector> // dynamic array
#include <string>
#include <algorithm> // Add this line to include the <algorithm> header
#include <random>    // Add this line to include the <random> header
#include <map>       // map a class label to the enum value
#include <math.h>
#include <unordered_set> // for track of indexes as we split the Data

class DataHandler
{
    // Data arrays to store different sets
    std::vector<Data *> *data_array;      // All Data before splitting
    std::vector<Data *> *train_data;      // Training Data set
    std::vector<Data *> *test_data;       // Testing Data set
    std::vector<Data *> *validation_data; // Validation Data set

    int num_classes;                     // Number of unique classes in the Data
    int feature_vector_size;             // Size of the feature vector
    std::map<uint8_t, int> class_map;    // Map class label to enum value
    std::map<std::string, int> classMap; //

    // Constants
    // USE THEM FOR KMEANS & KNN BECAUSE IT IS A SMALLER DATA SET
    // const double TRAIN_SET_PERCENTAGE = 0.75;
    // const double TEST_SET_PERCENTAGE = 0.20;
    // const double VALIDATION_SET_PERCENTAGE = 0.05;
    // End of constants

public:
    // Constants
    // USE THEM FOr NEURAL NETWORK BECAUSE IT IS A BIGGER DATA SET
    const double TRAIN_SET_PERCENTAGE = .1;
    const double TEST_SET_PERCENTAGE = .075;
    const double VALIDATION_SET_PERCENTAGE = 0.005;
    // End of constants

    // Constructor and destructor
    DataHandler();  // Constructor
    ~DataHandler(); // Destructor

    // Functions for reading and handling Data
    void read_data_from_csv(std::string, std::string); // Read Data from csv file
    void read_input_data(std::string);                 // Read input Data from file
    void read_feature_vector(std::string path);        // Read feature vector from file
    void read_label_vector(std::string path);          // Read label vector from file
    void read_label_data(std::string path);            // Read label Data from file
    void split_data();                                 // Split Data into train, test, and validation
    void count_classes();                              // Count the number of unique classes
    void normalize_data();                             // Normalize Data

    // Utility function for little-endian conversion
    uint32_t convert_to_little_endian(const unsigned char *bytes); // Convert number to little endian

    // Getter functions for different Data sets
    int get_num_classes();
    int get_feature_vector_size();
    int get_training_data_size();
    int get_testing_data_size();
    int get_validation_data_size();
    std::vector<Data *> *get_train_data();
    std::vector<Data *> *get_test_data();
    std::vector<Data *> *get_validation_data();
    std::map<uint8_t, int> get_class_map();
};

#endif // __DATA_HANDLER_H__
