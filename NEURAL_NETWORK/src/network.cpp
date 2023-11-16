#include "network.hpp"

Network::Network(std::vector<int> spec, int input_size, int classNum, double learning_rate)
{
    for (int i = 0; i < spec.size(); i++)
    {
        if (i == 0)
        {
            layers.push_back(new Layer(input_size, spec.at(i)));
        }
        else
        {
            layers.push_back(new Layer(spec.at(i - 1), spec.at(i)));
        }
    }
    layers.push_back(new Layer(layers.at(layers.size() - 1)->neurons.size(), classNum));
    this->learning_rate = learning_rate;
}

Network::~Network()
{
    for (int i = 0; i < layers.size(); i++)
    {
        delete layers.at(i);
    }
}

double Network::activate(std::vector<double> weights, std::vector<double> inputs)
{
    double activation = weights.back();
    for (int i = 0; i < inputs.size() - 1; i++)
    {
        activation += weights.at(i) * inputs.at(i);
    }
    return activation;
}

double Network::transfer(double activation)
{
    return 1.0 / (1.0 + exp(-activation));
}

double Network::transfer_derivative(double output)
{
    return output * (1.0 - output);
}

std::vector<double> Network::fprop(data *d)
{
    std::vector<double> inputs = *d->get_normalised_feature_vector();
    for (int i = 0; i < layers.size(); i++)
    {
        Layer *layer = layers.at(i);
        std::vector<double> new_inputs;
        for (Neuron *neuron : layer->neurons)
        {
            double activation = this->activate(neuron->weights, inputs);
            neuron->output = this->transfer(activation);
            new_inputs.push_back(neuron->output);
        }
        inputs = new_inputs;
    }

    return inputs; // output layer outputs
}

void Network::bprop(data *d)
{
    for (int i = layers.size() - 1; i >= 0; i++)
    {
        Layer *layer = layers.at(i);
        std::vector<double> errs;
        if (i != layers.size() - 1)
        {
            for (int j = 0; j < layer->neurons.size(); j++)
            {
                double error = 0.0;
                for (Neuron *neuron : layers.at(i + 1)->neurons) // error that contributes to the next layer
                {
                    error += (neuron->weights.at(j) * neuron->delta);
                }
                errs.push_back(error);
            }
        }
        else
        {
            for (int j = 0; j < layer->neurons.size(); j++)
            {
                Neuron *neuron = layer->neurons.at(j);
                errs.push_back((double)d->get_class_vector()->at(j) - neuron->output); // expected - actual
            }
        }
        for (int j = 0; j < layer->neurons.size(); j++)
        {
            Neuron *neuron = layer->neurons.at(j);
            neuron->delta = errs.at(j) * this->transfer_derivative(neuron->output); //    gradient /  derivative part of backprop
        }
    }
}

void Network::update_weights(data *d)
{
    std::vector<double> inputs = *d->get_normalised_feature_vector();
    for (int i = 0; i < layers.size(); i++)
    {
        if (i != 0)
        {
            for (Neuron *neuron : layers.at(i - 1)->neurons)
            {
                inputs.push_back(neuron->output);
            }
        }
        for (Neuron *neuron : layers.at(i)->neurons)
        {
            for (int j = 0; j < inputs.size(); j++)
            {
                neuron->weights.at(j) += this->learning_rate * neuron->delta * inputs.at(j);
            }
            neuron->weights.back() += this->learning_rate * neuron->delta;
        }
        inputs.clear();
    }
}

int Network::predict(data *d)
{
    std::vector<double> outputs = this->fprop(d);
    return std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));
}

void Network::train(int epochs)
{
    for (int i = 0; i < epochs; i++)
    {
        double sum_error = 0.0;
        for (data *d : *this->train_data)
        {
            std::vector<double> outputs = this->fprop(d);
            std::vector<int> expected = *d->get_class_vector();
            double temp_err = 0.0;
            for (int j = 0; j < expected.size(); j++)
            {
                temp_err += pow(expected.at(j) - outputs.at(j), 2);
            }
            sum_error += temp_err;
            bprop(d);
            update_weights(d);
        }
        std::cout << "epoch: " << i << " error: " << sum_error << std::endl;
    }
}

double Network::test()
{
    double correct = 0.0;
    double cnt = 0.0;
    for (data *d : *this->test_data)
    {
        cnt++;
        int prediction = this->predict(d);
        if (d->get_class_vector()->at(prediction) == 1)
        {
            correct++;
        }
    }
    test_performance = correct / cnt;
    return test_performance;
}

void Network::validate()
{
    double correct = 0.0;
    double cnt = 0.0;
    for (data *d : *this->valid_data)
    {
        cnt++;
        int prediction = this->predict(d);
        if (d->get_class_vector()->at(prediction) == 1)
        {
            correct++;
        }
    }
    std::cout << "validation performance: " << correct / cnt << std::endl;
}

int main()
{
    data_handler *dh = new data_handler();
#ifdef MLINX

    dh->read_feature_vector("Dataset/train-images-idx3-ubyte");
    dh->read_label_vector("Dataset/train-labels-idx1-ubyte");

#else
    dh->read_data_from_csv("../Dataset/iris.csv", ",");
#endif
    dh->split_data();
    std::vector<int> hidden_layers = {10};
    auto lambda = [&]()
    {
        Network *net = new Network(hidden_layers, dh->get_train_data()->at(0)->get_normalised_feature_vector()->size(), dh->get_num_classes(), 0.1);
        net->set_train_data(dh->get_train_data());
        net->set_test_data(dh->get_test_data());
        net->set_valid_data(dh->get_validation_data());
        net->train(17);
        net->validate();
        std::cout << "test performance: " << net->test() << std::endl;
    };
    lambda();
}