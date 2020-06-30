/**
 * @file topfivestats.c
 * @author Pedro Vitória
 * @brief Provides implentations for all operations related to the <b><i>TopFiveStats</i></b> data type
 */

#include <stdio.h>
#include "topfivestats.h"
#include "patientUtils.h"

TopFiveStats topFiveStatsCreate(int age, int daysWithIllness, long int patientID)
{
    TopFiveStats stats;
    stats.age = age;
    stats.daysWithIllness = daysWithIllness;
    stats.patientID = patientID;
    return stats;
}

void topFiveStatsPrint(TopFiveStats stats)
{
    printf("\nPatient ID: %ld\n", stats.patientID);
    if (stats.age != -1)
    {
        printf("Age: %d\n", stats.age);
    }
    else
    {
        printf("Age: unknown\n");
    }

    printf("Number of days taken to recover: %d\n", stats.daysWithIllness);
}

void sortTopFiveByDaysToRecover(TopFiveStats arr[], int sizeArr)
{
    TopFiveStats temp;
    for (int i = 0; i < sizeArr; i++)
    {
        for (int j = 0; j < sizeArr - i - 1; j++)
        {
            if (arr[j].daysWithIllness < arr[j + 1].daysWithIllness)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortTopFiveByAgeTie(TopFiveStats arr[], int sizeArr)
{
    TopFiveStats temp;
    for (int i = 0; i < sizeArr; i++)
    {
        for (int j = 0; j < sizeArr - i - 1; j++)
        {
            if (arr[j].daysWithIllness == arr[j + 1].daysWithIllness && arr[j].age < arr[j + 1].age)
            {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void fillTopFiveArray(PtList patientsList, TopFiveStats arr[], int sizeArr)
{
    TopFiveStats patientStats;
    for (int i = 0; i < sizeArr; i++)
    {
        ListElem patient;
        listGet(patientsList, i, &patient);

        int age = patient.birthYear != -1 ? 2020 - patient.birthYear : -1;
        int daysWithIllness = getDifferenceBetweenDates(patient.confirmedDate, patient.releasedDate);
        patientStats = topFiveStatsCreate(age, daysWithIllness, patient.id);

        arr[i] = patientStats;
    }
}
