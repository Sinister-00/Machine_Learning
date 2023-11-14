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
        int idx = rand() % (train_data->size()); // rand value between 0 and train_data->size()
        while (used_indices->find(idx) != used_indices->end())
        {
            idx = rand() % (train_data->size()); // if the index is already used, get a new one
        }
        clusters->push_back(new cluster_t(train_data->at(idx))); // in clusters, add a new cluster with the centroid being the data point at idx
        used_indices->insert(idx);                               // add the index to the used indices
    }
}
void kmeans::initialize_clusters_for_each_class()
{
    std::unordered_set<int> classes_used;        // to keep track of the classes used
    for (int i = 0; i < train_data->size(); i++) // for each data point
    {
        if (classes_used.find(train_data->at(i)->get_label()) == classes_used.end()) // if the class is not used
        {
            clusters->push_back(new cluster_t(train_data->at(i))); // push back a new cluster with the centroid being the data point at i
            classes_used.insert(train_data->at(i)->get_label());   // add the class to the used classes (for the train data)
            used_indices->insert(i);                               // add the index to the used indices (for the train data)
        }
    }
}
void kmeans::train()
{
    while (used_indices->size() != train_data->size()) // while there are still data points not used
    {
        int idx = (rand() % (train_data->size())); // get a random index between 0 and train_data->size()
        // int idx = 0; // to speed up the process
        while (used_indices->find(idx) != used_indices->end()) // if the index is already used, get a new one
        {
            idx = (rand() % (train_data->size()));
            // idx++;
        }
        double min_dist = std::numeric_limits<double>::max(); // initialize the minimum distance to the maximum double value
        int best_cluster = -1;                                // -1 means no cluster is the best cluster
        for (int i = 0; i < clusters->size(); i++)            // for each cluster
        {
            // double curr_dist = manhattan_distance(clusters->at(i)->centroid, train_data->at(idx)); // get the distance between the centroid and the data point at idx
            double curr_dist = euclidean_distance(clusters->at(i)->centroid, train_data->at(idx)); // get the distance between the centroid and the data point at idx
            if (curr_dist < min_dist)                                                              // if the distance is less than the minimum distance
            {
                min_dist = curr_dist; // update the minimum distance
                best_cluster = i;     // update the best cluster
            }
        }
        clusters->at(best_cluster)->add_to_cluster(train_data->at(idx)); // add the data point at idx to the best cluster
        used_indices->insert(idx);                                       // add the index to the used indices
    }
}
double kmeans::euclidean_distance(std::vector<double> *centeroid, data *d)
{
    double dist = 0.0;                          // initialize the distance to 0
    for (int i = 0; i < centeroid->size(); i++) // for each value in the centroid
    {
        dist += pow(centeroid->at(i) - d->get_feature_vector()->at(i), 2); // add the squared difference between the centroid and the data point
    }
    return sqrt(dist); // return the square root of the distance
}

