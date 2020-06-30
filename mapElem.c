/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>
#include <string.h>
void mapKeyPrint(MapKey key)
{
	printf("%s", key.contents);
}

void mapValuePrint(MapValue value)
{
	regionPrint(value);
}

bool mapKeyEquals(MapKey key1, MapKey key2)
{
	return (strcmp(key1.contents, key2.contents) == 0);
}

int mapKeyCompare(MapKey key1, MapKey key2)
{
	return (strcmp(key1.contents, key2.contents));
}

KeyString mapKeyCreate(char *keyContents)
{
	KeyString key;
	strcpy(key.contents, keyContents);
	return key;
}