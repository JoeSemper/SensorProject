#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 65536
#define ARG_STRING "hf:m:"
#define MONTH_NOT_SET -1
#define HELP_TEXT "Temperature statistics utile\nOptions:\n-h - Help\n-f <file_name> - Data file name\n-m <month> - Month\n"
#define MAX_ERROR_LINES 100

enum PARAMS_LIST
{
    help = 'h',
    file = 'f',
    month = 'm'
};

struct parameters
{
    bool need_help;
    FILE *file;
    int month;
};

void read_arguments(int argc, char **argv, struct parameters *params);

int count_lines(FILE *file);

void print_help_text();

void print_error_lines(int size, int *error_lines);