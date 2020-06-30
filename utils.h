/**
 * @file utils.h
 * @author Pedro Vitória
 * @brief Defines a set of auxiliary functions to aid in several types of operations or calculations.
 */

#pragma once

#include "list.h"
#include "map.h"

/**
 * @brief Splits a string into seperate pieces.
 * 
 * @param string [in] An array of characters
 * @param nFields [in] The number of fields to take in consideration in the splitting process
 * @param delim [in] A delimiter to determine how the splitting occurs in regards to field separation
 * @return An array of strings containing the split fields
 */
char **split(char *string, int nFields, const char *delim);

/**
 * @brief Checks if a given string is empty.
 * 
 * @param str [in] The string to be checked
 * @return true if it's empty
 * @return false if it's not empty
 */
bool isEmpty(char *str);

/**
 * @brief Replaces all occurences of a given character in a string with a new character
 * @param str [in] The string where the character(s) will be replaced
 * @param oldChar [in] The character to be replaced
 * @param newChar [in] The replacement character
 */
void replaceCharacter(char *str, char oldChar, char newChar);

/**
 * @brief Fills a new instance of Map with the regions that still have active COVID-19 cases.
 * 
 * @param patientsList [in] A list of patients
 * @param regionsMap [in] The map of all existing regions
 * @param mapOfRegionsStillInfected [out] The map that will only contain regions that still have active COVID-19 cases
 */
void fillMapOfRegionsStillInfected(PtList patientsList, PtMap regionsMap, PtMap mapOfRegionsStillInfected);

/**
 * @brief Calculates the number of leap years before a given date.
 * 
 * @param date [in] The date
 * @return The number of leap years
 */
int countLeapYears(Date date);

/**
 * @brief Calculates the difference of days between two dates.
 * 
 * @param date1 [in] The first date
 * @param date2 [in] The second date
 * @return The difference, in days, between both dates
 */
int getDifferenceBetweenDates(Date date1, Date date2);

/**
 * @brief Converts a date in a string format to an instance of Date.
 * 
 * @param dateStr [in] The date to be converted
 * @return Date The instance of date after conversion
 */
Date stringToDate(char *dateStr);

/**
 * @brief Finds the most recent confirmed date in a list of patients.
 * 
 * @param patientsList [in] A list of patients
 * @return Date The most recent confirmed date
 */
Date findMostRecentConfirmedDate(PtList patientsList);

/**
 * @brief Calculates and returns by reference the following statistics for a region
 * <ul>
 * <li>Lethality
 * <li>Mortality rate
 * <li>Incident Rate of infection
 * </ul>
 * (Units for the statistics are given in percentages)<br>
 * This function also determines if the specified region has a populational number.
 * @param patientsList [in] A list of patients
 * @param regionsMap [in] A map of regions
 * @param regionName [in] The name of the region to perform the aforementioned calculations for
 * @param lethality [out] The lethality of the disease
 * @param incidentRate [out] The incident rate of infection
 * @param mortality [out] The mortality rate
 * @param sizeList [in] The number of patients in the list
 * @param sizeMap [in] The number of regions in the map
 * @return true if the region has a populational number or,
 * @return false if the region has no population
 */
bool calculateRegionStatistics(PtList patientsList, PtMap regionsMap, char *regionName, double *lethality, double *incidentRate, double *mortality, int sizeList, int sizeMap);

/**
 * @brief Calculates and returns by reference the following country-related statistics
 * <ul>
 * <li>Lethality
 * <li>Mortality rate
 * <li>Incident Rate of infection
 * </ul> 
 * (Units for the statistics are given in percentages)<br>
 * This function also determines if the specified region has a populational number.
 * @param patientsList [in] A list of patients
 * @param regionsMap [in] A map of regions
 * @param country [in] The name of the country to perform the aforementioned calculations for
 * @param lethality [out] The lethality of the disease
 * @param incidentRate [out] The incident rate of infection
 * @param mortality [out] The mortality rate
 * @param sizeList [in] The number of patients in the list
 * @param sizeMap [in] The number of regions in the map
 * @return true if the country has a populational number or,
 * @return false if the country has no population
 */
bool calculateCountryStatistics(PtList patientsList, PtMap regionsMap, char *country, double *lethality, double *incidentRate, double *mortality, int sizeList, int sizeMap);

