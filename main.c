#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
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
        int lines = count_lines(params.file);
        int size;

        struct sensor* data = malloc(lines*sizeof(struct sensor));

        printf("Lines = %d\n", lines);

        size = read_data_from_file(params.file, data);

        printf("Read lines = %d\n", size);

        print_all_records(size, data);

        if (params.month == MONTH_NOT_SET)
        {
            print_year_statistics(size, data);
        }
        else
        {
            print_month_statistics(size, data, params.month);
        }

        free(data);
    }

    return 0;
}