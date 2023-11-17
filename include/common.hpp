#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#include "data.hpp"
#include <vector>
class CommonData
{
protected:
    std::vector<Data *> *train_data;
    std::vector<Data *> *test_data;
    std::vector<Data *> *valid_data;

public:
    void set_train_data(std::vector<Data *> *v);
    void set_test_data(std::vector<Data *> *v);
    void set_valid_data(std::vector<Data *> *v);
};

#endif // __COMMON_HPP__