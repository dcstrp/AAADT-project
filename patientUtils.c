/**
 * @file patientUtils.c
 * @author Pedro Vitória
 * @brief Provides implementations for all auxiliary functions used in patient-related commands
 */

#include "patientUtils.h"
#include "topfivestats.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int findPatientIndex(PtList list, long int patientID, int startRank, int endRank)
{
    ListElem elem;
    int sizeOfList = 0;
    listSize(list, &sizeOfList);

    for (int i = 0; i < sizeOfList; i++)
    {
        listGet(list, i, &elem);
        if (elem.id == patientID)
        {
            return i;
        }
    }
    return -1;
}

void calculatePercentageOfInfectedPatientsBySex(PtList list, double *malePercentage, double *femalePercentage, double *unknownPercentage)
{

    ListElem patient;
    double amountOfMales = 0;
    double amountOfFemales = 0;
    double amountOfUnknowns = 0;

    int sizeOfList = 0;
    listSize(list, &sizeOfList);

    for (int i = 0; i < sizeOfList; i++)
    {
        listGet(list, i, &patient);
        if ((strcmp(patient.sex, "male") == 0))
        {
            amountOfMales++;
        }
        else if ((strcmp(patient.sex, "female") == 0))
        {
            amountOfFemales++;
        }
        else
        {
            amountOfUnknowns++;
        }
    }

    *malePercentage = (amountOfMales / sizeOfList) * 100;
    *femalePercentage = (amountOfFemales / sizeOfList) * 100;
    *unknownPercentage = (amountOfUnknowns / sizeOfList) * 100;
}

void calculateAverageAgeByState(PtList list, double *averageIsolatedAge, double *averageDeceasedAge, double *averageReleasedAge)
{
    int sizeOfList = 0;
    listSize(list, &sizeOfList);

    ListElem patient;

    double deceasedCount = 0;
    double isolatedCount = 0;
    double releasedCount = 0;

    double totalDeceasedAge = 0;
    double totalIsolatedAge = 0;
    double totalReleasedAge = 0;

    for (int i = 0; i < sizeOfList; i++)
    {
        listGet(list, i, &patient);
        if (patient.birthYear != -1)
        {
            if (strcmp(patient.status, "isolated") == 0)
            {
                isolatedCount++;
                totalIsolatedAge += (2020 - patient.birthYear);
            }
            if (strcmp(patient.status, "deceased") == 0)
            {
                deceasedCount++;
                totalDeceasedAge += (2020 - patient.birthYear);
            }
            if (strcmp(patient.status, "released") == 0)
            {
                releasedCount++;
                totalReleasedAge += (2020 - patient.birthYear);
            }
        }
    }
    *averageDeceasedAge = totalDeceasedAge / deceasedCount;
    *averageIsolatedAge = totalIsolatedAge / isolatedCount;
    *averageReleasedAge = totalReleasedAge / releasedCount;
}

bool getPatientByID(PtList patientsList, long int patientID, Patient *soughtPatient)
{
    int sizeOfList = 0;
    listSize(patientsList, &sizeOfList);
    int index = findPatientIndex(patientsList, patientID, 0, sizeOfList);

    if (index != -1)
    {
        listGet(patientsList, index, soughtPatient);
        return true;
    }
    else
    {
        return false;
    }
}

void calculateEarliestBirthYearBySex(PtList patientsList, int *earliestMaleYear, int *earliestFemaleYear)
{
    int sizeOfList = 0;
    listSize(patientsList, &sizeOfList);

    ListElem patient;
    listGet(patientsList, 0, &patient);

    int earliestMale = (patient.birthYear != -1 ? patient.birthYear : 2000);
    int earliestFemale = earliestMale;

    for (int i = 0; i < sizeOfList; i++)
    {
        listGet(patientsList, i, &patient);
        if (patient.birthYear != -1)
        {
            if (patient.birthYear < earliestMale && (strcmp(patient.sex, "male") == 0))
            {
                earliestMale = patient.birthYear;
            }
            else if (patient.birthYear < earliestFemale && (strcmp(patient.sex, "female") == 0))
            {
                earliestFemale = patient.birthYear;
            }
        }
    }
    *earliestMaleYear = earliestMale;
    *earliestFemaleYear = earliestFemale;
}

