/**
 * @file mapSortedArrayList.c
 * 
 * @brief Provides an implementation of the ADT Map with an array list
 * as the underlying data structure.
 * Adapted to implement the Sorted ArrayList data structure.
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct keyValue
{
	MapKey key;
	MapValue value;
} KeyValue;

typedef struct mapImpl
{
	KeyValue *elements;
	int capacity;
	int size;
} MapImpl;

/**
 * @brief Auxiliary function to find the index of a specific key.
 * 
 * @param map [in] pointer to the map
 * @param key [in] key to find
 * @param start [in] beginning of the map
 * @param end [in] end of the map
 * @return The key's index
 */
int findIndexOfKeyBinary(PtMap map, MapKey key, int start, int end)
{
	int middle = (start + end) / 2;

	if (start > end)
		return -1;

	if (mapKeyCompare(map->elements[middle].key, key) == 0)
		return middle;

    if (mapKeyCompare(map->elements[middle].key, key) > 0)
		return findIndexOfKeyBinary(map, key, start, middle - 1);
	else
		return findIndexOfKeyBinary(map, key, middle + 1, end);
}

/**
 * @brief Auxiliary function to find the index of a specific key. 
 * 
 * Keys are compared by using mapKeyEquals function.
 * 
 * @param map [in] pointer to the map
 * @param key [in] key to find
 * @return index of 'elements' containing 'key', or
 * @return -1 if no index contains 'key'
 */
int findIndexOfKey(PtMap map, MapKey key)
{
	if (map == NULL)
		return -1;

	return findIndexOfKeyBinary(map, key, 0, map->size);
}

static bool ensureCapacity(PtMap map)
{
	if (map->size == map->capacity)
	{
		int newCapacity = map->capacity * 2;
		KeyValue *newArray = (KeyValue *)realloc(map->elements,
												 newCapacity * sizeof(KeyValue));

		if (newArray == NULL)
			return false;

		map->elements = newArray;
		map->capacity = newCapacity;
	}

	return true;
}

PtMap mapCreate(unsigned int initialCapacity)
{
	PtMap newMap = (PtMap)malloc(sizeof(MapImpl));
	if (newMap == NULL)
		return NULL;

	newMap->elements = (KeyValue *)calloc(initialCapacity, sizeof(KeyValue));
	if (newMap->elements == NULL)
	{
		free(newMap);
		return NULL;
	}

	newMap->size = 0;
	newMap->capacity = initialCapacity;

	return newMap;
}

int mapDestroy(PtMap *ptMap)
{
	PtMap map = *ptMap;

	if (map == NULL)
		return MAP_NULL;

	free(map->elements);
	free(map);

	*ptMap = NULL;

	return MAP_OK;
}

int mapSize(PtMap map, int *ptSize)
{
	if (map == NULL)
		return MAP_NULL;
	*ptSize = map->size;
	return MAP_OK;
}

bool mapIsEmpty(PtMap map)
{
	if (map == NULL)
		return 1;
	return (map->size == 0);
}

int mapClear(PtMap map)
{
	if (map == NULL)
		return MAP_NULL;
	map->size = 0;
	return MAP_OK;
}

void mapPrint(PtMap map)
{
	if (map == NULL)
	{
		printf("(MAP NULL)\n");
	}
	else if (mapIsEmpty(map))
	{
		printf("(MAP EMPTY)\n");
	}
	else
	{
		for (int i = 0; i < map->size; i++)
		{	printf("\n");
			mapKeyPrint(map->elements[i].key);
			printf(":\n");
			mapValuePrint(map->elements[i].value);
		}
	}
}

int mapPut(PtMap map, MapKey key, MapValue value)
{
	if (map == NULL)
		return MAP_NULL;

	int index = findIndexOfKey(map, key);
	if (index != -1)
	{
		map->elements[index].value = value;
	}
	else
	{
		if (!ensureCapacity(map))
			return MAP_FULL;

		int indexInsert = map->size;

		for (int i = 0; i < map->size; i++)
		{
			if (mapKeyCompare(map->elements[i].key, key) > 0)
			{
				indexInsert = i;
				break;
			}
		}
		for (int i = map->size; i > indexInsert; i--)
		{
			map->elements[i] = map->elements[i - 1];
		}

		map->elements[indexInsert].key = key;
		map->elements[indexInsert].value = value;
		map->size++;

		return MAP_OK;
	}
}

int mapRemove(PtMap map, MapKey key, MapValue *ptValue)
{
	if (map == NULL)
		return MAP_NULL;
	if (map->size == 0)
		return MAP_EMPTY;

	int index = findIndexOfKey(map, key);
	if (index == -1)
		return MAP_UNKNOWN_KEY;

	*ptValue = map->elements[index].value;

	for (int i = index; i < map->size - 1; i++)
	{
		map->elements[i] = map->elements[i + 1];
	}

	map->size--;

	return MAP_OK;
}

bool mapContains(PtMap map, MapKey key)
{
	if (map == NULL)
		return 0;

	return findIndexOfKey(map, key) != -1;
}

int mapGet(PtMap map, MapKey key, MapValue *ptValue)
{
	if (map == NULL)
		return MAP_NULL;
	if (map->size == 0)
		return MAP_EMPTY;

	int index = findIndexOfKey(map, key);
	if (index == -1)
		return MAP_UNKNOWN_KEY;

	*ptValue = map->elements[index].value;

	return MAP_OK;
}

MapKey *mapKeys(PtMap map)
{
	if (map == NULL || map->size == 0)
		return NULL;

	MapKey *keys = (MapKey *)calloc(map->size, sizeof(MapKey));

	for (int i = 0; i < map->size; i++)
	{
		keys[i] = map->elements[i].key;
	}

	return keys;
}

MapValue *mapValues(PtMap map)
{
	if (map == NULL || map->size == 0)
		return NULL;

	MapValue *values = (MapValue *)calloc(map->size, sizeof(MapValue));

	for (int i = 0; i < map->size; i++)
	{
		values[i] = map->elements[i].value;
	}

	return values;
}