double kmeans::manhattan_distance(std::vector<double> *centeroid, data *d)
{
    double dist = 0.0;                          // initialize the distance to 0
    for (int i = 0; i < centeroid->size(); i++) // for each value in the centroid
    {
        dist += abs(centeroid->at(i) - d->get_feature_vector()->at(i)); // add the absolute difference between the centroid and the data point
    }
    return dist; // return the distance
}
double kmeans::validate_performance()
{
    double correct = 0.0;      // initialize the number of correct predictions to 0
    for (auto d : *valid_data) // for each data point in the validation data
    {
        double min_dist = std::numeric_limits<double>::max(); // initialize the minimum distance to the maximum double value
        int best_cluster = -1;                                // -1 means no cluster is the best cluster
        for (int i = 0; i < clusters->size(); i++)            // for each cluster in the clusters vector
        {
            // double curr_dist = manhattan_distance(clusters->at(i)->centroid, d); // get the distance between the centroid and the data point
            double curr_dist = euclidean_distance(clusters->at(i)->centroid, d); // get the distance between the centroid and the data point
            if (curr_dist < min_dist)                                            // if the distance is less than the minimum distance
            {
                min_dist = curr_dist; // update the minimum distance
                best_cluster = i;     // update the best cluster
            }
        }
        if (clusters->at(best_cluster)->most_freq_class == d->get_label()) // if the most frequent class in the best cluster is the same as the data point's class
        {
            correct++; // increment the number of correct predictions
        }
    }
    return 100.0 * (correct / (double)valid_data->size()); // return the percentage of correct predictions
}
double kmeans::test_performance() // same as validate_performance() but for the test data
{
    double correct = 0.0;
    for (auto d : *test_data)
    {
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = -1;
        for (int i = 0; i < clusters->size(); i++)
        {
            // double curr_dist = manhattan_distance(clusters->at(i)->centroid, d);
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
// kmeans::~kmeans()
// {
//     // for (auto c : *clusters) // for each cluster in the clusters vector
//     // {
//     //     delete c; // delete the cluster
//     // }
//     // delete clusters;     // delete the clusters vector
//     // delete used_indices; // delete the used indices
// }

double kmeans::calculate_wcss()
{
    double wcss = 0.0;
    for (int i = 0; i < clusters->size(); i++)
    {
        for (int j = 0; j < clusters->at(i)->cluster_points->size(); j++)
        {
            wcss += euclidean_distance(clusters->at(i)->centroid, clusters->at(i)->cluster_points->at(j));
        }
    }
    return wcss;
}

// int main() // driver code
// {
//     data_handler *dh = new data_handler();                                     // initialize the data handler
//     dh->read_feature_vector("../Dataset/train-images-idx3-ubyte");             // read the feature vector from the train images file
//     dh->read_label_vector("../Dataset/train-labels-idx1-ubyte");               // read the label vector from the train labels file
//     dh->split_data();                                                          // split the data into train, validation, and test data
//     dh->count_classes();                                                       // count the number of classes
//     double performance = 0, best_performance = 0.0;                            // initialize the performance variables
//     int best_k = 1;                                                            // assuming that the best k is 1
//     for (int k = dh->get_num_classes(); k < dh->get_train_data()->size(); k++) // starts from the number of classes and goes up to the number of data points
//     {
//         kmeans *km = new kmeans(k);                    // initialize the kmeans object
//         km->set_test_data(dh->get_test_data());        // set the test data
//         km->set_valid_data(dh->get_validation_data()); // set the validation data
//         km->set_train_data(dh->get_train_data());      // set the train data
//         km->initialize_clusters_for_each_class();      // initialize the clusters for each class
//         km->train();                                   // train the model
//         performance = km->validate_performance();      // get the performance on the validation data
//         std::cout << "Current performance: " << performance << "%"
//                   << " at k = " << k << "\n";
//         if (performance > best_performance)
//         {
//             best_performance = performance;
//             best_k = k;
//         }
//     }
//     kmeans *km = new kmeans(best_k);
//     km->set_test_data(dh->get_test_data());
//     km->set_valid_data(dh->get_validation_data());
//     km->set_train_data(dh->get_train_data());
//     km->initialize_clusters_for_each_class();
//     km->test_performance();
//     performance = km->test_performance();
//     std::cout << "Best performance: " << performance << "%"
//               << " at k = " << best_k << "\n";
// }

// used WCSS to find the best k
int main()
{
    data_handler *dh = new data_handler();                         // initialize the data handler
    dh->read_feature_vector("../Dataset/train-images-idx3-ubyte"); // read the feature vector from the train images file
    dh->read_label_vector("../Dataset/train-labels-idx1-ubyte");   // read the label vector from the train labels file
    dh->split_data();                                              // split the data into train, validation, and test data
    dh->count_classes();                                           // count the number of classes
    double performance = 0, best_performance = 0.0;                // initialize the performance variables
    int best_k = 1;                                                // assuming that the best k is 1

    std::vector<double> wcss_values;            // to store the WCSS values
    std::vector<double> validation_performance; // to store the validation performance values

    for (int k = dh->get_num_classes(); k < dh->get_train_data()->size(); k++) // starts from the number of classes and goes up to the number of data points
    {
        kmeans *km = new kmeans(k);                    // initialize the kmeans object
        km->set_test_data(dh->get_test_data());        // set the test data
        km->set_valid_data(dh->get_validation_data()); // set the validation data
        km->set_train_data(dh->get_train_data());      // set the train data
        km->initialize_clusters_for_each_class();      // initialize the clusters for each class
        km->train();                                   // train the model
        double wcss = km->calculate_wcss();            // get the WCSS value for the current k
        double val_perf = km->validate_performance();  // get the performance on the validation data
        wcss_values.push_back(wcss);
        validation_performance.push_back(val_perf);

        std::cout << "For k = " << k << ": WCSS = " << wcss << ", Validation Performance = " << val_perf << "%\n";

        if (wcss_values.size() > 1 && wcss_values[wcss_values.size() - 2] - wcss_values[wcss_values.size() - 1] < 0.01 &&
            val_perf >= best_performance)
        {
            // If the rate of decrease in WCSS is small and validation performance is better, update best_k and best_performance
            best_k = k - 1;
            best_performance = val_perf;
            break; // break out of the loop
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

    delete dh;

    return 0;
}
