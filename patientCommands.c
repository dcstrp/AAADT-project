/**
 * @file patientCommands.c
 * @author Pedro Vitória
 * @brief Provides implementations for all patient-related commands.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "topfivestats.h"
#include "patientUtils.h"
#include "patientCommands.h"

int importPatientsFromFile(char *filename, PtList *list, int *numberOfPatientsReadFromFile, Date *mostRecentConfirmedDate)
{
    FILE *f = NULL;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("File not found (%s).\n", filename);
        return FILE_NOT_FOUND;
    }

    char nextline[1024];
    int countPT = 0;
    bool firstLine = true;

    *list = listCreate(3129);
    if (list == NULL)
        return LIST_NULL;

    while (fgets(nextline, sizeof(nextline), f))
    {
        if (strlen(nextline) < 1)
            continue;

        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        char **tokens = split(nextline, 11, ";");

        int birthYear = isEmpty(tokens[2]) ? -1 : atoi(tokens[2]);
        long int infectedBy = isEmpty(tokens[6]) ? -1 : atol(tokens[6]);

        Date confirmedDate = stringToDate(tokens[7]);
        Date releasedDate = stringToDate(tokens[8]);
        Date deceasedDate = stringToDate(tokens[9]);

        char status[100];
        int length = strlen(tokens[10]) - 1;
        strncpy(status, tokens[10], length);
        status[length - 1] = '\0';

        ListElem patient = patientCreate(atol(tokens[0]), tokens[1], birthYear,
                                         tokens[3], tokens[4], tokens[5], infectedBy,
                                         confirmedDate, releasedDate, deceasedDate, status);
        free(tokens);

        int error_code = listAdd(*list, countPT, patient);
        if (error_code == LIST_FULL || error_code == LIST_INVALID_RANK || error_code == LIST_NO_MEMORY || error_code == LIST_NULL)
        {
            printf("An error ocurred.... Please try again... \n");
            return error_code;
        }
        countPT++;
    }
    *numberOfPatientsReadFromFile = countPT;
    *mostRecentConfirmedDate = findMostRecentConfirmedDate(*list);
    fclose(f);
    return FILE_OK;
}

int average(PtList patientsList)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    double averageIsolatedAge = 0, averageDeceasedAge = 0, averageReleasedAge = 0;
    calculateAverageAgeByState(patientsList, &averageIsolatedAge, &averageDeceasedAge, &averageReleasedAge);

    printf("\nAverage Age for deceased patients: %.0lf", round(averageDeceasedAge) > 0 ? round(averageDeceasedAge) : 0);
    printf("\nAverage Age for released patients: %.0lf", round(averageReleasedAge) > 0 ? round(averageReleasedAge) : 0);
    printf("\nAverage Age for isolated patients: %.0lf", round(averageIsolatedAge) > 0 ? round(averageIsolatedAge) : 0);
    printf("\n");

    return OPERATION_SUCCESS;
}

int follow(PtList patientsList, long int patientID)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    ListElem patient;
    bool patientExists = getPatientByID(patientsList, patientID, &patient);

    if (!patientExists)
    {
        printf("ID:%ld : does not exist record \n", patientID);
        return OPERATION_SUCCESS;
    }
    else if (patient.infectedBy == -1)
    {
        int age = (patient.birthYear != -1 ? 2020 - patient.birthYear : -1);

        printf("ID:%ld, Sex: %s, ", patient.id, patient.sex);
        if (age != -1)
        {
            printf("AGE: %d, ", age);
        }
        else
        {
            printf("AGE: %s, ", "unknown");
        }
        printf("COUNTRY/REGION: %s/%s, STATE: %s\ncontaminated by Unknown\n", patient.country, patient.region, patient.status);
        return OPERATION_SUCCESS;
    }
    else
    {
        int age = (patient.birthYear != -1 ? 2020 - patient.birthYear : -1);

        printf("ID:%ld, Sex: %s, ", patient.id, patient.sex);
        if (age != -1)
        {
            printf("AGE: %d, ", age);
        }
        else
        {
            printf("AGE: %s ", "unknown");
        }

        printf("COUNTRY/REGION: %s/%s, STATE: %s\ncontaminated by Patient: ", patient.country, patient.region, patient.status);
        follow(patientsList, patient.infectedBy);
    }
}

int sex(PtList patientsList)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    double malePercentage = 0, femalePercentage = 0, unknownPercentage = 0;
    int numberOfPatients = 0;
    listSize(patientsList, &numberOfPatients);
    calculatePercentageOfInfectedPatientsBySex(patientsList, &malePercentage, &femalePercentage, &unknownPercentage);

    printf("\nPercentage of Females: %.0lf%% ", round(femalePercentage));
    printf("\nPercentage of Males: %.0lf%% ", round(malePercentage));
    printf("\nPercentage of unknowns: %.0lf%% ", round(unknownPercentage));
    printf("\nTotal of patients: %d", numberOfPatients);
    printf("\n");

    return OPERATION_SUCCESS;
}

int show(PtList patientsList, long int idOfPatientToShow, Date mostRecentConfirmedDate)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    Patient soughtPatient;
    bool patientExists = getPatientByID(patientsList, idOfPatientToShow, &soughtPatient);

    if (patientExists)
    {
        int daysWithIllness;
        if (soughtPatient.releasedDate.day > 0)
        {
            daysWithIllness = getDifferenceBetweenDates(soughtPatient.confirmedDate, soughtPatient.releasedDate);
        }
        else if (strcmp(soughtPatient.status, "isolated") == 0)
        {
            daysWithIllness = getDifferenceBetweenDates(soughtPatient.confirmedDate, mostRecentConfirmedDate);
        }
        else if (soughtPatient.deceasedDate.day > 0)
        {
            daysWithIllness = getDifferenceBetweenDates(soughtPatient.confirmedDate, soughtPatient.deceasedDate);
        }
        else
        {
            daysWithIllness = -1;
        }
        patientPrintSHOW(soughtPatient, daysWithIllness);
    }
    else
    {
        printf("Patient not found. Please enter a valid ID!\n");
        return OPERATION_FAILURE;
    }
    return OPERATION_SUCCESS;
}

int top5(PtList patientsList)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    int sizeAllPatientsList = 0;
    listSize(patientsList, &sizeAllPatientsList);

    int sizeReleasedList = 0;
    int releasedListInitialCapacity = calculateReleasedByAgeRange(patientsList, 0, 152); //Allot enough capacity to fit every released patient existent in the list

    PtList patientsReleasedList = listCreate(releasedListInitialCapacity);
    if (patientsReleasedList == NULL)
        return OPERATION_FAILURE;

    filterListByReleased(patientsList, sizeAllPatientsList, &patientsReleasedList, &sizeReleasedList);

    TopFiveStats topFiveStatsArray[sizeReleasedList]; //To store the elements so the sorting can be more easily done while at the same time, retaining access to the data type TopFiveStats.
    fillTopFiveArray(patientsReleasedList, topFiveStatsArray, sizeReleasedList);

    sortTopFiveByDaysToRecover(topFiveStatsArray, sizeReleasedList);
    sortTopFiveByAgeTie(topFiveStatsArray, sizeReleasedList);

    /*
    *The patients are in the filtered list, their stats are in the array. By combining the index of the array of stats with the underlying logic of getPatientByID, we get the final output.
    *getPatientByID will use the ID stored in the stats array to fetch the patient to be shown, which is then stored in releasedPatient by reference.
    *Afterwards, we show the patient.
    */
    printf("\n");
    ListElem releasedPatient;
    int patientsToDisplay = 5; //Change this value to show more patients.
    for (int i = 0; i < patientsToDisplay; i++)
    {
        if (getPatientByID(patientsReleasedList, topFiveStatsArray[i].patientID, &releasedPatient))
        {
            patientPrintSHOW(releasedPatient, topFiveStatsArray[i].daysWithIllness);
            printf("\n");
        }
    }
    //Dealloc the list we used to filter.
    listDestroy(&patientsReleasedList);
    return OPERATION_SUCCESS;
}

