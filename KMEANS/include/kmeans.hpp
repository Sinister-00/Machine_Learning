#ifndef __KMEANS_HPP__
#define __KMEANS_HPP__
#include "common.hpp"
#include <unordered_set>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <cmath>
#include <map>
#include "data_handler.hpp"

typedef struct cluster
{
    std::vector<double> *centroid;
    std::vector<data *> *cluster_points;
    std::map<int, int> class_counts;
    int most_freq_class;
    cluster(data *d)
    {
        centroid = new std::vector<double>;
        cluster_points = new std::vector<data *>;
        for (auto v : *(d->get_feature_vector()))
        {
            centroid->push_back(v); // initialize the centroid to the first data point
        }
        cluster_points->push_back(d);
        class_counts[d->get_label()] = 1; // initialize the class counts to the first data point
        most_freq_class = d->get_label();
    }
    void add_to_cluster(data *val)
    {
        int prevSize = cluster_points->size();
        cluster_points->push_back(val);
        for (int i = 0; i < centroid->size() - 1; i++)
        {
            double v = centroid->at(i);
            v *= prevSize;
            v += val->get_feature_vector()->at(i);
            v /= (double)cluster_points->size();
            centroid->at(i) = v;
        }
        if (class_counts.find(val->get_label()) == class_counts.end())
        {
            class_counts[val->get_label()] = 1;
        }
        else
        {
            class_counts[val->get_label()]++;
        }
    }
    void set_most_freq_class()
    {
        int best_class = -1;
        int freq = 0;
        for (auto it : class_counts)
        {
            if (it.second > freq)
            {
                freq = it.second;
                best_class = it.first;
            }
        }
        most_freq_class = best_class;
    }

} cluster_t;

class kmeans : common_data
{
    int number_of_clusters;
    std::vector<cluster_t *> *clusters;
    std::unordered_set<int> *used_indices;

public:
    kmeans(int);
    void initialize_clusters();
    void initialize_clusters_for_each_class();
    void train();
    double euclidean_distance(std::vector<double> *, data *);
    double validate_performance();
    double test_performance();
};

#endif // __KMEANS_HPP__