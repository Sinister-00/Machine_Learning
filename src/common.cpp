#include "common.hpp"
void common_data::set_train_data(std::vector<data *> *v)
{
    train_data = v;
}
void common_data::set_test_data(std::vector<data *> *v)
{
    test_data = v;
}
void common_data::set_valid_data(std::vector<data *> *v)
{
    valid_data = v;
}