int oldest(PtList patientsList)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    int sizeOfList = 0;
    listSize(patientsList, &sizeOfList);
    ListElem patient;

    int earliestMaleYear = 0, earliestFemaleYear = 0;

    calculateEarliestBirthYearBySex(patientsList, &earliestMaleYear, &earliestFemaleYear);

    printf("\nFEMALE:\n");
    for (int i = 0; i < sizeOfList; i++)
    {
        listGet(patientsList, i, &patient);

        if (strcmp(patient.sex, "female") == 0)
        {
            if (patient.birthYear == earliestFemaleYear)
            {
                patientPrintOLDEST(patient);
            }
        }
    }

    printf("\nMALE:\n");
    for (int i = 0; i < sizeOfList; i++)
    {
        listGet(patientsList, i, &patient);

        if (strcmp(patient.sex, "male") == 0)
        {
            if (patient.birthYear == earliestMaleYear)
            {
                patientPrintOLDEST(patient);
            }
        }
    }
    return OPERATION_SUCCESS;
}

int growth(PtList patientsList, Date date)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    int prevDateDeaths = 0;
    int currentDeaths = 0;
    Date previousDate = dateCreate(date.day - 1, date.month, date.year);
    deathsPreviousToCurrentDay(patientsList, date, previousDate, &prevDateDeaths, &currentDeaths);
    if (prevDateDeaths < 1 || currentDeaths < 1)
    {
        printf("\nThere is no record for date <");
        datePrint(date);
        printf(">");
        return OPERATION_FAILURE;
    }
    int prevDateIsolated = 0;
    int currentIsolated = 0;
    isolatedPreviousToCurrentDay(patientsList, date, previousDate, &prevDateIsolated, &currentIsolated);
    if (prevDateIsolated < 1 || currentIsolated < 1)
    {
        printf("\nThere is no record for date <");
        datePrint(date);
        printf(">");
        return OPERATION_FAILURE;
    }

    printf("\nDate:<");
    datePrint(previousDate);
    printf(">\nNumber of dead: %d", prevDateDeaths);
    printf("\nNumber of isolated: %d", prevDateIsolated);
    printf("\n\n");

    printf("Date:<");
    datePrint(date);
    printf(">\nNumber of dead: %d", currentDeaths);
    printf("\nNumber of isolated: %d", currentIsolated);

    printf("\n");
    double rateDeaths = ((double)(currentDeaths - prevDateDeaths) / (double)prevDateDeaths) * 100;
    double rateInfected = ((double)(currentIsolated - prevDateIsolated) / (double)prevDateIsolated) * 100;
    printf("\nRate of new infected: %.0lf%%", rateInfected > 0 ? rateInfected : 0);
    printf("\nRate of new dead: %.0lf%%", rateDeaths > 0 ? rateDeaths : 0);
    printf("\n");

    return OPERATION_SUCCESS;
}

