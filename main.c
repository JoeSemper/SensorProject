#include <stdio.h>
#include "temp_api.h"
#include "util.h"

int main(int argc, char **argv)
{
    struct parameters params = {.need_help = false, .file = NULL, .month = MONTH_NOT_SET};

    read_arguments(argc, argv, &params);

    if (params.need_help)
        print_help_text();

    if (params.file != NULL)
    {
        int size = count_lines(params.file);
        struct sensor data[size];

        read_data_from_file(params.file, size, data);

        if (params.month == MONTH_NOT_SET)
        {
            print_year_statistics(size, data);
        }
        else
        {
            print_month_statistics(size, data, params.month);
        }
    }

    return 0;
}