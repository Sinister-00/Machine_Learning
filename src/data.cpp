#include "data.hpp"

void Data::set_feature_vector(std::vector<uint8_t> *vect)
{
    feature_vector = vect;
}
void Data::set_feature_vector(std::vector<double> *vect)
{
    feature_vector_double = vect;
}
void Data::set_normalised_feature_vector(std::vector<double> *vect)
{
    normalised_feature_vector = vect;
}
void Data::append_feature_vector(uint8_t val)
{
    feature_vector->push_back(val);
}
void Data::append_feature_vector(double val)
{
    feature_vector_double->push_back(val);
}
void Data::append_normalised_feature_vector(double val)
{
    normalised_feature_vector->push_back(val);
}

void Data::set_class_vector(int val)
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
void Data::set_label(uint8_t val)
{
    label = val;
}
void Data::set_enum_label(uint8_t val)
{
    enum_label = val;
}

int Data::get_feature_vector_size()
{
    return feature_vector->size();
}
uint8_t Data::get_label()
{
    return label;
}
uint8_t Data::get_enum_label()
{
    return enum_label;
}

std::vector<uint8_t> *Data::get_feature_vector()
{
    return feature_vector;
}
std::vector<double> *Data::get_feature_vector_double()
{
    return feature_vector_double;
}
std::vector<double> *Data::get_normalised_feature_vector()
{
    return normalised_feature_vector;
}
std::vector<int> Data::get_class_vector()
{
    return *class_vector;
}
Data::Data()
{
    feature_vector = new std::vector<uint8_t>;
}
Data::~Data()
{
    delete feature_vector;
}

void Data::set_distance(double val)
{
    distance = val;
}

void Data::print_vector()
{
    for (int i = 0; i < get_feature_vector_size(); i++)
    {
        std::cout << (int)feature_vector->at(i) << " ";
    }
    std::cout << std::endl;
}

void Data::print_normalised_vector()
{
    int size = normalised_feature_vector->size();
    for (int i = 0; i <size; i++)
    {
        std::cout << normalised_feature_vector->at(i) << " ";
    }
    std::cout << std::endl;
}