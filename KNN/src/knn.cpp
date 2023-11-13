#include "knn.hpp"
knn::knn(int value)
{
    k = value;
}
knn::knn()
{
    // NA
}
knn::~knn()
{
    // NA
    delete_neighbors();
}
void knn::delete_neighbors()
{
    delete neighbors;    // Free up memory allocated for neighbors
    neighbors = nullptr; // Set the pointer to nullptr after deletion
}

// complexity: O(n^2) if k = n
// if k=2, then O(~n)
//
void knn::find_k_nearest_neighbors(data *d)
{
    neighbors = new std::vector<data *>;
    double min_distance = std::numeric_limits<double>::max(); // Set min_distance to max double value to ensure first distance is less than min_distance
    double prev_min_distance = min_distance;                  // Set prev_min_distance to max double value to ensure first distance is less than prev_min_distance
    int idx = 0;
    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < train_data->size(); j++)
            {
                double distance = calculateDistance(d, train_data->at(j));
                train_data->at(j)->set_distance(distance);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    idx = j;
                }
            }
            neighbors->push_back(train_data->at(idx));         // Add the nearest neighbor to the neighbors vector
            prev_min_distance = min_distance;                  // Set prev_min_distance to min_distance
            min_distance = std::numeric_limits<double>::max(); // Reset min_distance to max double value
        }
        else
        {
            for (int j = 0; j < train_data->size(); j++)
            {
                // double distance = calculateDistance(d, train_data->at(j));
                double distance = train_data->at(j)->get_distance();
                train_data->at(j)->set_distance(distance);
                if (distance < min_distance && distance > prev_min_distance)
                {
                    min_distance = distance;
                    idx = j;
                }
            }
            neighbors->push_back(train_data->at(idx));         // Add the nearest neighbor to the neighbors vector
            prev_min_distance = min_distance;                  // Set prev_min_distance to min_distance
            min_distance = std::numeric_limits<double>::max(); // Reset min_distance to max double value
        }
    }
}
void knn::set_train_data(std::vector<data *> *v)
{
    train_data = v;
}
void knn::set_test_data(std::vector<data *> *v)
{
    test_data = v;
}
void knn::set_valid_data(std::vector<data *> *v)
{
    valid_data = v;
}
void knn::set_k(int k)
{
    this->k = k;
}
int knn::prediction()
{
    std::map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbors->size(); i++)
    {
        uint8_t label = neighbors->at(i)->get_label();
        if (class_freq.find(label) == class_freq.end())
        {
            class_freq[label] = 1;
        }
        else
        {
            class_freq[label]++;
        }
    }
    int max = 0, best = 0;
    for (auto it : class_freq)
    {
        if (it.second > max)
        {
            max = it.second;
            best = it.first;
        }
    }
    // delete neighbors; // Free up memory allocated for neighbors //// handled by destructor
    delete_neighbors();
    return best; // Return the class label with the highest frequency
}
double knn::calculateDistance(data *d1, data *d2)
{
    double distance = 0.0;
    if (d1->get_feature_vector_size() != d2->get_feature_vector_size())
    {
        std::cout << "Error: Feature vector sizes do not match" << std::endl;
        return -1;
    }
#ifdef EUCLID
    for (unsigned i = 0; i < d1->get_feature_vector_size(); i++)
    {
        distance += pow(d1->get_feature_vector()->at(i) - d2->get_feature_vector()->at(i), 2);
        // std::cout << distance << std::endl;
    }

    distance = sqrt(distance);
#elif defined MANHATTAN
// TODO: Implement Manhattan distance
#endif
    return distance;
}

double knn::validatePerformance()
{
    double currenr = 0.0;
    int count = 0, idx = 0;
    for (data *d : *valid_data)
    {
        find_k_nearest_neighbors(d);
        int prediction = this->prediction();
        // printing d->get_label()
        std::cout << prediction << "->" << (int)d->get_label() << std::endl;
        // std::cout << "d->get_label(): " << (int)d->get_label() << std::endl;
        if (prediction == d->get_label())
        {
            count++;
        }
        // print current performance upto 3 decimal places
        idx++;
        std::cout << "Current performance: " << std::fixed << std::setprecision(3) << (((double)count * 100) / (double)(idx)) << "%" << std::endl;
        // delete neighbors;
    }
    std::cout << "Validation performance for k = " << k << " :" << std::fixed << std::setprecision(3) << (((double)count * 100) / (double)(valid_data->size())) << "%" << std::endl;
    return (((double)count * 100) / (double)(valid_data->size()));
}
double knn::testPerformance()
{
    double currenr = 0.0;
    int count = 0, idx = 0;
    for (data *d : *test_data)
    {
        find_k_nearest_neighbors(d);
        int prediction = this->prediction();
        if (prediction == d->get_label())
        {
            count++;
        }
    }
    std::cout << "Test performance: " << std::fixed << std::setprecision(3) << (((double)count * 100) / (double)(test_data->size())) << "%" << std::endl;
    return (((double)count * 100) / (double)(test_data->size()));
}

double data::get_distance()
{
    return distance;
}

int main()
{
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../Dataset/train-images-idx3-ubyte");
    dh->read_label_vector("../Dataset/train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();
    knn *knn_model = new knn();
    knn_model->set_train_data(dh->get_train_data());
    knn_model->set_test_data(dh->get_test_data());
    knn_model->set_valid_data(dh->get_validation_data());
    knn_model->set_k(3);
    double performance = 0, best_performance = 0.0;
    int best_k = 0;
    for (int i = 1; i <= 4; i++)
    {
        if (i == 1)
        {
            knn_model->set_k(i);
            performance = knn_model->validatePerformance();
            best_performance = performance;
        }
        else
        {
            knn_model->set_k(i);
            performance = knn_model->validatePerformance();
            if (performance > best_performance)
            {
                best_performance = performance;
                best_k = i;
            }
        }
    }
    knn_model->set_k(best_k);
    knn_model->testPerformance();
}
