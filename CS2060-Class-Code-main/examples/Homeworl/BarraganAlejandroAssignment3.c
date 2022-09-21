/*
Alejandro Barragan
Assignment 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Methods declared at the top
void printCurrentBoardInfo(double hour, double price, int board);
double getValidHours();
double calculatePrice(double hours);
void printTotalSummary(double price, double hour, int boards);

// All of the constants which include the hours and the charges used for the program
const double MIN_CHARGE_FEE = 35;
const double CHARGE_OVER_TWO_HOURS = 10;
const double MAX_HOURS = 10;
const double MIN_HOURS = 0;
const double MIN_HOUR_CHARGE = 2;
const double MAX_CHARGE = 75;
const double END_PROGRAM = -1;

int main(void) {

	// Variables declared at the top of main to be used later
	int totalBoards = 0;
	double hours = 0;
	double price = 0;
	double totalHours = 0;
	double totalPrice = 0;
	bool isValid = true;

	// Do while loop is used to call the method of getting valid hours an if the 
	// end program button is entered, it will skip the while loop and end the program
	do {
		hours = getValidHours();
		
		// Once negative 1 is entered, it exits the loop
		if (hours == END_PROGRAM) {
			isValid = false;
		}

		else {

			// the calculate price method is called along with the variables being added up to show the total 
			price = calculatePrice(hours);
			totalPrice += price;
			totalHours += hours;
			totalBoards++;
			printCurrentBoardInfo(totalHours, totalPrice, totalBoards);
		}
	} 
	// After -1 is entered, it will print the total out for the boards entered previously
	while (isValid);
	printTotalSummary(totalPrice, totalHours, totalBoards);

}

/// <summary>
/// This method is called to print the current board information once the valid hours 
/// are entered for each board
/// </summary>
void printCurrentBoardInfo(double hour, double price, int board) {
	puts("Board\tHours\tCharge");
	printf("%d\t%3.2lf\t%3.2lf\n", board, hour, price);
}


/// <summary>
/// This function takes the user input and runs through to make sure the number 
/// entered is within the range and not a number outside the range or a letter
/// </summary>
double getValidHours() {
	double hours = 0;
	int isValidScan = 0;

	while (isValidScan <= 0) {

		// Prints out the information to type in the right value and makes sure no 
		// character or number outside of range is entered
		puts("Enter hours (Max is 10) or -1 to end program: ");
		isValidScan = scanf("%lf", &hours);
		while (getchar() != '\n');

		if (isValidScan <= 0) {

			puts("Invalid, try again");

		}
		else if (hours == END_PROGRAM) {
			hours = END_PROGRAM;
		}
		else if (hours < MIN_HOURS || hours > MAX_HOURS) {
			puts("Out of range, try again");
			scanf("%lf", &hours);
		}


	}


	return hours;

}
/// <summary>
/// This function will take in the amount of hours that were entered by the user 
/// and depending on if it was between 0 and 2 they will be charged the minimum 
/// charge and for every two hour
/// </summary>
double calculatePrice(double hours) {

	double price = 0;

	if (hours > MIN_HOUR_CHARGE) {
		price += (CHARGE_OVER_TWO_HOURS * hours) + MIN_CHARGE_FEE;

	}

	else if (hours > MIN_HOURS && hours <= MIN_HOUR_CHARGE) {
		price += MIN_CHARGE_FEE;
	}

	if (price > MAX_CHARGE) {
		price = MAX_CHARGE;
	}

	return price;
}

/// <summary>
/// This method will print the total summary after negative 1 is entered
/// </summary>
void printTotalSummary(double price, double hour, int boards)
{

	if (boards == 0) {
		puts("No boards entered");
	}
	else if (boards >= 1) {
		puts("Boards Rented\tHours\tCharge");
		printf("%d\t\t%3.2lf\t%3.2lf\n", boards, hour, price);

	}
}
