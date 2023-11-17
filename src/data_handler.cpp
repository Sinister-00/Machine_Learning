#include "data_handler.hpp"
DataHandler::DataHandler()
{
    data_array = new std::vector<Data *>;
    train_data = new std::vector<Data *>;
    test_data = new std::vector<Data *>;
    validation_data = new std::vector<Data *>;
}
DataHandler::~DataHandler()
{
    // Delete all the Data
    // delete data_array;
    // delete train_data;
    // delete test_data;
    // delete validation_data;
}

void DataHandler::read_data_from_csv(std::string path, std::string delimiter)
{
    // std::cout << "I'm inside csv read\n";
    num_classes = 0;
    std::ifstream data_file;
    data_file.open(path.c_str());
    // std::cout << "I'm inside csv read 2\n";
    std::string line;

    while (getline(data_file, line))
    {
        if (line.length() == 0)
            continue;

        Data *d = new Data();
        d->set_normalised_feature_vector(new std::vector<double>());

        size_t posi = 0;
        std::string token;
        // std::cout << "entering the while loop\n";

        while ((posi = line.find(delimiter)) != std::string::npos)
        {
            // std::cout << "inside the while loop\n";
            token = line.substr(0, posi);
            d->append_normalised_feature_vector(std::stod(token));
            line.erase(0, posi + delimiter.length());
        }
        if (classMap.find(line) != classMap.end())
        {
            d->set_label(classMap[line]);
        }
        else
        {
            classMap[line] = num_classes;
            d->set_label(classMap[line]);
            num_classes++;
        }
        data_array->push_back(d);
    }

    for (Data *d : *data_array)
        d->set_class_vector(num_classes);

    feature_vector_size = data_array->at(0)->get_normalised_feature_vector()->size();
    // std::cout << "Successfully read " << data_array->size() << " data entries.\n";
}

void DataHandler::read_input_data(std::string path)
{
    uint32_t magic = 0, num_images = 0, num_rows = 0, num_cols = 0;
    unsigned char bytes[4];
    FILE *fp = fopen(path.c_str(), "rb");
    if (fp)
    {
        int i = 0;
        while (i < 4)
        {
            fread(bytes, sizeof(bytes), 1, fp); // read 4 bytes
            switch (i)
            {
            case 0:
                magic = convert_to_little_endian(bytes);
                i++;
                break;
            case 1:
                num_images = convert_to_little_endian(bytes);
                i++;
                break;
            case 2:
                num_rows = convert_to_little_endian(bytes);
                i++;
                break;
            case 3:
                num_cols = convert_to_little_endian(bytes);
                i++;
                break;
            }
        }
        std::cout << "number of images: " << num_images << "\n";
        std::cout << "Magic: " << magic << "\n";
        std::cout << "number of rows: " << num_rows << "\n";
        std::cout << "number of cols: " << num_cols << "\n";
        std::cout << "Done getting input file header" << std::endl;
        uint32_t img_size = num_rows * num_cols;
        for (i = 0; i < num_images; i++)
        {
            // std::cout << "inside the for loop\n";
            Data *d = new Data();
            d->set_feature_vector(new std::vector<uint8_t>());
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
            data_array->back()->set_class_vector(num_classes);
        }
        // std::cout << "Outside the loop\n";
        normalize_data();
        feature_vector_size = data_array->at(0)->get_feature_vector()->size();
        std::cout << "Successfully read " << data_array->size() << " data entries.\n";
        std::cout << "The Feature Vector Size is: " << feature_vector_size << std::endl;
    }
    else
    {
        std::cout << "Error opening file: " << path << std::endl;
        exit(1);
    }
}

void DataHandler::read_label_data(std::string path)
{
    // std::cout << "I'm inside read label data\n";
    uint32_t magic = 0, num_images = 0;
    unsigned char bytes[4];
    FILE *fp = fopen(path.c_str(), "r");
    if (fp)
    {
        int i = 0;
        while (i < 2)
        {
            if (fread(bytes, sizeof(bytes), 1, fp))
            {
                switch (i)
                {
                case 0:
                    magic = convert_to_little_endian(bytes);
                    i++;
                    break;
                case 1:
                    num_images = convert_to_little_endian(bytes);
                    i++;
                    break;
                }
            }
            else
            {
                std::cout << "Error reading from file\n";
                exit(1);
            }
        }
        std::cout << "number of images: " << num_images << "\n";
        std::cout << "Magic: " << magic << "\n";

        std::cout << "Done getting label file header" << std::endl;
        for (unsigned j = 0; j < num_images; j++)
        {
            uint8_t elem[1];
            if (fread(elem, sizeof(elem), 1, fp))
            {
                data_array->at(j)->set_label(elem[0]);
            }
            else
            {
                std::cout << "Error reading from file\n";
                exit(1); //
            }
        }
        std::cout << "Successfully read " << data_array->size() << " labels.\n";
    }
    else
    {
        std::cout << "Error opening file: " << path << std::endl;
        exit(1);
    }
}

