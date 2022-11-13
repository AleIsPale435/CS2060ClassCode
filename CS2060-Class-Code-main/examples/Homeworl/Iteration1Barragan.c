/*
Alejandro Barragan
Project Iteration 1
This program performs several tasks. It prompts the user for the admin password to begin the bike 
registration, if it is not entered correctly three times, the program will exit. Once done it then 
prompts for the organization name, race distance, race cost, jersey cost, and the percent amount 
going to charity. Each with a different range of numbers that it requires. Once done, it then prompts
the user for registration names but if QUIT is entered, it will require to enter the admin password
to quit registration mode and print out the total sales for the race. Otherwise, name is entered, it 
will prompt the user to either buy or not buy a jersey, followed by the size of the jerseythen will 
prompt for card information following a pattern that is 4 uppercase letters, 4 numbers, and then 5 
numbers each seperated with a dash. Then it will ask if a receipt wants to be printed out then repeat 
until QUIT and the admin password has been entered which will then display the summary of sales.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <ctype.h>

// Constants and the buffer size for user input
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

// Functions
void fgetsRemoveNewLine(char* string);
bool adminSetUp();
void setupOrg(struct org* org);
bool validNumericData(char* string, double* value, double max, double min);
bool bikeRegistrationMode(char* name);
void displaySummary(struct org* org, int* jerseyCount, int* peopleCount);
void bikeRegistration(char* jerseySize[], char* answer[], int* jerseys, struct org* org, bool* jersey);
char getValidChar(char* arrayPtr[], size_t size);
bool enterCreditCard(char *card);
void getReciept(char* arrayPtr[], size_t size, struct org* org, bool jersey);

int main(void) {

	// This first part sets up the creation of the first organization. If the user admin password is entered
	// then the rest of the code will execute, otherwise it will shut down the program.
	puts("Enter admin pin to set up race information");
	bool admin = adminSetUp();
	struct org org1;
	struct org* org1Ptr = &org1;
	if (admin) {

		// This part sets up the organization by making the name and the other data types inside of the structure
		// then it displays all of the information about the structure
		puts("Set up the funraising information for the organization");
		setupOrg(org1Ptr);
		printf("You can register for one of the following races and %0.0lf%c will be raised for %s\n", org1.charityCost, '%', org1.orgName);
		puts("Ride #1\tDistance\tCost");
		printf("%s\t%0.0lf miles\t$%0.2lf\n", org1.orgName, org1.raceDistance, org1.raceCost);

		// Values for later
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
			// This is the bike registration mode, unless quit in all capitals is entered, it will simply take in 
			// the name and continue to register. Otherwise if QUIT is entered, the admin password will be needed
			// to exit out and display the summary which shows the total cost of all the registrants and jerseys bought. 
			// But if failed it will simply go back to bike registration mode
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
				// After getting the user name, it will then prompt to ask to buy a jersey, if yes a size
				// will be selected then the credit card information will be prompted to be entered. Keep
				// prompting until it is valid. Once done, it will ask for a receipt then will keep looping
				// until QUIT is entered then the admin password
				bikeRegistration(JERSEY_SIZE, ANSWER, numJerseysPtr, org1Ptr, totalCostPtr, jerseyPtr);
				size_t answerArraySize = sizeof(ANSWER) / sizeof(ANSWER[0]);
				bool cardValid;
				char card[BUFF];
				do {
					puts("Enter your credit card");
					fgetsRemoveNewLine(card);
					cardValid = enterCreditCard(card);
				} while (cardValid == false);
				getReciept(ANSWER, answerArraySize, org1Ptr, jerseyPtr);
				numRegistrants++;
				printf("Thank you %s for your purchase\n", name);
			}

		} while (registration == true);



	}
	else {
		puts("Exiting admin set-up");
	}

	
}

/// <summary>
/// This function takes in a character array and uses fgets to receieve user input but instead of leaving
/// the new line character in the array, this function finds the new line character and replaces it with 
/// the null character to make sure the new line character is not part of the string entered by the user
/// </summary>
void fgetsRemoveNewLine(char* string) {

	fgets(string, BUFF, stdin);
	size_t lastChar = strlen(string) - 1;
	if (string[lastChar] == '\n') {
		string[lastChar] = '\0';
	}
}
/// <summary>
/// This function takes user input in and if it does match the user admin password, it will return a true. 
/// If the input does not match the password and fails to type it in three times, the function will return
/// a false.
/// </summary>
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
/// <summary>
/// This function takes in a pointer to a structure of an organization and fills in the data types that currently 
/// stored inside of it. The org has a name, race cost, race distance, charity percentage, and a jersey cost. This
/// function simply fills those data types in using a pointer to the address of those data types.
/// </summary>
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
/// <summary>
/// This function takes in a user input, converts it to a double using string to double function, then goes
/// through it and makes sure it is withing the min and max that were also entered in the parameters. It also 
/// checks the number and makes sure no letters or other characters that are not numbers are entered, otherwise
/// it will return false if it could not convert the value to a valid number. If nothing was found and number is
/// in range, it will return a true.
/// </summary>
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
/// <summary>
/// This function takes in the string inputed by the user in the bike registration part of the project and 
/// determines if the user wants to quit out of bike registration mode. If QUIT is entered, false is returned
/// and is prompted to enter the admin password. Otherwise it takes in the name and returns true
/// </summary>
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
/// <summary>
/// This simple function just takes in the org pointer and the number of people that registered for the race
/// along with the amount of jerseys that were bought and calculates and displays the total amount of money 
/// that was spent including the amount of money raised for the charity of the organization.
/// </summary>
void displaySummary(struct org* org, int* jerseyCount, int* peopleCount) {

	printf("Summary of race sales where %c%0.0lf goes to charity\n", '%', org->charityCost);
	puts("Race\tDistance\tPrice\tRegistrants\tTotal Sales\tCharity Amount");
	double totalRegistrants = org->raceCost * *peopleCount;
	double charityRegistrants = (totalRegistrants * org->charityCost) / 100;
	double jerseySales = *jerseyCount * org->jerseyCost;
	double charityJerseySales = (jerseySales * org->charityCost) / 100;
	double totalSales = jerseySales + totalRegistrants;
	double totalCharitySales = (totalSales * org->charityCost) / 100;
	printf("#1\t%0.0lf miles\t$%0.2lf\t%d\t\t$%0.2lf\t\t$%0.2lf\n", org->raceDistance, org->raceCost, *peopleCount, totalRegistrants, charityRegistrants);
	puts("Shirts Sold\tSales\tCharity");
	printf("%d\t$%0.0lf\t$%0.0lf\n", *jerseyCount, jerseySales, charityJerseySales);
	printf("Total Sales:\t$%0.2lf\n", totalSales);
	printf("Total funds raised for Charity:\t$%0.2lf\n", totalCharitySales);

}
/// <summary>
/// This function takes in both the answer and size jersey arrays, along with the organization pointer and the bool jersey
/// and this asks the user if the user wants to buy a jersey. If they said y or yes then they are asked for the size of the
/// jersey which will repeat if they do not select the right size. After it will be added to the total cost then display it.
/// It also adds the jersey counter pointer to one to calculate the amount of jerseys that are bought. Static variable is 
/// used to keep track of it. If the user selects n or no then it will only show the total cost without the jersey.
/// </summary>
void bikeRegistration(char* jerseySize[], char* answer[], int* jerseys, struct org* org, bool* jersey) {

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
		jerseyCount++;
		*jerseys = jerseyCount;
		*jersey = true;
	}
	printf("Your total cost is $%0.0lf\n", totalCost);


}
/// <summary>
/// This function takes in either the answers or the sizes pointer array and gets a character for selection.
/// If the character that is entered does not match either of the ones that are in the pointer array, 
/// it will keep prompting to enter the character until the right one is entered. It will then return the 
/// character.
/// </summary>
char getValidChar(char* arrayPtr[], size_t size) {

	char character;

	bool validChar = false;
	do {
		character = getchar();
		while (getchar() != '\n');
		for (size_t i = 0; i < size; i++) {
			if (character == *arrayPtr[i]) {
				return character;
			}
		}
		puts("Invalid Character try again");

	} while (validChar == false);

}
/// <summary>
/// This function takes in the card information that was typed in and goes through each token with the -
/// character and makes sure it is valid. The first four characters of token1 must be uppercase letters and
/// then the next 4 must be numbers and finally the last 5 must be numbers as well. It will return true if 
/// the information is correct, otherwise it will keep prompting the user to enter the card information
/// in the right order.
/// </summary>
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
/// <summary>
/// This function takes in the array of pointers with yes and no then asks the user if they want a receipt
/// It will print out a receipt for both a purchased jersey or not along with the total. If typed n, then
/// nothing will be typed
/// </summary>
void getReciept(char* arrayPtr[], size_t size, struct org* org, bool jersey) {

	puts("Would you like a receipt?");
	double totalCost = org->raceCost;
	double charityCost = org->charityCost;

	if (getValidChar(ANSWER, size) == 'y' && jersey == true) {

		totalCost += org->jerseyCost;
		charityCost = (totalCost * charityCost) / 100;
		printf("Race\t$%0.2lf\n", org->raceCost);
		printf("Jersey\t$%0.2lf\n", org->jerseyCost);
		printf("Total cost: $%0.2lf\n", totalCost);
		printf("Donation to Charity: $%0.2lf\n", charityCost);
	}

	else if (getValidChar(ANSWER, size) == 'y' && jersey == false) {

		charityCost = (totalCost * charityCost) / 100;
		printf("Race\t$%0.2lf\n", org->raceCost);
		printf("Jersey\t$%0.2lf\n", org->jerseyCost);
		printf("Total cost: $%0.2lf\n", totalCost);
		printf("Donation to Charity: $%0.2lf\n", charityCost);
	}

	else {
		return false;
	}


	return true;
}