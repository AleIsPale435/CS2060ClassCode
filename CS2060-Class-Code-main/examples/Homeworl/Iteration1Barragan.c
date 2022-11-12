#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <ctype.h>

#define BUFF 80

const char* JERSEY_SIZE[] = { "small", "medium", "large", "xtra-large" };
const char* ANSWER[] = { "yes", "no" };

struct org {

	char orgName[BUFF];
	double raceDistance;
	double raceCost;
	double jerseyCost;
	double charityCost;
};

void fgetsRemoveNewLine(char* string);
bool adminSetUp();
void setupOrg(struct org* org);
bool validNumericData(char* string, double* value, double max, double min);
bool bikeRegistrationMode(char* name);
void displaySummary(struct org* org, int* jerseyCount, int* peopleCount);
void bikeRegistration(char* jerseySize[], char* answer[], int* jerseys, struct org* org, double *totalCostPtr, bool* jersey);
char getValidChar(char* arrayPtr[], size_t size);
bool enterCreditCard(char *card);
bool getReciept(char* arrayPtr[], size_t size, struct org* org, bool jersey);

int main(void) {


	puts("Enter admin pin to set up race information");
	bool admin = adminSetUp();
	struct org org1;
	struct org* org1Ptr = &org1;
	if (admin) {

		puts("Set up the funraising information for the organization");
		setupOrg(org1Ptr);
		printf("You can register for one of the following races and %0.0lf%c will be raised for %s\n", org1.charityCost, '%', org1.orgName);
		puts("Ride #1\tDistance\tCost");
		printf("%s\t%0.0lf miles\t$%0.2lf\n", org1.orgName, org1.raceDistance, org1.raceCost);

		bool registration;
		int numRegistrants = 0;
		int numJerseys = 0;
		int* numRegistrantsPtr = &numRegistrants;
		int* numJerseysPtr = &numJerseys;
		double totalCost = 0;
		double* totalCostPtr = &totalCost;
		bool jersey;
		bool* jerseyPtr = &jersey;

		do {
			puts("Enter first and last name to register");
			char name[BUFF];
			char* namePtr = name;
			registration = bikeRegistrationMode(namePtr);
			if (registration == false) {
				admin = adminSetUp();
				if (admin == true) {
					displaySummary(org1Ptr, numJerseysPtr, numRegistrantsPtr);
				}
				else {
					registration = true;
				}
			}
			else {

				bikeRegistration(JERSEY_SIZE, ANSWER, numJerseysPtr, org1Ptr, totalCostPtr, jerseyPtr);
				size_t answerArraySize = sizeof(ANSWER) / sizeof(ANSWER[0]);
				bool cardValid;
				char card[BUFF];
				do {
					puts("Enter your credit card");
					fgetsRemoveNewLine(card);
					cardValid = enterCreditCard(card);
				} while (cardValid == false);
				bool reciept = getReciept(ANSWER, answerArraySize, org1Ptr, jerseyPtr);
				numRegistrants++;
				printf("Thank you %s for your purchase", name);
			}

		} while (registration == true);



	}
	else {
		puts("Exiting admin set-up");
	}

	
}


void fgetsRemoveNewLine(char* string) {

	fgets(string, BUFF, stdin);
	size_t lastChar = strlen(string) - 1;
	if (string[lastChar] == '\n') {
		string[lastChar] = '\0';
	}
}

