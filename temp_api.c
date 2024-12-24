#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <search.h>
#include "temp_api.h"

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
            "%02d.%02d.%04d %02d:%02d t=%02d\n",
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
    int sum = 0;
    int counter = 0;

    for (int i = 0; i < size; i++)
    {
        if (data[i].month == month)
        {
            sum += data[i].temperature;
            counter++;
        }
    }

    return (float)sum / counter;
}

int month_min_temp(int size, struct sensor *data, int month)
{
    int min = data[0].temperature;

    for (int i = 1; i < size; i++)
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
    int max = data[0].temperature;

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

void read_data_from_file(FILE *file, int size, struct sensor *data){}

void print_year_statistics(int size, struct sensor *data){}
void print_month_statistics(int size, struct sensor *data, int month){}
