/**
 * @file region.c
 * @author Pedro Vitória
 * @brief Provides implementations for all operations related to the <b><i>Region</i></b> data type
 */

#include "region.h"
#include <string.h>
#include <stdio.h>

Region regionCreate(char *name, char *capital, int population, float area)
{
    Region region;
    strcpy(region.name, name);
    strcpy(region.capital, capital);
    region.population = population;
    region.area = area;
    return region;
}

void regionPrint(Region region)
{
    printf("\nRegion: %s\nCapital: %s\nPopulation: %d\nArea: %.3f km2\n",
           region.name, region.capital, region.population, region.area);
}
