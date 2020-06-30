/**
 * @file regionCommands.h
 * @author Pedro Vitória
 * @brief Defines commands that are only associated with region-related operations
 */

#pragma once

#define FILE_OK 0
#define FILE_NOT_FOUND 1

#include "utils.h"

/**
 * @brief Imports the contents of a file containing information about a certain amount of regions and stores it on a Map.
 * 
 * @param filename [in] The name of the file
 * @param map [in] The instance of Map which will store the imported information
 * @param numberOfRegionsReadFromFile [out] The number of regions read from the imported file
 * @return FILE_OK if file is sucessfuly imported
 * @return FILE_NOT_FOUND if the given filename isn't found or able to be created
 * @return MAP_NULL If the map creation is not sucessful
 * @return MAP_FULL If the MAP has no more capacity available
 * @return MAP_NO_MEMORY If insufficient memory for allocation
 */
int importRegionsFromFile(char *filename, PtMap *map, int *numberOfRegionsReadFromFile);



