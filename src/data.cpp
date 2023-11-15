#include "data.hpp"

void data::set_feature_vector(std::vector<uint8_t> *vect)
{
    feature_vector = vect;
}
void data::set_feature_vector(std::vector<double> *vect)
{
    feature_vector_double = vect;
}
void data::append_feature_vector(uint8_t val)
{
    feature_vector->push_back(val);
}
void data::append_feature_vector(double val)
{
    feature_vector_double->push_back(val);
}

void data::set_class_vector(int val)
{
    class_vector = new std::vector<int>();
    for (int i = 0; i < val; i++)
    {
        if (i == label)
        {
            class_vector->push_back(1);
        }
        else
        {
            class_vector->push_back(0);
        }
    }
}
void data::set_label(uint8_t val)
{
    label = val;
}
void data::set_enum_label(int val)
{
    enum_label = val;
}

int data::get_feature_vector_size()
{
    return feature_vector->size();
}
uint8_t data::get_label()
{
    return label;
}
uint8_t data::get_enum_label()
{
    return enum_label;
}

std::vector<uint8_t> *data::get_feature_vector()
{
    return feature_vector;
}
std::vector<double> *data::get_feature_vector_double()
{
    return feature_vector_double;
}
std::vector<int> *data::get_class_vector()
{
    return class_vector;
}
data::data()
{
    feature_vector = new std::vector<uint8_t>;
}
data::~data()
{
    delete feature_vector;
}

void data::set_distance(double val)
{
    distance = val;
}