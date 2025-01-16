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
        int lines_total = count_lines(params.file);
        int lines_read;

        struct sensor *data = malloc(lines_total * sizeof(struct sensor));
        int error_lines[MAX_ERROR_LINES];

        printf("Total lines %d\n", lines_total);

        lines_read = read_data_from_file(params.file, data, error_lines);

        printf("Read lines %d\n", lines_read);

        print_error_lines(lines_total - lines_read, error_lines);

        if (params.month == MONTH_NOT_SET)
        {
            print_year_statistics(lines_read, data);
        }
        else
        {
            print_month_statistics(lines_read, data, params.month);
        }

        free(data);
    }

    return 0;
}
