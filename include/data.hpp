#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <iostream>
#include <stdint.h>

class Data
{
    std::vector<uint8_t> *feature_vector; // Feature vector without a class label at the end.
    uint8_t label;                        // Class label
    int enum_label;                       // Enumerated label (A->1, B->2, ...)

public:
    // Setter methods
    void set_feature_vector(std::vector<uint8_t> *); // Set the feature vector
    void set_label(uint8_t);                         // Set the class label
    void set_enum_label(int);                        // Set the enumerated label

    // Getter methods
    int get_feature_vector_size();              // Get the size of the feature vector
    uint8_t get_label();                        // Get the class label
    uint8_t get_enum_label();                   // Get the enumerated label
    std::vector<uint8_t> *get_feature_vector(); // Get the feature vector
};

#endif // __DATA_H__
