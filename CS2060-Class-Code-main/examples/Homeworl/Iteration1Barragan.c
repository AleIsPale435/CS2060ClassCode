#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <ctype.h>

#define BUFF 80

const char* JERSEY_SIZE[] = { "small", "medium", "large", "xtra-large" };
const char* ANSWER[] = { "yes", "no"};

struct org{

	char orgName[BUFF];
	double raceDistance;
	double raceCost;
	double jerseyCost;
	double charityCost;
};

void fgetsRemoveNewLine(char* string);
bool adminSetUp(char* input);
void setupOrg(struct org *org);
bool validNumericData(char* string, double* value, double max, double min);


int main(void) {

	char userInput[BUFF];
	char* userInputPtr = userInput;
	bool admin = adminSetUp(userInputPtr);
	struct org org1;
	struct org* org1Ptr = &org1;
	if (admin) {
		
		setupOrg(org1Ptr);
		printf("%s\t%0.0lf miles\t$%0.2lf\t$%0.2lf\t%0.0lf Percent", org1.orgName, org1.raceDistance, org1.raceCost, org1.jerseyCost, org1.charityCost);
	}
	else {
		
	}

}

void fgetsRemoveNewLine(char* string) {

	fgets(string, BUFF, stdin);
	size_t lastChar = strlen(string) - 1;
	if (string[lastChar] == '\n') {
		string[lastChar] = '\0';
	}
}

bool adminSetUp(char* input) {
	int failedAttempt = 0;
	bool status = false;
	int counter = 3;
	char adminPassword[] = { "B!k34u" };
	puts("Enter admin pin to set up race information");

	do {
		puts("Enter admin password:");
		fgetsRemoveNewLine(input);
		int result = strcmp(input, adminPassword);
		if (result < 0 || result > 0) {
			failedAttempt++;
			printf("You have %d attempts\n", --counter);
			if (failedAttempt == 3) {
				puts("Exiting admin set-up");
				return status;
			}
		}
		else {
			status = true;
			puts("Set up the funraising information for the organization");
			return status;
		}

	} while (failedAttempt);
}

void setupOrg(struct org* org) {

	char orgDistance[BUFF];
	char orgRaceCost[BUFF];
	char jerseyCost[BUFF];
	char charityPercentage[BUFF];
	double distanceMax = 100;
	double distanceMin = 1;
	double rideCostMax = 250;
	double rideCostMin = 50;
	double jerseyCostMax = 150;
	double jerseyCostMin = 50;
	double charityPercentMax = 30;
	double charityPercentMin = 5;

	puts("Enter funraising organizations name:");
	fgetsRemoveNewLine(org->orgName);

	puts("Enter distance in miles for the bike course:");
	bool validDistance = false;
	do {
		fgetsRemoveNewLine(orgDistance);
		validDistance = validNumericData(orgDistance, &org->raceDistance, distanceMax, distanceMin);
	} while (validDistance == false);

	printf("Enter the registration cost of the bike ride for %s\n", org->orgName);
	bool validCost = false;
	do {
		fgetsRemoveNewLine(orgRaceCost);
		validCost = validNumericData(orgRaceCost, &org->raceCost, rideCostMax, rideCostMin);
	} while (validCost == false);
	printf("The bike race cost is $%0.0lf\n", org->raceCost);

	printf("Enter sales price of jersey for %s\n", org->orgName);
	bool validJerseyCost = false;
	do {
		fgetsRemoveNewLine(jerseyCost);
		validJerseyCost = validNumericData(jerseyCost, &org->jerseyCost, jerseyCostMax, jerseyCostMin);
	} while (validJerseyCost == false);
	printf("The bike jersey cost is $%0.0lf\n", org->jerseyCost);

	printf("Enter percentage of the bike race sales that will be donated to %s\n", org->orgName);
	bool validCharityPercentage = false;
	do {
		fgetsRemoveNewLine(charityPercentage);
		validCharityPercentage = validNumericData(charityPercentage, &org->charityCost, charityPercentMax, charityPercentMin);
	} while (validCharityPercentage == false);
	printf("The bike jersey cost is %0.0lf percent\n", org->charityCost);
}

bool validNumericData(char *string, double* value, double max, double min) {
	char* end;
	double tempValue = strtod(string, &end);
	errno = 0;
	bool state = false;
	if (end == string) {
		puts("No number was entered, try again");
	}
	else if ('\0' != *end) {
		puts("Number was not read, try again");
	}
	else if (tempValue > max || tempValue < min) {
		puts("Number out of range, try again");
	}
	else {
		 *value = tempValue;
		state = true;
	}

	if (state == false) {
		printf("Error: Enter a value from %0.0lf to %0.0lf\n", min, max);
	}
	return state;
}


