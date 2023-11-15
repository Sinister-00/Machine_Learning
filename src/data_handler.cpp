#include "data_handler.hpp"
data_handler::data_handler()
{
    data_array = new std::vector<data *>;
    train_data = new std::vector<data *>;
    test_data = new std::vector<data *>;
    validation_data = new std::vector<data *>;
}
data_handler::~data_handler()
{
    // Delete all the data
    delete data_array;
    delete train_data;
    delete test_data;
    delete validation_data;
}

void data_handler::read_data_from_csv(std::string path, std::string delimiter)
{
    // also well count classes here;
    // general function supposed to be;
    num_classes = 0;
    std::ifstream data_file(path.c_str());
    std::string line; // stores each line of the csv file
    while (getline(data_file, line))
    {
        if (line.length() == 0)
            continue;
        data *d = new data();
        d->set_feature_vector(new std::vector<double>());
        size_t pos = 0;
        std::string token; // stores the value in between each delimiter
        while (pos == line.find(delimiter) != std::string::npos)
        {
            token = line.substr(0, pos);                // from 0 to the position of the delimiter not including the delimiter
            d->append_feature_vector(std::stod(token)); // convert the string to a double and append it to the feature vector
            line.erase(0, pos + delimiter.length());    // remove first token and shorten the array
        }
        if (classMap.find(line) == classMap.end())
        {
            d->set_label(classMap[line]);
        }
        else
        {
            classMap[line] = num_classes;
            d->set_label(num_classes);
            num_classes++;
        }
        data_array->push_back(d);
    }
    feature_vector_size = data_array->at(0)->get_feature_vector_double()->size();
}

void data_handler::read_feature_vector(std::string path)
{
    uint32_t header[4]; // Magic number, number of images, number of rows, number of columns
    unsigned char bytes[4];
    FILE *fp = fopen(path.c_str(), "rb");
    if (fp == NULL)
    {
        std::cout << "Error opening file: " << path << std::endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (fread(bytes, sizeof(bytes), 1, fp) != 1)
            {
                std::cout << "Error reading file: " << path << std::endl;
                exit(1);
            }
            header[i] = convert_to_little_endian(bytes);
        }
        std::cout << "Done getting input fle header header" << std::endl;
        int img_size = header[2] * header[3];
        for (uint32_t i = 0; i < header[1]; i++)
        {
            data *d = new data();
            uint8_t elem[1];
            for (int j = 0; j < img_size; j++)
            {
                if (fread(elem, sizeof(elem), 1, fp))
                {
                    d->append_feature_vector(elem[0]);
                }
                else
                {
                    std::cout << "Error reading from file\n";
                    exit(1); //
                }
            }
            data_array->push_back(d);
        }
        std::cout << "Successfully read and stored " << data_array->size() << " feature vectors\n";
    }
}
void data_handler::read_label_vector(std::string path)
{
    uint32_t header[2]; // Magic number, number of images
    unsigned char bytes[4];
    FILE *fp = fopen(path.c_str(), "rb");
    if (fp == NULL)
    {
        std::cout << "Error opening file: " << path << std::endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            if (fread(bytes, sizeof(bytes), 1, fp) != 1)
            {
                std::cout << "Error reading file: " << path << std::endl;
                exit(1);
            }
            header[i] = convert_to_little_endian(bytes);
        }
        std::cout << "Done getting label file header" << std::endl;
        // int img_size = header[2] * header[3];
        // std::cout << header[1] << std::endl;
        for (uint32_t i = 0; i < std::min(header[1], static_cast<uint32_t>(data_array->size())); i++)
        {
            uint8_t elem[1];
            if (fread(elem, sizeof(elem), 1, fp))
            {
                data_array->at(i)->set_label(elem[0]);
            }
            else
            {
                std::cout << "Error reading from file\n";
                exit(1); //
            }
        }
        std::cout << "Successfully read and stored " << data_array->size() << " labels\n";
    }
}
void data_handler::split_data()
{
    std::unordered_set<int> used_idxs;
    int train_size = data_array->size() * TRAIN_SET_PERCENTAGE;
    int test_size = data_array->size() * TEST_SET_PERCENTAGE;
    int validation_size = data_array->size() * VALIDATION_SET_PERCENTAGE;

    // training
    int count = 0;
    while (count < train_size)
    {
        int idx = rand() % data_array->size(); // index between 0 and data_array->size()-1
        if (used_idxs.find(idx) == used_idxs.end())
        {
            train_data->push_back(data_array->at(idx));
            used_idxs.insert(idx);
            count++;
        }
    }
    // test
    count = 0;
    while (count < test_size)
    {
        int idx = rand() % data_array->size(); // index between 0 and data_array->size()-1
        if (used_idxs.find(idx) == used_idxs.end())
        {
            test_data->push_back(data_array->at(idx));
            used_idxs.insert(idx);
            count++;
        }
    }
    // validation
    count = 0;
    while (count < validation_size)
    {
        int idx = rand() % data_array->size(); // index between 0 and data_array->size()-1
        if (used_idxs.find(idx) == used_idxs.end())
        {
            validation_data->push_back(data_array->at(idx));
            used_idxs.insert(idx);
            count++;
        }
    }
    std::cout << "Successfully split data into training, test, and validation sets\n";
    std::cout << "Training set size: " << train_data->size() << std::endl;
    std::cout << "Test set size: " << test_data->size() << std::endl;
    std::cout << "Validation set size: " << validation_data->size() << std::endl;
}
void data_handler::count_classes()
{
    int count = 0;
    for (unsigned int i = 0; i < data_array->size(); i++)
    {
        if (class_map.find(data_array->at(i)->get_label()) == class_map.end())
        {
            class_map[data_array->at(i)->get_label()] = count;
            data_array->at(i)->set_enum_label(count);
            count++;
        }
    }
    num_classes = count;
    for (data *data : *data_array)
    {
        data->set_class_vector(num_classes);
    }
    std::cout << "Successfully counted number of classes: " << num_classes << std::endl;
}

uint32_t data_handler::convert_to_little_endian(const unsigned char *bytes)
{
    // from stack overflow

    return (uint32_t)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]));
}

int data_handler::get_num_classes()
{
    return num_classes;
}

std::vector<data *> *data_handler::get_train_data()
{
    return train_data;
}
std::vector<data *> *data_handler::get_test_data()
{
    return test_data;
}
std::vector<data *> *data_handler::get_validation_data()
{
    return validation_data;
}

// testing that the data handler works

// run this command to compile: g++ -Wall -std=c++17 -I./include/ -o test ./src/*.cpp
// int main()
// {
//     data_handler *dh = new data_handler();
//     dh->read_feature_vector("Dataset/train-images-idx3-ubyte");
//     dh->read_label_vector("Dataset/train-labels-idx1-ubyte");
//     dh->split_data();
//     dh->count_classes();
//     std::cout << "Done\n";
//     return 0;
// }