/**
 * @file patientCommands.h
 * @author Pedro Vitória
 * @brief Defines commands that are only associated with patient-related operations.
 */

#pragma once

#define FILE_OK 0
#define FILE_NOT_FOUND 1
#define OPERATION_SUCCESS 10
#define OPERATION_FAILURE 11

#include "list.h"
#include "patientUtils.h"

/**
 * @brief Imports the contents of a file containing information about a number of patients and stores it on a List
 * @param filename [in] The name of the file
 * @param list [in] The address of an instance of List which will store the imported information. Henceforth, this will be the list of patients
 * @param numberOfPatientsReadFromFile [out] The number of patiends read from the imported file
 * @param mostRecentConfirmedDate [out] The most recent confirmed date of COVID-19 contamination
 * @return FILE_OK if file is successfully imported
 * @return FILE_NOT_FOUND if the requested file to be opened is not found
 * @return LIST_NULL If the list is null
 * @return LIST_FULL If the list has no more capacity available
 * @return LIST_INVALID_RANK If the rank for an element's insertion is not valid
 * @return LIST_NO_MEMORY if insufficient memory for allocation
 */
int importPatientsFromFile(char *filename, PtList *list, int *numberOfPatientsReadFromFile, Date *mostRecentConfirmedDate);

/**
 * @brief Shows the following averages
 * <ul>
 * <li> Average age of isolated patients
 * <li> Average age of released patients
 * <li> Average age of deceased patients
 * </ul>
 * @param patientsList [in] A list of patients
 * @return OPERATION_SUCCESS If the averages are successfully calculated and shown
 * @return OPERATION_FAILURE If the list is NULL
 */
int average(PtList patientsList);

/**
 * @brief Tracks and shows the contamination sequence starting with a given patient
 * 
 * @param patientsList [in] A list of patients
 * @param patientID [in] The ID of the contamination sequence's initial patient
 * @return OPERATION_SUCCESS If the function is able to begin tracking the contamination sequence
 * @return OPERATION_FAILURE If the list is NULL
 */
int follow(PtList patientsList, long int patientID);

/**
 * @brief Shows the percentage of:
 * <ul>
 * <li> Male patients
 * <li> Female patients
 * <li> Patients for whom the sex is unknown
 * </ul>
 * @param patientsList [in] A list of patients. 
 * @return OPERATION_SUCCESS If the sex percentages are successfully calculated and shown
 * @return OPERATION_FAILURE If the list is NULL
 */
int sex(PtList patientsList);

/**
 * @brief Shows a patient's data according to their ID
 * 
 * @param patientsList [in] A list of patients
 * @param idOfPatientToShow [in] The patients ID
 * @param mostRecentConfirmedDate [in] The most recent confirmed date of infection
 * @return OPERATION_SUCCESS If the patient exists and is shown
 * @return OPERATION_FAILURE If the list is NULL or if the supplied ID does not exist in the list of patients
 */
int show(PtList patientsList, long int idOfPatientToShow, Date mostRecentConfirmedDate);

/**
 * @brief Shows, in descending order, the 5 patients that took the longest to recover 
 * 
 * @param patientsList [in] A list of patients
 * @return OPERATION_SUCCESS If the top 5 patients are successfully determined and shown
 * @return OPERATION_FAILURE If either the patient's list or the filtered list are NULL
 */
int top5(PtList patientsList);

/**
 * @brief Shows the oldest patients in a list of patients. <br>The patients are divided and shown by sex
 * 
 * @param patientsList [in] A list of patients
 * @return OPERATION_SUCCESS If the oldest patients are successfully determined and shown
 * @return OPERATION_FAILURE If the list is NULL
 */
int oldest(PtList patientsList);

/**
 * @brief Shows the growth rate of deaths and contaminations with regards to the previous date
 * 
 * @param patientsList [in] A list of patients
 * @param date [in] The current date. <br>The previous date to the current date is calculated implictly
 * @return OPERATION_SUCCESS If the growth rate is successfully determined and shown
 * @return OPERATION_FAILURE If the list is NULL or there are no records for the specified date
 */
int growth(PtList patientsList, Date date);

/**
 * @brief Creates and prints a 6x3 matrix containing information about isolated, deceased and released patients in several different age groups
 * 
 * @param patientsList [in] A list of patients
 * @return OPERATION_SUCCESS If the matrix is successfully assembled and shown
 * @return OPERATION_FAILURE If the list is NULL
 */
int matrix(PtList patientsList);
