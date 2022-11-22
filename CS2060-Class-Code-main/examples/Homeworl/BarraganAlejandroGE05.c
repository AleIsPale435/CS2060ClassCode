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

void fgetsRemoveNewLine(char* string);
void createPet(struct Pet** headPtr, char* name, int age);
void printList(Pet* listPtr);
void deleteNode(Pet** headPtr, char* nameToDelete);
void freeRemainingPets(Pet** headPtr);
void writeToFile(Pet* printPtr);


int main(void) {

	bool status = false;
	Pet* headPtr = NULL;
	char name[80];
	int age = 0;

	puts("Enter name:");
	fgetsRemoveNewLine(name);
	puts("Enter age:");
	scanf("%d", &age);
	while ((getchar()) != '\n');
	createPet(&headPtr, name, age);

	do {
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
		else if (answer == 'n') {
			printList(headPtr);
			do {
				puts("Would you like to remove pet? Answer (y)es or (n)o");
				char answer2 = getchar();
				while ((getchar()) != '\n');
				if (answer2 == 'y') {
					char nameToRemove[80];
					puts("Enter pet to remove");
					fgetsRemoveNewLine(nameToRemove);
					deleteNode(&headPtr, nameToRemove);
					printList(headPtr);
				}
				else if (answer2 == 'n') {
					printList(headPtr);
					writeToFile(headPtr);
					freeRemainingPets(&headPtr);

					status = true;
				}
				else {
					puts("Invalid letter try again");
				}

			} while (status == false);

		}
		else {
			puts("Invalid letter try again");
		}



	} while (status == false);
}

void fgetsRemoveNewLine(char* string) {

	fgets(string, 80, stdin);
	int lastChar = strlen(string) - 1;
	if (string[lastChar] == '\n') {
		string[lastChar] = '\0';
	}

}

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

void deleteNode(Pet** headPtr, char* nameToDelete)
{
	Pet* previousPtr = NULL;
	Pet* currentPtr = *headPtr;

	if (*headPtr != NULL) {

		if ((strcmp((*headPtr)->name, nameToDelete) == 0)) {
			*headPtr = (*headPtr)->nextPtr;
			free(currentPtr);
			currentPtr = NULL;
		}
		else {
			while (currentPtr != NULL && strcmp(currentPtr->name, nameToDelete) != 0) {
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

void writeToFile(Pet* printPtr) {
	FILE* filePtr = fopen("C:\\Users\\kyerm\\Desktop\\Github2060\\CS2060ClassCode\\CS2060-Class-Code-main\\examples\\Homeworl\\pets.txt", "w");
	if (filePtr != NULL) {
		if (printPtr != NULL) {
			puts("List:");
			Pet* currentPtr = currentPtr;

			while (currentPtr != NULL) {
				fprintf("Name: %s\tAge: %d\n", currentPtr->name, currentPtr->age);
				currentPtr = currentPtr->nextPtr;
			}
		}
		else {
			puts("List is empty");
		}
	}

	fclose(filePtr);
}