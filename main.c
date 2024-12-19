#include <stdio.h>
#include <unistd.h>
#include "temp_api.h"

#define SIZE 5
#define ARG_STING "hf:m:"

enum ARGS
{
    help = 'h',
    file = 'f',
    month = 'm'
};

void add_mock_data(int size, struct sensor *data)
{
    for (int i = 0; i < size; i++)
    {
        add_record(data, i, i * 2, i, 2024, i * 4, i * 3, i * 10);
    }
}

int main(int argc, char **argv)
{
    int arg = 0;

    while ((arg = getopt(argc, argv, ARG_STING)) != -1)
    {
        switch (arg)
        {
        case help:
            printf("Help\n");
            break;

        case file:
            printf("File %s\n", optarg);
            break;

        case month:
            printf("Month %s\n", optarg);
            break;

        default:
            break;
        }
    }

    struct sensor data[SIZE];

    add_mock_data(SIZE, data);
    print_all_records(SIZE, data);

    return 0;
}