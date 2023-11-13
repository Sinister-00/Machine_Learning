#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <iostream>
#include <stdint.h>

class data
{
    std::vector<uint8_t> *feature_vector; // Feature vector without a class label at the end.
    uint8_t label;                        // Class label
    int enum_label;                       // Enumerated label (A->1, B->2, ...)
    double distance;                      // Distance from test data point

public:
    data();
    ~data();
    // Setter methods
    void set_feature_vector(std::vector<uint8_t> *); // Set the feature vector
    void append_feature_vector(uint8_t);             // Append a value to the feature vector
    void set_label(uint8_t);                         // Set the class label
    void set_enum_label(int);                        // Set the enumerated label
    void set_distance(double);                       // Set the distance from test data point

    // Getter methods
    int get_feature_vector_size();              // Get the size of the feature vector
    uint8_t get_label();                        // Get the class label
    uint8_t get_enum_label();                   // Get the enumerated label
    std::vector<uint8_t> *get_feature_vector(); // Get the feature vector
    double get_distance();                      // Get the distance from test data point
};

#endif // __DATA_H__
