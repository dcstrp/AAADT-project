/**
 * @file patient.c
 * @author Pedro Vitória
 * @brief Provides implementations for all operations related to the <b><i>Patient</i></b> data type
 */

#include "patient.h"
#include <stdio.h>
#include <string.h>

Patient patientCreate(long int id, char *sex, int birthYear, char *country, char *region, char *infectionReason,
                      long int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char *status)
{
    Patient patient;
    patient.id = id;
    patient.birthYear = birthYear;
    patient.infectedBy = infectedBy;
    patient.confirmedDate = confirmedDate;
    patient.releasedDate = releasedDate;
    patient.deceasedDate = deceasedDate;
    strcpy(patient.country, country);
    strcpy(patient.sex, sex);
    strcpy(patient.status, status);
    strcpy(patient.region, region);
    strcpy(patient.infectionReason, infectionReason);

    return patient;
}

void patientFullPrint(Patient patient)
{
    printf("\n=========================================");
    printf("\nID: %ld \nBirth year: %d \nSex: %s \nCountry: %s \nRegion: %s \nStatus: %s \nInfection reason: %s\nInfected by: %ld \n",
           patient.id, patient.birthYear, patient.sex, patient.country, patient.region, patient.status, patient.infectionReason, patient.infectedBy);
    printf("Confirmed date: ");
    datePrint(patient.confirmedDate);
    printf("\nReleased date: ");
    datePrint(patient.releasedDate);
    printf("\nDeceased date: ");
    datePrint(patient.deceasedDate);
    printf("\n=========================================");
}

void patientPrintSHOW(Patient patient, int daysWithIllness)
{

    int age = patient.birthYear != -1 ? 2020 - patient.birthYear : -1;
    printf("ID: %ld\nSex: %s\n", patient.id, patient.sex);
    if (age != -1)
    {
        printf("AGE: %d\n", age);
    }
    else
    {
        printf("AGE: %s\n", "unknown");
    }

    printf("COUNTRY/REGION: %s/%s\nINFECTION REASON: %s\nSTATE: %s\n",
           patient.country, patient.region, strlen(patient.infectionReason) == 0 ? "unknown" : patient.infectionReason, patient.status);

    if (daysWithIllness != -1)
    {
        printf("NUMBER OF DAYS WITH ILLNESS: %d\n", daysWithIllness);
    }
    else
    {
        printf("NUMBER OF DAYS WITH ILLNESS: %s\n", "unknown");
    }
}

void patientPrintOLDEST(Patient patient)
{
    int age = (patient.birthYear != -1 ? 2020 - patient.birthYear : -1);
    printf("ID: %ld, Sex: %s, AGE: %d, COUNTRY/REGION: %s/%s,STATE: %s\n",
           patient.id, patient.sex, age, patient.country, patient.region, patient.status);
}
