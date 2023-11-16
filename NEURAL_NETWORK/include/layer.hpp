#ifndef __LAYER_HPP__
#define __LAYER_HPP__
#include "neuron.hpp"
#include <stdint.h>
#include <vector>

class Layer
{
public:
    int current_layer_size;
    std::vector<Neuron *> neurons;
    std::vector<double> layer_output;
    Layer(int, int);
    ~Layer();
    std::vector<double> get_layer_output();
    int get_size();
};
#endif // __LAYER_HPP__