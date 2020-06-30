/**
 * @file main.c
 * @author Pedro Vitória
 * @brief The program's main entry point.<br><br>This program consists in a set of helpful functionalities that the user can use to import, normalize and classify data related to the incidence of COVID-19 in a given country.
 * These functionalities are represented in the form of several different commands which the user can choose from by interacting with the underlying command interpreter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "regionCommands.h"
#include "patientCommands.h"
#include "mixedCommands.h"

typedef char String[255];

/**
 * @brief Checks if two given strings are equal, ignoring their capitalization.
 * 
 * @param str1 [in] The first string.
 * @param str2 [in] The second string.
 * @return 1 if the strings are equal or,
 * @return 0 if the strings are not equal.
 */
int equalsStringIgnoreCase(char str1[], char str2[]);
/**
 * @brief Prints a menu containing an assortment of different commands for the user to choose from.
 * 
 */
void printCommandsMenu();
/**
 * @brief Tests the creation and printing of an instance of Date.
 * 
 */
void testDate();
/**
 * @brief Tests the creation and printing of an instance of Patient.
 * 
 */
void testPatient();
/**
 * @brief Tests the creation and printing of an instance of Region.
 * 
 */
void testRegion();
/*
* <br> This program consists in a set of helpful functionalities that the user can use to import, normalize and classify data related to the incidence of COVID-19 in a given country.
* <br> These functionalities are represented in the form of several different commands which the user can choose from by interacting with the underlying command interpreter.
*/
int main(int argc, char **argv)
{
	PtList patientsList = NULL;
	PtMap regionsMap = NULL;

	Date mostRecentConfirmedDate = dateCreate(11, 11, 1111); //Default date value, will be changed after importing patients.

	String fileName;
	String command;

	int quit = 0;
	int numberOfPatientsReadFromFile = 0;
	int numberOfRegionsReadFromFile = 0;

	setlocale(LC_ALL, "PT");
	while (!quit)
	{
		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT"))
		{
			quit = 1;
		}
		else if (equalsStringIgnoreCase(command, "LOADP"))
		{
			printf("Insert filename> ");
			fgets(fileName, sizeof(fileName), stdin);
			fileName[strlen(fileName) - 1] = '\0';

			int error_code = importPatientsFromFile(fileName, &patientsList, &numberOfPatientsReadFromFile, &mostRecentConfirmedDate);
			if (!listIsEmpty(patientsList) && error_code == FILE_OK)
			{
				printf("\n%d patients were read from %s\n", numberOfPatientsReadFromFile, fileName);
			}
		}
		else if (equalsStringIgnoreCase(command, "LOADR"))
		{
			printf("Insert filename> ");
			fgets(fileName, sizeof(fileName), stdin);
			fileName[strlen(fileName) - 1] = '\0';

			int error_code = importRegionsFromFile(fileName, &regionsMap, &numberOfRegionsReadFromFile);

			if (!mapIsEmpty(regionsMap) && error_code == FILE_OK)
			{
				printf("\n%d regions were read from %s\n", numberOfRegionsReadFromFile, fileName);
			}
		}
		else if (equalsStringIgnoreCase(command, "CLEAR"))
		{
			mapClear(regionsMap);
			listClear(patientsList);
			printf("\n%d region records deleted.", numberOfRegionsReadFromFile);
			printf("\n%d patient records deleted.\n", numberOfPatientsReadFromFile);
			numberOfPatientsReadFromFile = 0; //to reset the number of patients read from the file variable after clearing
			numberOfRegionsReadFromFile = 0;  //same thing as above, but for the regions
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE"))
		{
			if (!listIsEmpty(patientsList))
			{
				int error_code = average(patientsList);

				if (error_code == OPERATION_FAILURE)
				{
					printf("\nOperation failure: Unable to show averages. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW"))
		{
			if (!listIsEmpty(patientsList))
			{
				long int patientID = 0;
				printf("Insert an ID\nFOLLOW> ");
				scanf("%ld", &patientID);
				getchar();
				printf("\nFollowing Patient : ");
				int error_code = follow(patientsList, patientID);

				if (error_code == OPERATION_FAILURE)
				{
					printf("\nOperation failure: Unable to show contamination sequence. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "SEX"))
		{
			if (!listIsEmpty(patientsList))
			{
				int error_code = sex(patientsList);

				if (error_code == OPERATION_FAILURE)
				{
					printf("\nOperation failure: Unable to show sex percentages. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "SHOW"))
		{
			if (!listIsEmpty(patientsList))
			{
				long int idOfPatientToShow = 0;

				printf("Insert an ID to show the patient\nSHOW> ");
				scanf("%ld", &idOfPatientToShow);
				getchar();
				printf("\n");
				int error_code = show(patientsList, idOfPatientToShow, mostRecentConfirmedDate);

				if (error_code == OPERATION_FAILURE)
				{
					printf("Operation failure: Unable to show patient. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "TOP5"))
		{
			if (!listIsEmpty(patientsList))
			{
				int error_code = top5(patientsList);

				if (error_code == OPERATION_FAILURE)
				{
					printf("\nOperation failure. Unable to show top 5. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "OLDEST"))
		{
			if (!listIsEmpty(patientsList))
			{
				int error_code = oldest(patientsList);

				if (error_code == OPERATION_FAILURE)
				{
					printf("\nOperation failure: Unable to show oldest patients. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "GROWTH"))
		{
			if (!listIsEmpty(patientsList))
			{
				String growthDate;

				printf("Please insert a date to show the growth rate (DD/MM/YYYY)\nGROWTH> ");
				fgets(growthDate, sizeof(growthDate), stdin);
				growthDate[strlen(growthDate) - 1] = '\0';

				int error_code = growth(patientsList, stringToDate(growthDate));

				if (error_code == OPERATION_FAILURE)
				{
					printf("\nOperation failure: Unable to show growth. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "MATRIX"))
		{
			if (!listIsEmpty(patientsList))
			{
				int error_code = matrix(patientsList);

				if (error_code == OPERATION_FAILURE)
				{
					printf("\nOperation failure: Unable to show matrix. Please try again!\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "REGIONS"))
		{
			if (listIsEmpty(patientsList) && mapIsEmpty(regionsMap))
			{
				printf("\nNo records were found! Please make sure you've correctly imported both the patients' and the regions' files before proceeding.\n");
			}
			else if (!listIsEmpty(patientsList))
			{
				if (!mapIsEmpty(regionsMap))
				{
					int error_code = regions(patientsList, regionsMap);

					if (error_code == OPERATION_FAILURE)
					{
						printf("\nOperation failure: Unable to show list of infected regions. Please try again!\n");
					}
				}
				else
				{
					printf("\nNo region records were found! Please make sure you've correctly imported the regions' file before proceeding.\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "REPORT"))
		{
			if (listIsEmpty(patientsList) && mapIsEmpty(regionsMap))
			{
				printf("\nNo records were found to create the report from! Please make sure you've correctly imported both the patients' and the regions' files before proceeding.\n");
			}
			else if (!listIsEmpty(patientsList))
			{
				if (!mapIsEmpty(regionsMap))
				{
					int error_code = report(patientsList, regionsMap);

					if (error_code == OPERATION_SUCCESS)
					{
						printf("\nReport created\n");
					}
					else
					{
						printf("\nReport not created\n");
					}
				}
				else
				{
					printf("\nNo region records were found! Please make sure you've correctly imported the regions' file before proceeding.\n");
				}
			}
			else
			{
				printf("\nNo patient records were found! Please make sure you've correctly imported the patients' file before proceeding.\n");
			}
		}
		else
		{
			printf("%s : Command not found.\n", command);
		}
	}

	listDestroy(&patientsList);
	mapDestroy(&regionsMap);
	printf("\nThank you for using the program. See you next time!\n\n");

	return (EXIT_SUCCESS);
}
int equalsStringIgnoreCase(char str1[], char str2[])
{
	return (strcasecmp(str1, str2) == 0);
}
void printCommandsMenu()
{
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOADP, LOADR, CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, GROWTH, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORT)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
void testDate()
{
	printf("===============================\n");
	printf("Create and print a test date");
	Date date = dateCreate(27, 05, 2020);
	printf("\n\n");
	datePrint(date);
	printf("\n===============================");
}
void testPatient()
{
	printf("===============================\n");
	printf("Create and print a test patient\n");
	Date date1 = dateCreate(11, 11, 1995);
	Date date2 = dateCreate(12, 12, 1996);
	Date date3 = dateCreate(14, 5, 1987);
	Patient patient = patientCreate(123456789, "Male", 1995, "Portugal", "Setúbal", "Physical Contact", 45678913, date3, date2, date1, "Dead");
	patientFullPrint(patient);
	printf("\n===============================");
}
void testRegion()
{
	printf("===============================\n");
	printf("Create and print a test region\n");
	Region region = regionCreate("Region name goes here!", "Capital of the region goes here!", 12345, 345.52);
	regionPrint(region);
	printf("===============================");
}