#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "util.h"

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
            params->month = optarg[0] - '0';
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
