/*
Alejandro Barragan
CS2060
T/Th
This program
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <ctype.h>

// Global constants
#define SIZE 80


// Functions
void fgetsRemoveNewLine(char* string);
void adminSetUp(char* string, double* distance, double* cost);
bool getValidDouble(char* string, double* value);
char getValidChar(char* sizes);

const char *SIZE_LIST[4] = {"small", "medium", "large", "xtra-large"};

int main(void) {

	/*
	// Task 1 Code:
	char input[SIZE];
	char* inputPtr = input;
	puts("Enter your first and last name (80 Characters Max):");
	fgetsRemoveNewLine(inputPtr);

	// Task 2 Code:
	char orgName[SIZE];
	char* orgNamePtr = &orgName;
	double raceDistance = 0;
	double* raceDistancePtr = &raceDistance;
	double raceCost = 0;
	double* raceCostPtr = &raceCost;

	adminSetUp(orgNamePtr, raceDistancePtr, raceCostPtr);
	printf("%s\t%6.2lf Miles\t$%6.2lf\n", orgName, raceDistance, raceCost);
*/
	// Task 3 Code:
	
	
	puts("Select shirt size by entering the character shown (s)mall, (m)edium, (l)arge, (x)tra-large");
	
	getValidChar(SIZE_LIST);


}
/// <summary>
/// Function takes a string input and if there is a new line 
/// character entered, it will replace it with the null character
/// </summary>
void fgetsRemoveNewLine(char* string) {


	fgets(string, SIZE, stdin);
	int lastChar = strlen(string) - 1;
	if (string[lastChar] == '\n') {
		string[lastChar] = '\0';
	}

}

/// <summary>
/// Function takes in a org name, race distace and cost and using
/// pointers plugs them in to the addresses of the variables and 
/// pass values by reference
/// </summary>
void adminSetUp(char* string, double* distance, double* cost) {

	char raceDistance[SIZE];
	char raceCost[SIZE];

	puts("Enter org Name:");
	fgetsRemoveNewLine(string);

	bool validDistance = false;
	do {
		puts("Enter race distance:");
		fgetsRemoveNewLine(raceDistance);
		validDistance = getValidDouble(raceDistance, distance);
	} while (validDistance == false);

	bool validCost = false;
	do {
		puts("Enter race cost:");
		fgetsRemoveNewLine(raceCost);
		validCost = getValidDouble(raceCost, cost);
	} while (validCost == false);

}

/// <summary>
/// Function takes in a string, converts it into a number and determines 
/// whether it is a valid double or not
/// </summary>
bool getValidDouble(char* string, double* value) {

	char* end;
	double tempValue = strtod(string, &end);
	errno = 0;
	bool state = false;


	if (end == string) {
		puts("No number was entered, try again");
	}
	else if ('\0' != *end && '\n' != *end) {
		puts("Number was not read, try again");
	}

	else if (tempValue > DBL_MAX || tempValue < DBL_MIN) {
		puts("Value is not in double range, try again");
	}
	else {
		*value = tempValue;
		state = true;

	}
	return state;
}

/// <summary>
/// Function takes in a character and determines which size shirt is 
/// selected and if any of the correct characters are entered, it will 
/// prompt the user to try again until it is valid
/// </summary>
char getValidChar(char* sizes) {

	bool validChar = false;
	
	do {
		char shirtSize = getchar();
		for (size_t i = 0; i < 4; i++) {
			if (tolower(shirtSize) == &sizes) {
				printf("Shirt size selected: %s", sizes[i]);
				validChar = true;
				return shirtSize;
			}
		}
		puts("Invalid try again");
	}
	while (validChar == false);
	
	
}