/*
Alejandro Barragan
Homework 04
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
#define MAX_GRADE 105
#define MIN_GRADE 0
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };

double getInput(double value);


int main(void) {

	double studentInput = 0;
	double grades[STUDENTS][GRADE_CATEGORIES];
	bool validScan = true;
	
	do {
		studentInput = getInput(studentInput);

		if (studentInput > MAX_GRADE || studentInput < MIN_GRADE) {
			validScan = false;
		}

	}


}

double getInput(double value) {

	int validScan = 0;
	double input = 0;

	while (validScan <= 0) {

		validScan = scanf("%f", &input);
		while (getchar != '\n');

		if (validScan <= 0) {
			printf("%s", "Invalid try again");
		}
		else {
			return value;
		}
	}
}