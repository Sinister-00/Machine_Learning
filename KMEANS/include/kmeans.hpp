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

typedef struct cluster // cluster struct
{
    std::vector<double> *centroid;       // centroid of the cluster
    std::vector<data *> *cluster_points; // data points in the cluster
    std::map<int, int> class_counts;     // class counts in the cluster (class, count)
    int most_freq_class;                 // most frequent class in the cluster
    cluster(data *d)                     // constructor for the cluster struct that takes a data point
    {
        centroid = new std::vector<double>;       // initialize the centroid vector
        cluster_points = new std::vector<data *>; // initialize the cluster points vector
        for (auto v : *(d->get_feature_vector())) // for each value in the data point's feature vector
        {
            centroid->push_back(v); // initialize the centroid to the first data point
        }
        cluster_points->push_back(d);     // push back the data point to the cluster points vector
        class_counts[d->get_label()] = 1; // initialize the class counts to the first data point
        most_freq_class = d->get_label();
    }
    void add_to_cluster(data *val) // add a data point to the cluster
    {
        int prevSize = cluster_points->size(); // get the previous size of the cluster
        cluster_points->push_back(val);        // push back the data point to the cluster points vector
        for (int i = 0; i < centroid->size() - 1; i++)
        {
            double v = centroid->at(i);
            v *= prevSize;
            v += val->get_feature_vector()->at(i);
            v /= (double)cluster_points->size();
            centroid->at(i) = v;
        }
        if (class_counts.find(val->get_label()) == class_counts.end()) // if the class is not in the class counts
        {
            class_counts[val->get_label()] = 1;
        }
        else
        {
            class_counts[val->get_label()]++;
        }
        set_most_freq_class(); // set the most frequent class in the cluster
    }
    void set_most_freq_class() // set the most frequent class in the cluster
    {
        int best_class = -1;         // -1 means no class is the best class
        int freq = 0;                // frequency of the best class
        for (auto it : class_counts) // for each class count
        {
            if (it.second > freq) // if the frequency is greater than the current frequency
            {
                freq = it.second;
                best_class = it.first;
            }
        }
        most_freq_class = best_class; // set the most frequent class to the best class
    }

} cluster_t; // cluster type

class kmeans : public common_data
{
    int number_of_clusters;
    std::vector<cluster_t *> *clusters;
    std::unordered_set<int> *used_indices;

public:
    kmeans(int);
    // ~kmeans();
    void initialize_clusters();
    void initialize_clusters_for_each_class();
    void train();
    double euclidean_distance(std::vector<double> *, data *);
    double manhattan_distance(std::vector<double> *, data *);
    double validate_performance();
    double test_performance();
    double calculate_wcss();
};

#endif // __KMEANS_HPP__