int matrix(PtList patientsList)
{
    if (patientsList == NULL)
        return OPERATION_FAILURE;

    int mat[6][3] = {
        {calculateIsolatedByAgeRange(patientsList, 0, 15), calculateDeceasedByAgeRange(patientsList, 0, 15), calculateReleasedByAgeRange(patientsList, 0, 15)},
        {calculateIsolatedByAgeRange(patientsList, 16, 30), calculateDeceasedByAgeRange(patientsList, 16, 30), calculateReleasedByAgeRange(patientsList, 16, 30)},
        {calculateIsolatedByAgeRange(patientsList, 31, 45), calculateDeceasedByAgeRange(patientsList, 31, 45), calculateReleasedByAgeRange(patientsList, 31, 45)},
        {calculateIsolatedByAgeRange(patientsList, 46, 60), calculateDeceasedByAgeRange(patientsList, 46, 60), calculateReleasedByAgeRange(patientsList, 46, 60)},
        {calculateIsolatedByAgeRange(patientsList, 61, 75), calculateDeceasedByAgeRange(patientsList, 61, 75), calculateReleasedByAgeRange(patientsList, 61, 75)},
        {calculateIsolatedByAgeRange(patientsList, 76, 152), calculateDeceasedByAgeRange(patientsList, 76, 152), calculateReleasedByAgeRange(patientsList, 76, 152)},
    };

    printf("\n\t|  %s |  %s |  %s |", "Isol", "Dcsd", "Rlsd");
    printf("\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%s ", i == 0 ? "[0-15]\t|" : i == 1 ? "[16-30]\t|" : i == 2 ? "[31-45]\t|" : i == 3 ? "[46-30]\t|" : i == 4 ? "[61-75]\t|" : "[76...[\t|");
        for (int j = 0; j < 3; j++)
        {
            printf("%5d\t|", mat[i][j]);
        }
        printf("\n");
    }

    return OPERATION_SUCCESS;
}
