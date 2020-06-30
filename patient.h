/**
 * @file patient.h
 * @author Pedro Vitória
 * @brief Defines the data type <b><i>Patient</i></b> and related operations. 
 */

#pragma once

#include "date.h"

/**
 * @brief Represents a patient.
 * 
 */
typedef struct patient
{
    long int id;
    char sex[10];
    int birthYear;
    char country[40];
    char region[40];
    char infectionReason[100];
    long int infectedBy;
    Date confirmedDate;
    Date releasedDate;
    Date deceasedDate;
    char status[10];
} Patient;

/**
 * @brief Returns a newly created instance of Patient.
 * 
 * @param id [in] The patient's ID.
 * @param sex [in] The patient's sex [male/female].
 * @param birthYear [in] The patient's birthyear (Numerical - YYYY).
 * @param country [in] The patient's country.
 * @param region [in] The patient's region.
 * @param infectionReason [in] The reason as to why the patient got infected.
 * @param infectedBy [in]  Who infected the patient.
 * @param confirmedDate [in] The date that represents when the patient was confirmed to be infected.
 * @param releasedDate [in] The date that represents when the patient was released from care.
 * @param deceasedDate [in] The date that represents when the patient died.
 * @param status [in] The patient's status.
 * @return The newly created patient instance.
 */
Patient patientCreate(long int id, char *sex, int birthYear, char *country, char *region, char *infectionReason,
                      long int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char *status);

/**
 * @brief Prints a textual representation of a given instance of Patient by printing all of the instance's fields.
 * 
 * @param patient [in] The instance of Patient to be printed.
 */
void patientFullPrint(Patient patient);

/**
 * @brief Prints a textual representation of a patient according to the fields that are meant to be shown when the "SHOW" command is selected.
 * <br>The fields are as follows:
 * <ul>
 * <li>ID
 * <li>SEX
 * <li>AGE
 * <li>COUNTRY/REGION
 * <li>INFECTION REASON
 * <li>STATE
 * <li>NUMBER OF DAYS WITH ILLNESS
 * </ul> 
 * @param patient [in] The instance of Patient to be printed.
 * @param daysWithIllness [in] The patient's number of days with illness.
 */
void patientPrintSHOW(Patient patient, int daysWithIllness);

/**
 * @brief Prints a textual representation of a patient according to the fields that are meant to be shown when the "OLDEST" command is selected.
 * <br>The fields are as follows:
 * <ul>
 * <li>ID
 * <li>SEX
 * <li>AGE
 * <li>COUNTRY/REGION
 * <li>STATE
 * </ul>
 * @param patient [in] The instance of Patient to be printed.
 */
void patientPrintOLDEST(Patient patient);