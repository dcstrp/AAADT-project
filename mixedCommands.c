/**
 * @file mixedCommands.c
 * @author Pedro Vitória
 * @brief Provides implementations for all complex calculation commands.
 */

#include "mixedCommands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int regions(PtList patientsList, PtMap regionsMap)
{
    if (patientsList == NULL || regionsMap == NULL)
        return OPERATION_FAILURE;

    int sizeOfRegionsMap = 0;
    mapSize(regionsMap, &sizeOfRegionsMap);

    PtMap mapOfRegionsStillInfected = mapCreate(sizeOfRegionsMap);
    fillMapOfRegionsStillInfected(patientsList, regionsMap, mapOfRegionsStillInfected);

    int sizeOfMapOfStillInfected = 0;
    mapSize(mapOfRegionsStillInfected, &sizeOfMapOfStillInfected);

    MapValue *values = mapValues(mapOfRegionsStillInfected);

    for (int i = 0; i < sizeOfMapOfStillInfected; i++)
    {
        mapValuePrint(values[i]);
        printf("\n");
    }

    free(values);
    mapDestroy(&mapOfRegionsStillInfected);
    return OPERATION_SUCCESS;
}

int report(PtList patientsList, PtMap regionsMap)
{
    if (patientsList == NULL || regionsMap == NULL)
    {
        return OPERATION_FAILURE;
    }

    FILE *reportFile = NULL;
    reportFile = fopen("report.txt", "w");

    if (reportFile == NULL)
    {
        return OPERATION_FAILURE;
    }

    double regionLethality = 0;
    double regionIncidentRate = 0;
    double regionMortalityRate = 0;

    double countryLethality = 0;
    double countryIncidentRate = 0;
    double countryMortalityRate = 0;

    int sizeMap = 0;
    int sizeList = 0;

    mapSize(regionsMap, &sizeMap);
    listSize(patientsList, &sizeList);

    bool countryHasPopulation = calculateCountryStatistics(patientsList, regionsMap, "Korea", &countryLethality, &countryIncidentRate, &countryMortalityRate, sizeList, sizeMap);
    if (!countryHasPopulation)
    {
        fprintf(reportFile, "%s unknown (no population data)", "Korea");
        fprintf(reportFile, "\n\n");
    }
    else
    {
        fprintf(reportFile, "%s Mortality: %.3lf%% Incident Rate: %.3lf%% Lethality: %.3lf%%", "Korea", countryMortalityRate, countryIncidentRate, countryLethality);
        fprintf(reportFile, "\n\n");
    }

    MapValue *values = mapValues(regionsMap);

    for (int i = 0; i < sizeMap; i++)
    {
        if (!(strcmp(values[i].name, "South Korea") == 0))
        {
            bool hasPopulation = calculateRegionStatistics(patientsList, regionsMap, values[i].name, &regionLethality, &regionIncidentRate, &regionMortalityRate, sizeList, sizeMap);
            if (!hasPopulation)
            {
                fprintf(reportFile, "%s unknown (no population data)", values[i].name);
            }
            else
            {
                fprintf(reportFile, "%s Mortality: %.3lf%% Incident Rate: %.3lf%% Lethality: %.3lf%%", values[i].name, regionMortalityRate, regionIncidentRate, regionLethality);
            }
            fprintf(reportFile, "\n");
        }
    }

    fclose(reportFile);
    free(values);
    return OPERATION_SUCCESS;
}