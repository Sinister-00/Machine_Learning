#ifndef __KNN_H__
#define __KNN_H__
#include <vector>
#include <limits>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <map>
#include <iostream>
#include "data_handler.hpp"
#include <data.hpp>
#include "common.hpp"
class knn : public CommonData
{
    int k;
    std::vector<Data *> *neighbors; // keep track of the k nearest neighbors

public:
    knn(int);
    knn();
    ~knn();
    void find_k_nearest_neighbors(Data *d);
    void set_k(int); // set the value of k for kNN
    int prediction();
    double calculateDistance(Data *d1, Data *d2); // we will use Euclidean distance
    double validatePerformance();                 // pick the correct k value
    double testPerformance();                     // test the performance of the model on the test set
    void delete_neighbors();
};

#endif // __KNN_H__