//----------Building block of the neural network----------//

#ifndef __NEURON_HPP__
#define __NEURON_HPP__
#include <stdio.h>
#include <vector>
#include <cmath>
class Neuron
{
public:
    double output;
    double delta;
    std::vector<double> weights;
    Neuron(int, int);
    void initializeWeights(int);
};
#endif // __NEURON_HPP__