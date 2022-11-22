/*
Alejandro Barragan
Guided Exploration 5
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Pet {
	char name[80];
	int age;
	struct Pet* nextPtr;
}Pet;

// Functions used
void fgetsRemoveNewLine(char* string);
int stringCompareIgnoreCase(char* string1, char* string2);
void createPet(struct Pet** headPtr, char* name, int age);
void printList(Pet* listPtr);
void deleteNode(Pet** headPtr, char* nameToDelete);
void freeRemainingPets(Pet** headPtr);
void writeToFile(Pet* printPtr);


int main(void) {

	// Initialized values for below
	bool status = false;
	Pet* headPtr = NULL;
	char name[80];
	int age = 0;

	// Enters information for first pet and sends it to the createPet fuction
	puts("Enter name:");
	fgetsRemoveNewLine(name);
	puts("Enter age:");
	scanf("%d", &age);
	while ((getchar()) != '\n');
	createPet(&headPtr, name, age);

	do {
		// Prompts use to enter character of y or n to see if they would like to add another pet, if entered y, the name and age will be entered and sent to the createPet function
		puts("Would you like to add a pet? Answer (y)es or (n)o");
		char answer = getchar();
		while ((getchar()) != '\n');
		if (answer == 'y') {
			puts("Enter name:");
			fgetsRemoveNewLine(name);
			puts("Enter age:");
			scanf("%d", &age);
			while ((getchar()) != '\n');
			createPet(&headPtr, name, age);
		}
		// If user selects n, it will print out the current linked list of pets then will prompt the user to enter yes or no again to remove a pet
		else if (answer == 'n') {
			printList(headPtr);
			do {
				puts("Would you like to remove pet? Answer (y)es or (n)o");
				char answer2 = getchar();
				while ((getchar()) != '\n');

				// If the user selects yes, they will be prompted to enter the name of the pet they want to remove, it will get sent to the delete node method then print the list after
				if (answer2 == 'y') {
					char nameToRemove[80];
					puts("Enter pet to remove");
					fgetsRemoveNewLine(nameToRemove);
					deleteNode(&headPtr, nameToRemove);
					printList(headPtr);
				}

				// If the user selects no the list will be printed and the file will get written to along with freeing any remaining pets in memory
				else if (answer2 == 'n') {
					printList(headPtr);
					writeToFile(headPtr);
					freeRemainingPets(&headPtr);

					status = true;
				}

				// Will display if the user does not enter one of the two correct letters
				else {
					puts("Invalid letter try again");
				}

			} while (status == false);

		}
		// If the user enters incorrect letters this will prompt up
		else {
			puts("Invalid letter try again");
		}



	} while (status == false);
}

/// <summary>
/// This function gets user input and removes the new line character from the string
/// </summary>
void fgetsRemoveNewLine(char* string) {

	fgets(string, 80, stdin);
	int lastChar = strlen(string) - 1;
	if (string[lastChar] == '\n') {
		string[lastChar] = '\0';
	}

}

/// <summary>
/// This method is similar to the strcmp function except it will convert the two strings being compared to lowercase so it can compare them no matter what case the name was typed in
/// </summary>
int stringCompareIgnoreCase(char* string1, char* string2) {

	char string1Copy[80];
	strcpy(string1Copy, string1);
	char string2Copy[80];
	strcpy(string2Copy, string2);
	for (size_t i = 0; i < strlen(string1Copy); i++) {
		string1Copy[i] = tolower(string1Copy[i]);
	}
	for (size_t i = 0; i < strlen(string2); i++) {
		string2Copy[i] = tolower(string2Copy[i]);
	}

	return strcmp(string1Copy, string2Copy);
}

/// <summary>
/// This function takes in a name and an age along with a head ptr and will allocate memory for the pet node, make a new head, 
/// also insert the node based on alphabetical order comparing the first letter of each name and inserting it wherever it is necessary
/// </summary>
void createPet(Pet** headPtr, char* name, int age) {

	Pet* newNodePtr = malloc(sizeof(Pet));
	if (newNodePtr != NULL) {

		strcpy(newNodePtr->name, name);
		newNodePtr->age = age;

		Pet* previousPtr = NULL;
		Pet* currentPtr = *headPtr;

		while (currentPtr != NULL && currentPtr->name[0] <= name[0]) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if (previousPtr == NULL) {
			*headPtr = newNodePtr;
		}

		else {
			previousPtr->nextPtr = newNodePtr;
		}

		newNodePtr->nextPtr = currentPtr;
	}

	else {
		printf("No memory allocated for pet");
	}
}

/// <summary>
/// This function takes the head ptr and simply iterates through the list to print it out, if there is nothing it will report that it is empty
/// </summary>
void printList(Pet* listPtr)
{
	if (listPtr != NULL) {
		puts("List:");
		Pet* currentPtr = listPtr;

		while (currentPtr != NULL) {
			printf("Name: %s\tAge: %d\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPtr;
		}
	}
	else {
		puts("List is empty");
	}
}

/// <summary>
/// This function takes in the name of the pet that is wanting to be removed and goes ahead and compares through each pet in the list and determines 
/// which pet to remove then reconnect the list, it will report that the pet was not found if so
/// </summary>
void deleteNode(Pet** headPtr, char* nameToDelete)
{
	Pet* previousPtr = NULL;
	Pet* currentPtr = *headPtr;

	if (*headPtr != NULL) {

		if ((stringCompareIgnoreCase((*headPtr)->name, nameToDelete) == 0)) {
			*headPtr = (*headPtr)->nextPtr;
			free(currentPtr);
			currentPtr = NULL;
		}
		else {
			while (currentPtr != NULL && stringCompareIgnoreCase(currentPtr->name, nameToDelete) != 0) {
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
			}

			if (currentPtr != NULL) {
				previousPtr->nextPtr = currentPtr->nextPtr;
				free(currentPtr);
				currentPtr = NULL;
			}
			else {
				puts("Pet not found!");
			}
		}
	}
	else {
		puts("There aren't any pets in the list!");
	}

}

/// <summary>
/// This function will iterate through the list and if there are any more pets in memory it will deallocate them and remove them
/// </summary>
void freeRemainingPets(Pet** headPtr)
{
	Pet* currentPtr = *headPtr;
	Pet* nextNodePtr = NULL;

	while (currentPtr != NULL) {
		nextNodePtr = currentPtr->nextPtr;
		free(currentPtr);
		currentPtr = nextNodePtr;
	}

	*headPtr = NULL;
	puts("Removing all pets from program");
}

/// <summary>
/// This simple function is used to write the pet ageand name to a file
/// </summary>
void writeToFile(Pet* printPtr) {
	FILE* filePtr = fopen("C:\\Users\\kyerm\\Desktop\\Github2060\\CS2060ClassCode\\CS2060-Class-Code-main\\examples\\Homeworl\\pets.txt", "w");
	if (filePtr != NULL) {
		if (printPtr != NULL) {
			puts("List:");
			Pet* currentPtr = printPtr;

			while (currentPtr != NULL) {
				fprintf(filePtr, "Name: %s\tAge: %d\n", currentPtr->name, currentPtr->age);
				currentPtr = currentPtr->nextPtr;
			}
		}
		else {
			puts("List is empty");
		}
	}

	fclose(filePtr);
}