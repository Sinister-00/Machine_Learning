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

void data_handler::read_feature_vector(std::string path)
{
    uint32_t header[4]; // Magic number, number of images, number of rows, number of columns
    unsigned char bytes[4];
    FILE *fp = fopen(path.c_str(), "r");
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
        for (int i = 0; i < header[1]; i++)
        {
            data *d = new data();
            uint8_t elem[1];
            for (int j = 0; j < img_size; i++)
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
    unsigned char bytes[2];
    FILE *fp = fopen(path.c_str(), "r");
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
        for (int i = 0; i < header[1]; i++)
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
}
void data_handler::count_classes()
{
}

uint32_t data_handler::convert_to_little_endian(const unsigned char *bytes)
{
}
std::vector<data *> *data_handler::get_train_data()
{
}
std::vector<data *> *data_handler::get_test_data()
{
}
std::vector<data *> *data_handler::get_validation_data()
{
}