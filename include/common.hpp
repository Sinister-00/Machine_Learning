#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#include "data.hpp"
#include <vector>
class common_data
{
protected:
    std::vector<data *> *train_data;
    std::vector<data *> *test_data;
    std::vector<data *> *valid_data;

public:
    void set_train_data(std::vector<data *> *v);
    void set_test_data(std::vector<data *> *v);
    void set_valid_data(std::vector<data *> *v);
};

#endif // __COMMON_HPP__