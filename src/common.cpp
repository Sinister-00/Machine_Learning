#include "common.hpp"
void CommonData::set_train_data(std::vector<Data *> *v)
{
    train_data = v;
}
void CommonData::set_test_data(std::vector<Data *> *v)
{
    test_data = v;
}
void CommonData::set_valid_data(std::vector<Data *> *v)
{
    valid_data = v;
}