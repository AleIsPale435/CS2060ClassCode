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
void createPet(struct Pet **headPtr, char *name, int age);
void printList(Pet* listPtr);
void deleteNode(Pet** headPtr, char* nameToDelete);



int main(void) {

	bool status = false;
	Pet *headPtr = NULL;
	
	puts("Would you like to add a pet?");
	do {
		char answer = getchar();
		while ((getchar()) != '\n');
		if (answer == 'y') {
			char name[80];
			puts("Enter name:");
			fgetsRemoveNewLine(name);
			int age = 0;
			puts("Enter age:");
			scanf("%d", &age);
			while ((getchar()) != '\n');
			createPet(&headPtr, name, age);
		}
		else if (answer == 'n') {
			printList(headPtr);
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

void createPet(Pet **headPtr, char* name, int age) {

	Pet* newNodePtr = malloc(sizeof(Pet));
	if (newNodePtr != NULL) {
		
		strcpy(newNodePtr->name, name);
		newNodePtr->age = age;

		Pet* previousPtr = NULL;
		Pet* currentPtr = *headPtr;

		while (currentPtr != NULL && currentPtr->name[0] <= name[0])
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if (previousPtr == NULL)
		{
			*headPtr = newNodePtr;
		}
		
		else
		{
			previousPtr->nextPtr = newNodePtr;
		}

		newNodePtr->nextPtr = currentPtr;
	}

	else {
		printf("No memory allocated for node");
	}
}


void printList(Pet* listPtr)
{
	if (listPtr != NULL)
	{
		printf("%s", "The list is: ");
		Pet* currentPtr = listPtr;

		while (currentPtr != NULL)
		{
			printf("%s", currentPtr->name);
			printf("%d --> ", currentPtr->age);
			currentPtr = currentPtr->nextPtr;
		}
	}
	else
	{
		puts("List is empty");
	}
}

void deleteNode(Pet** headPtr, char *nameToDelete)
{ 
	Pet* previousPtr = NULL;
	Pet* currentPtr = *headPtr;

	if (*headPtr != NULL)
	{
		strcmp((* headPtr)->name, nameToDelete);
		if ((strcmp((*headPtr)->name, nameToDelete) == 1))
		{
			*headPtr = (*headPtr)->nextPtr;
			free(currentPtr);
			currentPtr = NULL;
		}
		else 
		{
			while (currentPtr != NULL && strcmp((*headPtr)->name, nameToDelete) <= 0)
			{			
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
			}
	
			if (currentPtr != NULL)
			{
				previousPtr->nextPtr = currentPtr->nextPtr;
				free(currentPtr);
				currentPtr = NULL;
			}
			else
			{
				puts("Node to delete not found!");
			}
		}
	}
	else 
	{
		puts("There aren't any pets in the list!");
	}

}