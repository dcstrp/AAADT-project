/**
 * @file patientUtils.h
 * @author Pedro Vitória
 * @brief Defines a set of auxiliary functions that aid in the operations or calculations performed by commands related to patient data.
 */

#pragma once

#include "utils.h"

/**
 * @brief Searches for the index of a patient in the list of patients, returning it if found.
 * 
 * @param patientID [in] The patient ID to look for
 * @param startRank [in] The first index (rank) of the List
 * @param endRank [in] The last index (rank) of the List
 * @param patientsList [in] A list of patients
 * @return The index of the patient if sucessfully found, or 
 * @return -1 if not found
 */
int findPatientIndex(PtList patientsList, long int patientID, int startRank, int endRank);

/**
 * @brief Calculates and returns by reference the percentage of infected patients for each sex, including patients whose sex is unknown 
 * 
 * @param patientsList [in] A list of patients
 * @param malePercentage [out] The percentage pertaining to male patients, returned by reference
 * @param femalePercentage [out] The percentage pertaining to female patients, returned by reference
 * @param unknownPercentage [out] The percentage pertaining to patients for whom the sex is unknown, returned by reference
 */
void calculatePercentageOfInfectedPatientsBySex(PtList patientsList, double *malePercentage, double *femalePercentage, double *unknownPercentage);

/**
 * @brief Calculates and returns by reference the average age for isolated, deceased and released patients in a list of patients.
 * 
 * @param patientsList [in] A list of patients
 * @param averageIsolatedAge [out] The average age of isolated patients
 * @param averageDeceasedAge [out] The average age of deceased patients
 * @param averageReleasedAge [out] The average age of released patients
 */
void calculateAverageAgeByState(PtList patientsList, double *averageIsolatedAge, double *averageDeceasedAge, double *averageReleasedAge);

/**
 * @brief Searches for a patient via the supplied ID and if found, returns said patient by reference.
 * 
 * @param patientsList [in] A list of patients
 * @param patientID [in] The ID of the patient to be searched for
 * @param soughtPatient [out] The desired patient returned by reference if such a patient exists in the list.
 * @return true If the patient exists on the list
 * @return false If the patient does not exist on the list
 */
bool getPatientByID(PtList patientsList, long int patientID, Patient *soughtPatient);

/**
 * @brief Calculates the earliest birth year for both sexes in a list of patients.
 * 
 * @param patientsList [in] A list of patients
 * @param earliestMaleYear [out] The earliest year for the male sex
 * @param earliestFemaleYear [out] The earliest year for the female sex
 */
void calculateEarliestBirthYearBySex(PtList patientsList, int *earliestMaleYear, int *earliestFemaleYear);

/**
 * @brief Calculates the number of isolated patients in a given age range.
 * 
 * @param patientsList [in] A list of patients
 * @param rangeStart [in] Beginning of the age range
 * @param rangeEnd [in] Ending of the age range
 * @return The number of isolated patients
 */
int calculateIsolatedByAgeRange(PtList patientsList, int rangeStart, int rangeEnd);

/**
 * @brief Calculates the number of deceased patients in a given age range.
 * 
 * @param patientsList [in] A list of patients
 * @param rangeStart [in] Beginning of the age range
 * @param rangeEnd [in] Ending of the age range
 * @return The number of deceased patients
 */
int calculateDeceasedByAgeRange(PtList patientsList, int rangeStart, int rangeEnd);

/**
 * @brief Calculates the number of released patients in a given age range.
 * 
 * @param patientsList [in] A list of patients
 * @param rangeStart [in] Beginning of the age range
 * @param rangeEnd [in] Ending of the age range
 * @return The number of released patients
 */
int calculateReleasedByAgeRange(PtList patientsList, int rangeStart, int rangeEnd);

/**
 * @brief Retrieves the number of deaths with respect to the specified dates.
 * 
 * @param patientsList [in] A list of patients
 * @param currentDate [in] The current date
 * @param previousDate [in] The date before the current date
 * @param previousDeaths [out] The deaths with respect to the previous date
 * @param currentDeaths [out] The deaths with respect to the current date with the deaths of the previous date added as well
 */
void deathsPreviousToCurrentDay(PtList patientsList, Date currentDate, Date previousDate, int *previousDeaths, int *currentDeaths);

/**
 * @brief Retrieves the number of isolated patients with respect to the specified dates.
 * 
 * @param patientsList [in] A list of patients
 * @param currentDate [in] The current date
 * @param previousDate [in] The date before the current date
 * @param previousIsolated [out] The number of isolated patients with respect to the previous date
 * @param currentIsolated [out] The number of isolated patients only with respect to the current date
 */
void isolatedPreviousToCurrentDay(PtList patientsList, Date currentDate, Date previousDate, int *previousIsolated, int *currentIsolated);

/**
 * @brief Filters the main patients list onto a new list, where the new list will only contain patients who have been released
 * 
 * @param patientsList [in] The main patient list
 * @param sizeAllPatientsList [in] The size of the main patient list
 * @param patientsReleasedList [out] The newly filtered list containing only patients whose status is released
 * @param sizeReleasedList [out] The size of the filtered list
 */
void filterListByReleased(PtList patientsList, int sizeAllPatientsList, PtList *patientsReleasedList, int *sizeReleasedList);
