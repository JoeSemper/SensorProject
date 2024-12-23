#include <stdint.h>

struct sensor
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hours;
    uint8_t minutes;
    uint8_t temperature;
};

void add_record(struct sensor *data, int position, uint8_t day,
                uint8_t month, uint16_t year, uint8_t hours,
                uint8_t minutes, int8_t temperature);

void print_all_records(int size, struct sensor *data);

void sort_by_temperature(int size, struct sensor *data);
void sort_by_date(int size, struct sensor *data);

float month_avg_temp(int size, struct sensor *data, int month);
int month_min_temp(int size, struct sensor *data, int month);
int month_max_temp(int size, struct sensor *data, int month);

float year_avg_temp(int size, struct sensor *data);
int year_min_temp(int size, struct sensor *data);
int year_max_temp(int size, struct sensor *data);