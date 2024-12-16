#include <stdio.h>
#include <stdint.h>
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

int month_avg_temp(int size, struct sensor *data, int month) {}

int month_min_temp(int size, struct sensor *data, int month) {}

int month_max_temp(int size, struct sensor *data, int month) {}

int year_avg_temp(int size, struct sensor *data) {}

int year_min_temp(int size, struct sensor *data) {}

int year_max_temp(int size, struct sensor *data) {}