/**
 * @file mixedCommands.h
 * @author Pedro Vitória
 * @brief Defines the commands that require both a list of patients and a map of regions.
 * Used for the commands that provide calculations for complex indicators.
 */

#pragma once

#include "utils.h"
#define OPERATION_SUCCESS 10
#define OPERATION_FAILURE 11

/**
 * @brief Shows the regions that still have active COVID-19 cases.
 * 
 * @param patientsList [in] A list of patients. 
 * It will be from this list that we retrieve the information about which patients are still sick.
 * @param regionsMap [in] A map of regions. 
 * @return OPERATION_SUCCESS If the regions are able to be shown
 * @return OPERATION_FAILURE If the either the list or the map are NULL
 */
int regions(PtList patientsList, PtMap regionsMap);

/**
 * @brief Creates a report containing information about the following percentages: Mortality | Incidence Rate | Lethality.
 * 
 * @param patientsList [in] A list of patients.
 * @param regionsMap [in] A map of regions.p 
 * @return OPERATION_SUCCESS If the file is sucessfully created with all the data in it
 * @return OPERATION_FAILURE If the either the list or the map are NULL or the if the file was not successfully created
 */
int report(PtList patientsList, PtMap regionsMap);