#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__
#include "data.hpp"
#include "layer.hpp"
#include "common.hpp"
#include "neuron.hpp"
#include <numeric>
#include "data_handler.hpp"
class Network : public CommonData
{
public:
    std::vector<Layer *> layers;
    double learning_rate;
    double test_performance;
    Network(std::vector<int> spec, int, int, double);
    ~Network();
    std::vector<double> fprop(Data *d);                        // vector of the doubles of last layer output
    double activate(std::vector<double>, std::vector<double>); // we pass in the weight vector of a neuron and the input vector of previous layer (dot product of the two)
    double transfer(double);                                   // sigmoid function (activation function)
    double transfer_derivative(double);                        // derivative of sigmoid function used for backpropagation
    void bprop(Data *d);                                       // backpropagation
    void update_weights(Data *d);                              // update weights
    int predict(Data *d);                                      // return the index of max value in the output array
    void train(int);                                           // number of iterations as int
    double test();
    void validate();
};

#endif //__NETWORK_HPP__