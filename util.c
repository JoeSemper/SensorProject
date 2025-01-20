#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "util.h"

int read_month(char *optarg)
{
    int month = optarg[0] - '0';
    if (optarg[1] > '0' && optarg[1] <= '9')
    {
        month *= 10 + optarg[1] - '0';
    }

    return (month > 1 && month < 13) ? month : MONTH_NOT_SET;
}

void read_arguments(int argc, char **argv, struct parameters *params)
{
    int arg;

    if (argc < 2)
    {
        params->need_help = true;
    }

    while ((arg = getopt(argc, argv, ARG_STRING)) != -1)
    {
        switch (arg)
        {
        case help:
            params->need_help = true;
            break;

        case file:
            printf("Opening file: %s\n", optarg);
            params->file = fopen(optarg, "r");

            if (params->file == NULL)
                printf("Can not open file %s\n", optarg);

            break;

        case month:
            params->month = read_month(optarg);
            break;

        default:
            break;
        }
    }
}

void print_help_text()
{
    printf(HELP_TEXT);
}

int count_lines(FILE *file)
{
    char buffer[BUF_SIZE];
    int counter = 0;

    for (;;)
    {
        uint64_t res = fread(buffer, sizeof(char), BUF_SIZE, file);

        int i;

        for (i = 0; i < res; i++)
        {
            if (buffer[i] == '\n')
            {
                counter++;
            }
        }

        if (feof(file))
        {
            break;
        }
    }

    return counter + 1;
}

void print_error_lines(int size, int *error_lines)
{
    if (size == 0)
    {
        return;
    }

    int max = size <= MAX_ERROR_LINES ? size : MAX_ERROR_LINES;

    printf("Error lines: ");

    for (int i = 0; i < max; i++)
    {
        if (i > 0)
        {
            printf(", ");
        }

        printf("%d", error_lines[i]);
    }

    printf("\n");
}