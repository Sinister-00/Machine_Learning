#include "../include/kmeans.hpp"

kmeans::kmeans(int k)
{
    number_of_clusters = k;
    clusters = new std::vector<cluster_t *>; // initialize the clusters vector
    used_indices = new std::unordered_set<int>;
}
void kmeans::initialize_clusters()
{
    for (int i = 0; i < number_of_clusters; i++)
    {
        int idx = rand() % (train_data->size());
        while (used_indices->find(idx) != used_indices->end())
        {
            idx = rand() % (train_data->size());
        }
        clusters->push_back(new cluster_t(train_data->at(idx)));
        used_indices->insert(idx);
    }
}
void kmeans::initialize_clusters_for_each_class()
{
    std::unordered_set<int> classes_used;
    for (int i = 0; i < train_data->size(); i++)
    {
        if (classes_used.find(train_data->at(i)->get_label()) == classes_used.end())
        {
            clusters->push_back(new cluster_t(train_data->at(i)));
            classes_used.insert(train_data->at(i)->get_label());
            used_indices->insert(i);
        }
    }
}
void kmeans::train()
{
    while (used_indices->size() != train_data->size())
    {
        int idx = (rand() % (train_data->size()));
        // int idx = 0; // to speed up the process  
        while (used_indices->find(idx) != used_indices->end())
        {
            idx = (rand() % (train_data->size()));
            // idx++;
        }
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = -1;
        for (int i = 0; i < clusters->size(); i++)
        {
            double curr_dist = euclidean_distance(clusters->at(i)->centroid, train_data->at(idx));
            if (curr_dist < min_dist)
            {
                min_dist = curr_dist;
                best_cluster = i;
            }
        }
        clusters->at(best_cluster)->add_to_cluster(train_data->at(idx));
        used_indices->insert(idx);
    }
}
double kmeans::euclidean_distance(std::vector<double> *centeroid, data *d)
{
    double dist = 0.0;
    for (int i = 0; i < centeroid->size(); i++)
    {
        dist += pow(centeroid->at(i) - d->get_feature_vector()->at(i), 2);
    }
    return sqrt(dist);
}
double kmeans::validate_performance()
{
    double correct = 0.0;
    for (auto d : *valid_data)
    {
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = -1;
        for (int i = 0; i < clusters->size(); i++)
        {
            double curr_dist = euclidean_distance(clusters->at(i)->centroid, d);
            if (curr_dist < min_dist)
            {
                min_dist = curr_dist;
                best_cluster = i;
            }
        }
        if (clusters->at(best_cluster)->most_freq_class == d->get_label())
        {
            correct++;
        }
    }
    return 100.0 * (correct / (double)valid_data->size());
}
double kmeans::test_performance()
{
    double correct = 0.0;
    for (auto d : *test_data)
    {
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = -1;
        for (int i = 0; i < clusters->size(); i++)
        {
            double curr_dist = euclidean_distance(clusters->at(i)->centroid, d);
            if (curr_dist < min_dist)
            {
                min_dist = curr_dist;
                best_cluster = i;
            }
        }
        if (clusters->at(best_cluster)->most_freq_class == d->get_label())
        {
            correct++;
        }
    }
    return 100.0 * (correct / (double)test_data->size());
}

int main()
{
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../Dataset/train-images-idx3-ubyte");
    dh->read_label_vector("../Dataset/train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();
    double performance = 0, best_performance = 0.0;
    int best_k = 1;
    for (int k = dh->get_num_classes(); k < dh->get_train_data()->size(); k++)
    {
        kmeans *km = new kmeans(k);
        km->set_test_data(dh->get_test_data());
        km->set_valid_data(dh->get_validation_data());
        km->set_train_data(dh->get_train_data());
        km->initialize_clusters_for_each_class();
        km->train();
        performance = km->validate_performance();
        std::cout << "Current performance: " << performance << "%"
                  << " at k = " << k << "\n";
        if (performance > best_performance)
        {
            best_performance = performance;
            best_k = k;
        }
    }
    kmeans *km = new kmeans(best_k);
    km->set_test_data(dh->get_test_data());
    km->set_valid_data(dh->get_validation_data());
    km->set_train_data(dh->get_train_data());
    km->initialize_clusters_for_each_class();
    km->test_performance();
    performance = km->test_performance();
    std::cout << "Best performance: " << performance << "%"
              << " at k = " << best_k << "\n";
}
