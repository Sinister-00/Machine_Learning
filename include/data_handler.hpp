#ifndef __DATA_HANDLER_H__
#define __DATA_HANDLER_H__
#include <fstream>
#include <stdint.h> // for uint8_t
#include "data.hpp"
#include <vector> // dynamic array
#include <string>
#include <map>           // map a class label to the enum value
#include <unordered_set> // for track of indexes as we split the data

class data_handler
{
    // data arrays to store different sets
    std::vector<data *> *data_array;      // All data before splitting
    std::vector<data *> *train_data;      // Training data set
    std::vector<data *> *test_data;       // Testing data set
    std::vector<data *> *validation_data; // Validation data set

    int num_classes;                     // Number of unique classes in the data
    int feature_vector_size;             // Size of the feature vector
    std::map<uint8_t, int> class_map;    // Map class label to enum value
    std::map<std::string, int> classMap; //

    const double TRAIN_SET_PERCENTAGE = 0.75;
    const double TEST_SET_PERCENTAGE = 0.20;
    const double VALIDATION_SET_PERCENTAGE = 0.05;

public:
    // Constructor and destructor
    data_handler();  // Constructor
    ~data_handler(); // Destructor

    // Functions for reading and handling data
    void read_data_from_csv(std::string path, std::string delimiter); // Read data from csv file
    void read_feature_vector(std::string path);                       // Read feature vector from file
    void read_label_vector(std::string path);                         // Read label vector from file
    void split_data();                                                // Split data into train, test, and validation
    void count_classes();                                             // Count the number of unique classes

    void normalize_data(); // Normalize data

    // Utility function for little-endian conversion
    uint32_t convert_to_little_endian(const unsigned char *bytes); // Convert number to little endian

    // Getter functions for different data sets
    int get_num_classes();
    std::vector<data *> *get_train_data();
    std::vector<data *> *get_test_data();
    std::vector<data *> *get_validation_data();
};

#endif // __DATA_HANDLER_H__
