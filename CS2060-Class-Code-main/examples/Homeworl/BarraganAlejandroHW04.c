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
const double GRADE_A = 90;
const double GRADE_B = 80;
const double GRADE_C = 70;
const double GRADE_D = 60;

double getInput();
double calculateGrade(double grades[][GRADE_CATEGORIES], size_t students, size_t gradeCats);
void printTotalGrade(double finalGrades[]);


int main(void) {

	double grades[STUDENTS][GRADE_CATEGORIES];
	calculateGrade(grades, STUDENTS, GRADE_CATEGORIES);

	double finalGrades[STUDENTS];
	
	for (size_t i = 0; i < STUDENTS; i++) {
		double totalSum = 0;
		for (size_t j = 0; j < GRADE_CATEGORIES; j++) {
			totalSum += grades[i][j] * GRADE_CATEGORY_WEIGHT[j];

		}
		finalGrades[i] = totalSum;

	}
	
	printTotalGrade(finalGrades);


}

double getInput() {

	int validScan = 0;
	double input = 0;
	bool valid = true;

	do {
		validScan = scanf("%lf", &input);
		while (getchar() != '\n');

		if (validScan <= 0) {
			puts("Invalid try again");
		}
		else {
			if (input < MIN_GRADE || input > MAX_GRADE) {
				puts("Invalid try again");
			}
			else {
				return input;
			}
		}

	}

	while (valid);

}

double calculateGrade(double grades[][GRADE_CATEGORIES], size_t students, size_t gradeCats) {

	for (size_t i = 0; i < STUDENTS; i++) {
			for (size_t j = 0; j < GRADE_CATEGORIES; j++) {
				printf("Enter grade for student %d in catagory %d\n", ((int)i + 1), ((int)j + 1));
				grades[i][j] = getInput();
			}
		}
}

void printTotalGrade(double finalGrades[]) {

	char letterGrade = ' ';
	for (size_t i = 0; i < STUDENTS; i++) {
		if (finalGrades[i] < MAX_GRADE && finalGrades[i] > 90) {
			letterGrade = 'A';
		}
		else if (finalGrades[i] < 89 && finalGrades[i] > 80) {
			letterGrade = 'B';
		}
		else if (finalGrades[i] < 79 && finalGrades[i] > 70) {
			letterGrade = 'C';
		}
		else if (finalGrades[i] < 69 && finalGrades[i] > 60){
			letterGrade = 'D';
		}
		else {
			letterGrade = 'F';
		}
		printf("Student &d Grade: %.1lf %c", i, finalGrades[i], letterGrade);
	}
}