bool adminSetUp() {

	char input[BUFF];
	int failedAttempt = 0;
	bool status = false;
	int counter = 3;
	char adminPassword[] = { "B!k34u" };


	do {
		puts("Enter admin password:");
		fgetsRemoveNewLine(input);
		int result = strcmp(input, adminPassword);
		if (result == 0) {
			status = true;
			return status;
		}
		else {
			failedAttempt++;
			printf("You have %d attempts\n", --counter);
			if (failedAttempt == 3) {

				return status;
			}
		}

	} while (failedAttempt);

	return status;
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

bool validNumericData(char* string, double* value, double max, double min) {
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

bool bikeRegistrationMode(char* name) {

	bool status = true;
	char quit[] = { "QUIT" };
	char input[BUFF];
	fgetsRemoveNewLine(input);
	strcpy(name, input);
	if (strcmp(input, quit) == 0) {
		status = false;
	}
	return status;
}

void displaySummary(struct org* org, int* jerseyCount, int* peopleCount) {



}

void bikeRegistration(char* jerseySize[], char* answer[], int* jerseys, struct org* org, double *totalCostPtr, bool* jersey) {

	static int jerseyCount = 0;
	size_t jerseyArraySize = sizeof(JERSEY_SIZE) / sizeof(JERSEY_SIZE[0]);
	size_t answerArraySize = sizeof(ANSWER) / sizeof(ANSWER[0]);
	double totalCost = org->raceCost;

	printf("Would you like to purchase a jersey for $%0.2lf?\n", org->jerseyCost);
	if (getValidChar(answer, answerArraySize) == 'y') {

		puts("Enter size of jersey");
		bool validJerseySize = false;
		do {
			validJerseySize = getValidChar(jerseySize, jerseyArraySize);
		} while (validJerseySize == false);
		totalCost += org->jerseyCost;
		*jerseys = jerseyCount++;
		*jersey = true;
	}
	*totalCostPtr += totalCost;
	printf("Your total cost is %0.0lf\n", totalCost);


}

char getValidChar(char* arrayPtr[], size_t size) {

	char character;

	bool validChar = false;
	do {
		character = getchar();
		for (size_t i = 0; i < size; i++) {
			if (character == *arrayPtr[i]) {
				return character;
			}
		}

	} while (validChar == false);

}

bool enterCreditCard(char *card) {

	char* token1 = strtok(card, "-");
	int size = strlen(token1);
	for (size_t i = 0; i < size; i++) {
		if (token1[i] <= 'A' || token1[i] >= 'Z' || strlen(token1) != 4) {
			return false;
		}
	}
	int spacingPattern = 1;
	int pattern1 = 4;
	int pattern2 = 5;
	while (token1 != NULL) {
		token1 = strtok(NULL, "-");
		if (token1 == NULL && spacingPattern == 3) {
			return true;
		}
		int length = strlen(token1);
		if (spacingPattern == 1 && strlen(token1) == pattern1) {
			for (size_t i = 0; i < length; i++) {
				if (token1[i] > '9') {
					return false;
				}
			}
		}
		else if (spacingPattern == 2 && strlen(token1) == pattern2) {
			for (size_t i = 0; i < length; i++) {
				if (token1[i] > '9') {
					return false;
				}
			}
		}
		else {
			return false;
		}
		spacingPattern++;
	}
	return true;
}

bool getReciept(char* arrayPtr[], size_t size, struct org* org, bool jersey) {

	puts("Would you like a receipt?");
	double totalCost = org->raceCost;
	double charityCost = org->charityCost;

	if (getValidChar(ANSWER, size) == 'y' && jersey == true) {

		totalCost += org->jerseyCost;
		charityCost = (totalCost * charityCost) / 100;
		printf("Race\t$%0.2lf\n", org->raceCost);
		printf("Jersey\t$%0.2lf", org->jerseyCost);
		printf("Total cost: $%0.2lf", totalCost);
		printf("Donation to Charity: $%0.2lf", charityCost);
	}

	else if (getValidChar(ANSWER, size) == 'y' && jersey == false) {

		charityCost = (totalCost * charityCost) / 100;
		printf("Race\t$%0.2lf\n", org->raceCost);
		printf("Jersey\t$%0.2lf", org->jerseyCost);
		printf("Total cost: $%0.2lf", totalCost);
		printf("Donation to Charity: $%0.2lf", charityCost);
	}

	else {
		return false;
	}


	return true;
}