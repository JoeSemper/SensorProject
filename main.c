#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "temp_api.h"

#define SIZE 10
#define ARG_STING "hf:m:"

enum ARGS
{
    help = 'h',
    file = 'f',
    month = 'm'
};

void add_mock_data(int size, struct sensor *data)
{
    srand(time(NULL)); 
    int r = rand() % 2024;

    for (int i = 0; i < size; i++)
    {
        add_record(data, i, rand() % 31, rand() % 12, rand() % 2024, rand() % 24, rand() % 60, rand() % 40);
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
            printf("Arguments:\n-h - Help\n-f - Input file name (required)\n-m - Month\n");
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

    printf("Original:\n");
    add_mock_data(SIZE, data);
    print_all_records(SIZE, data);

    printf("By temperature:\n");
    sort_by_temperature(SIZE, data);
    print_all_records(SIZE, data);

    printf("By date:\n");
    sort_by_date(SIZE, data);
    print_all_records(SIZE, data);

    return 0;
}