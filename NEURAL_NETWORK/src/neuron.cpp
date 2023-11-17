#include "neuron.hpp"
#include <random>

double generateRandomNumber(double min, double max)
{
    double random = ((double)rand()) / RAND_MAX;
    return min + random * (max - min);
}
Neuron::Neuron(int prevLayerSize, int currentLayerSize)
{
    initializeWeights(prevLayerSize);
}
void Neuron::initializeWeights(int prevLayerSize)
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0); // mean and standard deviation
    for (int i = 0; i < prevLayerSize + 1; i++)              // add aditional bias term to the weights
    {
        weights.push_back(generateRandomNumber(-1.0, 1.0));
    }
}