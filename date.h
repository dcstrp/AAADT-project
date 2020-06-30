/**
 * @file date.h
 * @author Pedro Vitória
 * @brief Defines the data type <b><i>Date</i></b> and related operations.
 */

#pragma once

#include <stdbool.h>

/**
 * @brief Represents a date (DD/MM/YYYY).
 * 
 */
typedef struct date
{
    unsigned int day, month, year;
} Date;

/**
 * @brief Returns a newly created instance of Date. This instance stores a given date in a DD/MM/YYYY format.
 * 
 * @param day [in] The day
 * @param month [in] The month
 * @param year [in] The year
 * @return Date The newly created instance of Date
 */
Date dateCreate(unsigned int day, unsigned int month, unsigned int year);

/**
 * @brief Prints a textual representation of a given Date.
 * 
 * @param date [in] An instance of date to print
 */
void datePrint(Date date);

/**
 * @brief Compares two dates for equality.
 * 
 * @param date1 The first date
 * @param date2 The second date
 * @return true If the dates are equal or,
 * @return false If the dates are different
 */
bool dateEquals(Date date1, Date date2);