void DataHandler::read_feature_vector(std::string path)
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
            Data *d = new Data();
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

void DataHandler::read_label_vector(std::string path)
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
void DataHandler::split_data()
{
    std::unordered_set<int> used_idxs;
    int train_size = data_array->size() * TRAIN_SET_PERCENTAGE;
    int test_size = data_array->size() * TEST_SET_PERCENTAGE;
    int validation_size = data_array->size() * VALIDATION_SET_PERCENTAGE;

    // comment starts here
    // // Using a random device as a random number generator engine
    // std::random_device rd;
    // // Using the Mersenne Twister engine with seed from random device
    // std::mt19937 g(rd());
    // std::shuffle(data_array->begin(), data_array->end(), g);
    // // training
    // int count = 0;
    // int idx = 0;
    // while (count < train_size)
    // {
    //     train_data->push_back(data_array->at(idx++));
    //     count++;
    // }
    // // test
    // count = 0;
    // while (count < test_size)
    // {
    //     test_data->push_back(data_array->at(idx++));
    //     count++;
    // }
    // // validation
    // count = 0;
    // while (count < validation_size)
    // {
    //     validation_data->push_back(data_array->at(idx++));
    //     count++;
    // }

    /// comment out the above and uncomment the below to use the old method

    int count = 0;
    // training
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
    std::cout << "Successfully split Data into training, test, and validation sets\n";
    std::cout << "Training set size: " << train_data->size() << std::endl;
    std::cout << "Test set size: " << test_data->size() << std::endl;
    std::cout << "Validation set size: " << validation_data->size() << std::endl;
}
void DataHandler::count_classes()
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
        else
        {
            data_array->at(i)->set_enum_label(class_map[data_array->at(i)->get_label()]);
        }
    }
    num_classes = count;
    for (Data *Data : *data_array)
    {
        Data->set_class_vector(num_classes);
    }
    std::cout << "Successfully counted number of classes: " << num_classes << std::endl;
}

void DataHandler::normalize_data()
{
    std::vector<double> mins, maxs;
    Data *d = data_array->at(0);
    for (auto val : *d->get_feature_vector())
    {
        mins.push_back(val);
        maxs.push_back(val);
    }
    int size = data_array->size();
    for (int i = 1; i < size; i++)
    {
        d = data_array->at(i);
        for (int j = 0; j < d->get_feature_vector_size(); j++)
        {
            double val = (double)d->get_feature_vector()->at(j);
            if (val < mins.at(j))
            {
                mins[j] = val;
            }
            if (val > maxs.at(j))
            {
                maxs[j] = val;
            }
        }
    }

    // normalize
    size = data_array->size();
    for (int i = 0; i < size; i++)
    {
        data_array->at(i)->set_normalised_feature_vector(new std::vector<double>());
        data_array->at(i)->set_class_vector(num_classes);
        for (int j = 0; j < data_array->at(i)->get_feature_vector_size(); j++)
        {
            if (maxs[j] - mins[j] == 0)
            {
                data_array->at(i)->append_normalised_feature_vector(0.0);
            }
            else
            {
                data_array->at(i)->append_normalised_feature_vector((double)(data_array->at(i)->get_feature_vector()->at(j) - mins[j]) / (maxs[j] - mins[j]));
            }
        }
    }
}

uint32_t DataHandler::convert_to_little_endian(const unsigned char *bytes)
{
    // from stack overflow

    return (uint32_t)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]));
}

int DataHandler::get_num_classes()
{
    return num_classes;
}

std::vector<Data *> *DataHandler::get_train_data()
{
    return train_data;
}
std::vector<Data *> *DataHandler::get_test_data()
{
    return test_data;
}
std::vector<Data *> *DataHandler::get_validation_data()
{
    return validation_data;
}

int DataHandler::get_feature_vector_size()
{
    return feature_vector_size;
}
int DataHandler::get_training_data_size()
{
    return train_data->size();
}
int DataHandler::get_testing_data_size()
{
    return test_data->size();
}
int DataHandler::get_validation_data_size()
{
    return validation_data->size();
}

std::map<uint8_t, int> DataHandler::get_class_map()
{
    return class_map;
}
// testing that the Data handler works

// run this command to compile: g++ -Wall -std=c++17 -I./include/ -o test ./src/*.cpp
// int main()
// {
//     DataHandler *dh = new DataHandler();
//     dh->read_feature_vector("Dataset/train-images-idx3-ubyte");
//     dh->read_label_vector("Dataset/train-labels-idx1-ubyte");
//     dh->split_data();
//     dh->count_classes();
//     std::cout << "Done\n";
//     return 0;
// }