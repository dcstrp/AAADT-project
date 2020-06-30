/**
 * @file regionCommands.c
 * @author Pedro Vitória
 * @brief Provides implementations for all region-related commands. 
 */

#include "regionCommands.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int importRegionsFromFile(char *filename, PtMap *map, int *numberOfRegionsReadFromFile)
{
    FILE *f = NULL;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("File not found (%s)\n", filename);
        return FILE_NOT_FOUND;
    }

    char nextline[1024];
    int countRegions = 0;
    bool firstLine = true;

    *map = mapCreate(18);
    if (map == NULL)
        return MAP_NULL;

    while (fgets(nextline, sizeof(nextline), f))
    {
        if (strlen(nextline) < 1)
            continue;

        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        char **tokens = split(nextline, 4, ";");

        replaceCharacter(tokens[2], ',', '.');

        int index = 0;
        char *population = tokens[3];
        for (int i = 0; i < strlen(population); i++)
        {
            if (population[i] == ',')
            {
                index = i;
                for (int j = index; j < strlen(population); j++)
                {
                    population[j] = population[j + 1];
                }
            }
        }

        MapValue region = regionCreate(tokens[0], tokens[1], atoi(population), atof(tokens[2]));
        MapKey regionAsKey = mapKeyCreate(region.name);

        int error_code = mapPut(*map, regionAsKey, region);
        free(tokens);

        if (error_code == MAP_FULL || error_code == MAP_UNKNOWN_KEY || error_code == MAP_NO_MEMORY || error_code == MAP_NULL)
        {
            printf("An error ocurred.... Please try again... \n");
            return error_code;
        }
        countRegions++;
    }
    *numberOfRegionsReadFromFile = countRegions;
    fclose(f);
    return FILE_OK;
}
