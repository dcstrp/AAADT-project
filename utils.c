/**
 * @file utils.c
 * @author Pedro Vitória
 * @brief Provides implementations for a set of auxiliary functions used in several types of operations or calculations
 */

#include "utils.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

char **split(char *string, int nFields, const char *delim)
{

    char **tokens = (char **)malloc(sizeof(char *) * nFields);
    int index = 0;
    int len = strlen(string);
    tokens[index++] = &string[0];

    for (int i = 0; i < len; i++)
    {
        if (string[i] == delim[0])
        {
            string[i] = '\0';
            if (i < len - 1)
            {
                tokens[index++] = &string[i] + 1;
            }
        }
    }
    return tokens;
}

bool isEmpty(char *str)
{
    return strlen(str) == 0;
}

void replaceCharacter(char *str, char oldChar, char newChar)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == oldChar)
        {
            str[i] = newChar;
        }
    }
}

void fillMapOfRegionsStillInfected(PtList patientsList, PtMap regionsMap, PtMap mapOfRegionsStillInfected)
{
    int sizeList = 0;
    listSize(patientsList, &sizeList);

    ListElem patient;
    for (int i = 0; i < sizeList; i++)
    {
        listGet(patientsList, i, &patient);
        if ((strcmp(patient.status, "isolated") == 0)) //if isolated, put in the map
        {
            MapKey regionAsKey = mapKeyCreate(patient.region);
            MapValue regionValue;
            mapGet(regionsMap, regionAsKey, &regionValue);
            mapPut(mapOfRegionsStillInfected, regionAsKey, regionValue);
        }
    } //Once this is done, we'll have our filtered map.
}

int countLeapYears(Date date)
{
    //Código tirado e adaptado de: https://www.geeksforgeeks.org/find-number-of-days-between-two-given-dates/
    //Alterações feitas: Indentação e nomes das variáveis.
    int years = date.year;
    if (date.month <= 2)
    {
        years--;
    }

    return years / 4 - years / 100 + years / 400;
}

int getDifferenceBetweenDates(Date date1, Date date2)
{
    //Código tirado e adaptado de: https://www.geeksforgeeks.org/find-number-of-days-between-two-given-dates/
    //Alterações feitas: Indentação e nomes das variáveis.
    int monthDays[12] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

    long int n1 = date1.year * 365 + date1.day;

    for (int i = 0; i < date1.month - 1; i++)
    {
        n1 += monthDays[i];
    }

    n1 += countLeapYears(date1);

    long int n2 = date2.year * 365 + date2.day;
    for (int i = 0; i < date2.month - 1; i++)
    {
        n2 += monthDays[i];
    }

    n2 += countLeapYears(date2);

    return (n2 - n1);
}

Date stringToDate(char *dateStr)
{
    Date date;

    if (isEmpty(dateStr))
    {
        date.day = 0;
        date.month = 0;
        date.year = 0;
    }
    else
    {
        sscanf(dateStr, "%2d/%2d/%4d", &date.day, &date.month, &date.year);
    }
    return date;
}

Date findMostRecentConfirmedDate(PtList patientsList)
{
    ListElem pt;
    int maxDiff = 0;
    Date helperMax = dateCreate(1, 1, 1111);
    Date mostRecentDate;

    int sizeList = 0;
    listSize(patientsList, &sizeList);

    for (int i = 0; i < sizeList; i++)
    {
        listGet(patientsList, i, &pt);
        int newDiff = getDifferenceBetweenDates(helperMax, pt.confirmedDate);
        if (newDiff > maxDiff)
        {
            maxDiff = newDiff;
            mostRecentDate = dateCreate(pt.confirmedDate.day, pt.confirmedDate.month, pt.confirmedDate.year);
        }
    }
    return mostRecentDate;
}

bool calculateRegionStatistics(PtList patientsList, PtMap regionsMap, char *regionName, double *lethality, double *incidentRate, double *mortality, int sizeList, int sizeMap)
{
    int population = 0;

    MapValue region;
    mapGet(regionsMap, mapKeyCreate(regionName), &region);
    population = region.population;

    if (population <= 0)
    {
        return false;
    }

    int numberOfDeaths = 0;
    int numberOfInfections = 0;
    for (int i = 0; i < sizeList; i++)
    {
        ListElem patient;
        listGet(patientsList, i, &patient);
        if (strcmp(patient.region, regionName) == 0)
        {
            if (strcmp(patient.status, "deceased") == 0)
            {
                numberOfDeaths++;
            }
            else if (strcmp(patient.status, "isolated") == 0)
            {
                numberOfInfections++;
            }
        }
    }

    *lethality = ((double)numberOfDeaths / (double)sizeList) * 100;
    *mortality = ((double)numberOfDeaths / (double)population) * 10000;
    *incidentRate = ((double)numberOfInfections / (double)population) * 100;

    return true;
}

bool calculateCountryStatistics(PtList patientsList, PtMap regionsMap, char *country, double *lethality, double *incidentRate, double *mortality, int sizeList, int sizeMap)
{
    int populationOfKorea = 0;

    MapValue korea;
    mapGet(regionsMap, mapKeyCreate("South Korea"), &korea);
    populationOfKorea = korea.population;

    if (populationOfKorea <= 0)
    {
        return false;
    }

    int countryDeaths = 0;
    int countryInfections = 0;

    ListElem patient;
    for (int i = 0; i < sizeList; i++)
    {
        listGet(patientsList, i, &patient);
        if (strcmp(patient.country, country) == 0)
        {
            if (strcmp(patient.status, "deceased") == 0)
            {
                countryDeaths++;
            }
            else if (strcmp(patient.status, "isolated") == 0)
            {
                countryInfections++;
            }
        }
    }

    *lethality = ((double)countryDeaths / (double)sizeList) * 100;
    *mortality = ((double)countryDeaths / (double)populationOfKorea) * 10000;
    *incidentRate = ((double)countryInfections / (double)populationOfKorea) * 100;

    return true;
}