int calculateIsolatedByAgeRange(PtList list, int startingAge, int endingAge)
{
    int sizeList = 0;
    listSize(list, &sizeList);
    int isolatedAmount = 0;

    for (int i = 0; i < sizeList; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        int age = 2020 - elem.birthYear;
        if (age >= startingAge && age <= endingAge)
        {
            if (strcmp(elem.status, "isolated") == 0)
            {
                isolatedAmount++;
            }
        }
    }
    return isolatedAmount;
}

int calculateDeceasedByAgeRange(PtList list, int startingAge, int endingAge)
{
    int sizeList = 0;
    listSize(list, &sizeList);
    int deceasedAmount = 0;

    for (int i = 0; i < sizeList; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        int age = 2020 - elem.birthYear;
        if (age >= startingAge && age <= endingAge)
        {
            if (strcmp(elem.status, "deceased") == 0)
            {
                deceasedAmount++;
            }
        }
    }
    return deceasedAmount;
}

int calculateReleasedByAgeRange(PtList list, int startingAge, int endingAge)
{
    int sizeList = 0;
    listSize(list, &sizeList);
    int releasedAmount = 0;

    for (int i = 0; i < sizeList; i++)
    {
        ListElem elem;
        listGet(list, i, &elem);
        int age = 2020 - elem.birthYear;
        if (age >= startingAge && age <= endingAge)
        {
            if (strcmp(elem.status, "released") == 0)
            {
                releasedAmount++;
            }
        }
    }
    return releasedAmount;
}

void deathsPreviousToCurrentDay(PtList patientsList, Date date, Date previousDate, int *previousDeaths, int *currentDeaths)
{
    int sizeList = 0;
    int prevDeaths = 0;
    int sameDayDeaths = 0;
    int totalDeaths = 0;
    ListElem patient;

    listSize(patientsList, &sizeList);

    for (int i = 0; i < sizeList; i++)
    {
        listGet(patientsList, i, &patient);

        if (dateEquals(previousDate, patient.deceasedDate))
        {
            prevDeaths++;
        }
        if (dateEquals(date, patient.deceasedDate))
        {
            sameDayDeaths++;
        }
    }
    *previousDeaths = prevDeaths;
    *currentDeaths = prevDeaths + sameDayDeaths;
}

void isolatedPreviousToCurrentDay(PtList patientsList, Date date, Date previousDate, int *previousIsolated, int *currentIsolated)
{
    int sizeList = 0;
    int prevDayIsolated = 0;
    int sameDayIsolated = 0;
    int totalIsolated = 0;
    ListElem patient;

    listSize(patientsList, &sizeList);

    for (int i = 0; i < sizeList; i++)
    {
        listGet(patientsList, i, &patient);

        if (dateEquals(previousDate, patient.confirmedDate))
        {
            prevDayIsolated++;
        }
        if (dateEquals(date, patient.confirmedDate))
        {
            sameDayIsolated++;
        }
    }
    *previousIsolated = prevDayIsolated;
    *currentIsolated = sameDayIsolated;
}

void filterListByReleased(PtList patientsList, int sizeAllPatientsList, PtList *patientsReleasedList, int *sizeReleasedList)
{
    for (int i = 0; i < sizeAllPatientsList; i++)
    {
        ListElem patient;
        listGet(patientsList, i, &patient);

        if (strcmp(patient.status, "released") == 0)
        {
            if (patient.releasedDate.day != 0)
            {
                /* Add at the end of the list using the size of the list as the index for the new element (rank). 
                * This is done because the ranks have to be sequential and since not all patients will have a released state, 
                * the ranks (that come from the counter in the for loop) might not always be sequential.
                * Therefor, we must use the size of the list as a new  element's rank.
                */
                listAdd(*patientsReleasedList, *sizeReleasedList, patient);
                //The size must then be updated to maintain the sequential order of ranks, otherwise the element would keep being added in the same index.
                listSize(*patientsReleasedList, sizeReleasedList);
            }
        }
    }
}