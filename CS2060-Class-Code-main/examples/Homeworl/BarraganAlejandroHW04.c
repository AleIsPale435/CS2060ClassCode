/*
Alejandro Barragan
Homework 04
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Constants defined at the top
#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1.Learning Activity 2.Homework 3.Projects 4.Midterm 5.Final "
#define MAX_GRADE 105
#define MIN_GRADE 0
const double GRADE_CATEGORY_WEIGHT[] = { .1, .3, .3, .15, .15 };

// Several methods for calculating and displaying grades and headers
void displayHeader();
double getInput();
void calculateGrade(double grades[][GRADE_CATEGORIES], size_t students, size_t gradeCats);
void calculateFinalGrade(double grades[][GRADE_CATEGORIES], double finalGrade[], size_t students, size_t gradeCats);
void printTotalGrades(double finalGrades[]);


int main(void) {

	// Make variables to hold the grades and the final grades 
	double grades[STUDENTS][GRADE_CATEGORIES];
	double finalGrades[STUDENTS];

	// Call all of the methods back to back
	displayHeader();
	calculateGrade(grades, STUDENTS, GRADE_CATEGORIES);
	calculateFinalGrade(grades, finalGrades, STUDENTS, GRADE_CATEGORIES);
	printTotalGrades(finalGrades);


}
/// <summary>
/// This simple void is simply going to just display the header to introduce the program
/// it will display the weight and the categories being graded on
/// </summary>
void displayHeader() {
	
	puts("This program will caculate grades for these categories: \n");
	printf(CATEGORIES"\n\n");
	for (size_t i = 0; i < GRADE_CATEGORIES; i++) {
		printf("Category %d weight is %1.2lf\n", ((int)i + 1), GRADE_CATEGORY_WEIGHT[i]);
	}
	puts("\nEnter grades in this order " CATEGORIES "\n");
}
/// <summary>
/// This simple input method will test each value it is received and make sure it is a valid 
/// value in range or that it is not a letter.
/// </summary>
double getInput() {

	int validScan = 0;
	double input = 0;
	bool valid = true;

	// Standard security measures, makes sure the scanf returns a 1 if not try again and if it
	// does return the value, it checks the input value and make sure it is in range
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
/// <summary>
/// This method will take in the grades array and prompt the user to type in the grades
/// for each student under each category
/// </summary>
void calculateGrade(double grades[][GRADE_CATEGORIES], size_t students, size_t gradeCats) {

	// First for loop takes in the input of the user
	for (size_t i = 0; i < STUDENTS; i++) {
		for (size_t j = 0; j < GRADE_CATEGORIES; j++) {
			printf("Enter grade for student %d in catagory %d\n", ((int)i + 1), ((int)j + 1));
			grades[i][j] = getInput();
		}
	}

	// Second for loop goes through the array and displays what the user inputted
	for (size_t i = 0; i < STUDENTS; i++) {
		printf("\nStudent %d grades entered: ", (int)i);
		for (size_t j = 0; j < GRADE_CATEGORIES; j++) {
			printf("%4.0lf\t", grades[i][j]);
		}
	}
	
	
		
}
/// <summary>
/// This function will go through each element of the array multiply by the appropriate 
/// weight scale and then add it up to get the final grade of the student
/// </summary>
void calculateFinalGrade(double const grades[][GRADE_CATEGORIES],double finalGrade[], size_t students, size_t gradeCats) {
	
	// For loop to go through each element, add it to total sum, then reset the counter
	// after each row is done then calculate the final grade for the student and put it 
	// in the 1 dimensional final grades array
	for (size_t i = 0; i < STUDENTS; i++) {
		double totalSum = 0;
		for (size_t j = 0; j < GRADE_CATEGORIES; j++) {
			totalSum += grades[i][j] * GRADE_CATEGORY_WEIGHT[j];

		}
		finalGrade[i] = totalSum;

	}
}
/// <summary>
/// This method takes in the final grades array and displays the final grades for each student
/// including the class average
/// </summary>
void printTotalGrades(double const finalGrades[]) {

	// Two variables made
	char letterGrade = ' ';
	double classAverage = 0;

	// Header and checks each final grade value to determine which letter grade the student will get
	puts("\n\nFinal grades: \n");
	for (size_t i = 0; i < STUDENTS; i++) {
		if (finalGrades[i] >= 90) {
			letterGrade = 'A';
		}
		else if (finalGrades[i] < 90 && finalGrades[i] >= 80) {
			letterGrade = 'B';
		}
		else if (finalGrades[i] < 80 && finalGrades[i] >= 70) {
			letterGrade = 'C';
		}
		else if (finalGrades[i] < 70 && finalGrades[i] >= 60){
			letterGrade = 'D';
		}
		else {
			letterGrade = 'F';
		}
		
		// Prints the students final grades then adds up all of the final grades 
		printf("Student %d Grade: %.1lf %c\n", ((int)i + 1), finalGrades[i], letterGrade);
		classAverage += finalGrades[i];
	}

	// Divides the total final grades by the amount of students tot get the final class average
	classAverage = classAverage / STUDENTS;
	printf("\nClass average: %.1lf", classAverage);
}