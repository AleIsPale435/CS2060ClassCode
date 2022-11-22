/*
Alejandro Barragan
Guided Exploration 5
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <ctype.h>

typedef struct Pet {
	char name[80];
	int age;
	struct Pet* nextPtr;
}Pet;

void fgetsRemoveNewLine(char* string);
void createPet(struct Pet **headPtr, char *name, int age);
void printList(Pet* listPtr);



int main(void) {

	bool status = false;
	Pet *headPtr = NULL;
	do {
		char answer = getchar();
		if (answer == 'y') {
			char name[80];
			fgetsRemoveNewLine(name);
			int age;
			scanf("%d", &age);
			while ((getchar()) != '\n');
			createPet(&headPtr, name, age);
		}
		else if (answer == 'n') {

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
		
		fgetsRemoveNewLine(newNodePtr->name);
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