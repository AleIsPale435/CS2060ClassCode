/*
Alejandro Barragan
CS2060
T/Th
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>

#define SIZE 80
const char* SIZE_LIST[] = { "small", "medium", "large", "xtra-large" };

void fgetsRemoveNewLine(char* string);
void adminSetUp(char* string, double* distance, double* cost);
bool getValidDouble(char* string, double* value);
char getValidChar(char* letter);

int main(void) {


	char input[SIZE];
	char* inputPtr = input;
	puts("Enter your first and last name (80 Characters Max):");
	fgetsRemoveNewLine(inputPtr);

	char orgName[SIZE];
	char* orgNamePtr = orgName;
	double raceDistance = 0;
	double* raceDistancePtr = &raceDistance;
	double raceCost = 0;
	double* raceCostPtr = &raceCost;

	adminSetUp(orgNamePtr, raceDistancePtr, raceCostPtr);
	printf("%s\t%6.2lf Miles\t$%6.2lf\n", orgNamePtr, raceDistance, raceCost);

	char sizeShirt;
	char* sizeShirtPtr = &sizeShirt;
	puts("Select shirt size by entering the character shown (s)mall, (m)edium, (l)arge, (x)tra-large");
	getValidChar(sizeShirtPtr);



}

void fgetsRemoveNewLine(char* string) {


	fgets(string, SIZE, stdin);
	int lastChar = strlen(string) - 1;
	if (string[lastChar] == '\n') {
		string[lastChar] = '\0';
	}

}

void adminSetUp(char* string, double* distance, double* cost) {

	char raceDistance[SIZE];
	char raceCost[SIZE];

	puts("Enter org Name:");
	fgetsRemoveNewLine(string);

	puts("Enter race distance:");
	fgetsRemoveNewLine(raceDistance);
	bool validDistance = false;
	do {
		validDistance = getValidDouble(raceDistance, distance);
	} while (validDistance == false);

	puts("Enter race cost:");
	fgetsRemoveNewLine(raceCost);
	bool validCost = false;
	do {
		validCost = getValidDouble(raceCost, cost);
	} while (validCost == false); {
	}
}

bool getValidDouble(char* string, double* value) {

	char* end;
	double tempValue = strtod(string, &end);
	errno = 0;
	bool state = false;


	if (end == string) {
		fprintf(stderr, "%s: not a decimal number\n", string);
	}
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", string, end);
	}

	else if (tempValue > DBL_MAX || tempValue < DBL_MIN) {
		puts("Value is not in double range");
	}
	else {
		*value = tempValue;
		state = true;

	}
	return state;
}

char getValidChar(char* letter) {

	bool valid = true;
	char size;
	int scan = 0;
	do {
		scan = scanf("%c", &size);
		while (getchar() != '\n');
		if (scan <= 0) {
			puts("Invalid character try again");
		}
		else if (size == 's' || size == 'm' || size == 'l' || size == 'x') {
			for (size_t i = 0; i < sizeof(SIZE_LIST) / sizeof(SIZE_LIST[0]); i++) {
				if (tolower(size) == *SIZE_LIST[i]) {
					*letter = *SIZE_LIST[i];
					printf("Size selected: %s", SIZE_LIST[i]);
					return size;
				}
			}
		}
		else {
			puts("Invalid size try again");
		}

	} while (valid);




}