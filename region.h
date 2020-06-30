/**
 * @file region.h
 * @author Pedro Vitória
 * @brief Defines the data type <b><i>Region</i></b> and related operations. 
 */

#pragma once

/**
 * @brief Represents a region.
 * 
 */
typedef struct region
{
    char name[40];
    char capital[40];
    int population;
    float area;
} Region;

/**
 * @brief Represents the key type for the map of regions.
 * 
 */
typedef struct keyString
{
    char contents[255];
} KeyString;

/**
 * @brief Returns a newly created instance of Region.
 * 
 * @param name [in] The name of the region
 * @param capital [in] The region's capital
 * @param population [in] The region's population
 * @param area [in] The region's area in km2
 * @return Region The newly created region instance
 */
Region regionCreate(char *name, char *capital, int population, float area);

/**
 * @brief Prints a textual representation of a given region.
 * 
 * @param region [in] An instance of region
 */
void regionPrint(Region region);

/**
 * @brief Creates a new key for a given map of regions
 * 
 * @param keyContents [in] The string associated with the key
 * @return KeyString The newly created key
 */
KeyString mapKeyCreate(char *keyContents);



