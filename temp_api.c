#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <search.h>
#include "temp_api.h"

#define EXPECTED_PARAMS 6

void print_header(void)
{
    printf("Year   Month   Min_t   Max_t   Avg_t\n");
}

void add_record(struct sensor *data, int position, uint8_t day,
                uint8_t month, uint16_t year, uint8_t hours,
                uint8_t minutes, int8_t temperature)
{
    data[position].day = day;
    data[position].month = month;
    data[position].year = year;
    data[position].hours = hours;
    data[position].minutes = minutes;
    data[position].temperature = temperature;
}

void print_all_records(int size, struct sensor *data)
{
    printf("==========================\n");

    for (int i = 0; i < size; i++)
    {
        printf(
            "%02d.%02d.%04d %02d:%02d t=%d\n",
            data[i].day,
            data[i].month,
            data[i].year,
            data[i].hours,
            data[i].minutes,
            data[i].temperature);
    }
}

long date_to_minutes(const struct sensor *data)
{
    return (long)((data->year * 525600) + (data->month * 43800) + (data->day * 1440) + (data->hours * 60) + data->minutes);
}

int compare_temperature(const void *data_1, const void *data_2)
{
    return ((struct sensor *)data_1)->temperature - ((struct sensor *)data_2)->temperature;
}

int compare_date(const void *data_1, const void *data_2)
{
    return date_to_minutes(data_1) - date_to_minutes(data_2);
}

void sort_by_temperature(int size, struct sensor *data)
{
    qsort(data, size, sizeof(struct sensor), compare_temperature);
}

void sort_by_date(int size, struct sensor *data)
{
    qsort(data, size, sizeof(struct sensor), compare_date);
}

float month_avg_temp(int size, struct sensor *data, int month)
{
    float sum = 0;
    float counter = 0;

    for (int i = 0; i < size; i++)
    {
        if (data[i].month == month)
        {
            sum += data[i].temperature;
            counter++;
        }
    }

    return sum / counter;
}

int month_min_temp(int size, struct sensor *data, int month)
{
    int i = 0;

    while (data[i].month != month)
    {
        i++;
    }

    int min = data[i].temperature;

    i++;

    for (i; i < size; i++)
    {
        if (data[i].month == month)
        {
            min = data[i].temperature < min ? data[i].temperature : min;
        }
    }

    return min;
}

int month_max_temp(int size, struct sensor *data, int month)
{
    int i = 0;

    while (data[i].month != month)
    {
        i++;
    }

    int max = data[i].temperature;

    i++;

    for (int i = 1; i < size; i++)
    {
        if (data[i].month == month)
        {
            max = data[i].temperature > max ? data[i].temperature : max;
        }
    }

    return max;
}

float year_avg_temp(int size, struct sensor *data)
{
    int sum = 0;
    int counter = 0;

    for (int i = 0; i < size; i++)
    {
        sum += data[i].temperature;
        counter++;
    }

    return (float)sum / counter;
}

int year_min_temp(int size, struct sensor *data)
{
    int min = data[0].temperature;

    for (int i = 1; i < size; i++)
    {

        min = data[i].temperature < min ? data[i].temperature : min;
    }

    return min;
}

int year_max_temp(int size, struct sensor *data)
{
    int max = data[0].temperature;

    for (int i = 1; i < size; i++)
    {
        max = data[i].temperature > max ? data[i].temperature : max;
    }

    return max;
}

int read_data_from_file(FILE *file, struct sensor *data, int *error_lines)
{
    if (file == NULL)
    {
        printf("No such file");
        return 0;
    }

    fseek(file, 0, SEEK_SET);

    int read_lines = 0;
    int current_line = 0;
    int i = 0;
    int read_params;
    char tmp[50];

    int year, month, day, hours, minutes, temperature;

    while (!feof(file))
    {
        read_params = fscanf(file, "%d;%d;%d;%d;%d;%d\n", &year, &month, &day, &hours, &minutes, &temperature);

        if (read_params != EXPECTED_PARAMS)
        {
            fscanf(file, "%[^\n]", tmp);
            error_lines[i] = current_line;
            i++;
        }
        else
        {
            add_record(data, read_lines, day, month, year, hours, minutes, temperature);
            read_lines++;
        }

        current_line++;
    }

    return read_lines;
}

int has_month(int size, struct sensor *data, int month)
{
    for (int i = 0; i < size; i++)
    {
        if (data[i].month == month)
        {
            return 1;
        }
    }

    return 0;
}

void print_month_values(int size, struct sensor *data, int month)
{
    if (has_month(size, data, month))
    {
        int min, max;
        float avg;

        min = month_min_temp(size, data, month);
        max = month_max_temp(size, data, month);
        avg = month_avg_temp(size, data, month);

        printf("%d    %2d      %3d     %3d    %3.1f\n", data[0].year, month, min, max, avg);
    }
}

void print_month_statistics(int size, struct sensor *data, int month)
{
    print_header();
    print_month_values(size, data, month);
}

void print_year_monthly_values(int size, struct sensor *data)
{
    for (int i = 1; i <= 12; i++)
    {
        print_month_values(size, data, i);
    }
}

void print_year_values(int size, struct sensor *data)
{
    int min, max;
    float avg;

    min = year_min_temp(size, data);
    max = year_max_temp(size, data);
    avg = year_avg_temp(size, data);

    printf("Year statistics: min t = %d, max t = %d, avg t = %.2f", min, max, avg);
}

void print_year_statistics(int size, struct sensor *data)
{
    print_header();
    print_year_monthly_values(size, data);
    print_year_values(size, data);
}
