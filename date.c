/**
 * @file date.c
 * @author Pedro Vitória
 * @brief Provides implementations for all operations related to the <b><i>Date</i></b> data type
 */

#include "date.h"
#include <stdio.h>

Date dateCreate(unsigned int day, unsigned int month, unsigned int year)
{
    Date date;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

void datePrint(Date date)
{
    printf("%02d/%02d/%d", date.day, date.month, date.year);
}

bool dateEquals(Date date1, Date date2)
{
    return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year);
}