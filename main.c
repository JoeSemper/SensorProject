#include <stdio.h>
#include "temp_api.h"
#define SIZE 5

void add_mock_data(int size, struct sensor *data)
{
    for (int i = 0; i < size; i++)
    {
        add_record(data, i, i*2, i, 2024, i*4, i*3, i*10);
    }
}

int main(int argc, char **argv)
{
    struct sensor data[SIZE]; 

    add_mock_data(SIZE, data);
    print_all_records(SIZE, data);

    return 0;
}