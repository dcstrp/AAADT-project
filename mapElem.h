/**
 * @file mapElem.h
 * @brief Defines the types MapKey and MapValue.
 * 
 * The MapKey is an alias to the type of keys 
 * held by an instance of the ADT Map (PtMap).
 * 
 * The MapValue is an alias to the type of values 
 * held by an instance of the ADT Map (PtMap).
 *  
 * These aliases must be changed according to the use-case.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#pragma once

#include <stdbool.h>
#include "region.h"
/** Key type definition. Change according to the use-case. */
typedef KeyString MapKey;

/** Value type definition. Change according to the use-case. */
typedef Region MapValue;

/**
 * @brief Prints a key.
 * 
 * 
 * @param key [in] key to print
 */
void mapKeyPrint(MapKey key);

/**
 * @brief Prints a value.
 * 
 * 
 * @param value [in] value to print
 */
void mapValuePrint(MapValue value);

/**
 * @brief Compares two keys for equality.
 * 
 * This function is used by the ADT Map to perform
 * a key-based access to the underlying data.
 * 
 * @param key1 [in] a key
 * @param key2 [in] another key
 * @return 'true' if keys match, or
 * @return 'false' if keys don't match. 
 */
bool mapKeyEquals(MapKey key1, MapKey key2);

/**
 * @brief Compares two keys
 * 
 * @param key1 [in] a key
 * @param key2 [in] another key
 * @return 0 if keys match, or
 * @return > 0 if key1 larger in value than key2, or
 * @return < 0 if key1 smaller in value than key2
 */
int mapKeyCompare(MapKey key1, MapKey key2);


