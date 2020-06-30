/**
 * @file topfivestats.h
 * @author Pedro Vitória
 * @brief Defines the data type <b><i>TopFiveStats</i></b> and related operations. 
 * This data type's main use is in helping with calculations related to the <b>TOP5</b> command.
 */

#pragma once
#include "list.h"

/**
 * @brief Represents an instance of TopFiveStats
 * 
 */
typedef struct topfivestats
{
    int age;
    int daysWithIllness;
    long int patientID;

} TopFiveStats;

/**
 * @brief Creates and returns a new instance of TopFiveStats.
 * 
 * @param age [in] The age of the patient
 * @param daysWithIllness [in] The days it took the patient to recover. Also referred to as number of days with illness
 * @param patientID [in] The patient's ID
 * @return The newly created instance
 */
TopFiveStats topFiveStatsCreate(int age, int daysWithIllness, long int patientID);

/**
 * @brief Prints a textual representation of an instance of TopFiveStats
 * 
 * @param stats [in] The instance to be printed
 */
void topFiveStatsPrint(TopFiveStats stats);

/**
 * @brief Sorts the array of stats in descending order from highest days infected to lowest. (Also called number of days with illness)
 * 
 * @param arr [in] The array to be sorted
 * @param sizeArr [in] The size of the array
 */
void sortTopFiveByDaysToRecover(TopFiveStats arr[], int sizeArr);

/**
 * @brief Sorts the array of stats by age if there's a tie between the patients' number of days with illness
 * 
 * @param arr [in] The array to be sorted
 * @param sizeArr [in] The size of the array
 */
void sortTopFiveByAgeTie(TopFiveStats arr[], int sizeArr);

/**
 * @brief Fills an array with <b><i>TopFiveStats</i></b> instances where each instance represents stats of each patient in a list of patients
 * 
 * @param patientsList [in] A list of patients
 * @param arr [out] The array to be filled
 * @param sizeArr [in] The size of the array 
 */
void fillTopFiveArray(PtList patientsList, TopFiveStats arr[], int sizeArr);