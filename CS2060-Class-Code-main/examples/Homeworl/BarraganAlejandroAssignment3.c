/*
Alejandro Barragan
Assignment 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printCurrentBoardInfo(double hour, double price, int board);
double getValidHours();
double calculatePrice(double hours);
void printTotalSummary(double price, double hour, int boards);

const double MIN_CHARGE_FEE = 35;
const double CHARGE_OVER_TWO_HOURS = 10;
const double MAX_HOURS = 10;
const double MIN_HOURS = 0;
const double MIN_HOUR_CHARGE = 2;
const double MAX_CHARGE = 75;

int main(void) {
	int totalBoards = 0;
	double hours = 0;
	double price = 0;
	double totalHours = 0;
	double totalPrice = 0;
	bool isValid = true;

	do {
		hours = getValidHours();
		if (hours == -1) {
			isValid = false;
		}
		else {
			price = calculatePrice(hours);
			totalPrice += price;
			totalHours += hours;
			totalBoards++;
			printCurrentBoardInfo(totalHours, totalPrice, totalBoards);
		}
	} while (isValid);
	printTotalSummary(totalPrice, totalHours, totalBoards);

}

void printCurrentBoardInfo(double hour, double price, int board) {
	puts("Board\tHours\tCharge");
	printf("%d\t%3.2lf\t%3.2lf\n", board, hour, price);
}



double getValidHours() {
	double hours = 0;
	int isValidScan = 0;

	while (isValidScan <= 0) {

		puts("Enter hours (Max is 10) or -1 to end program: ");
		isValidScan = scanf("%lf", &hours);
		while (getchar() != '\n');

		if (isValidScan <= 0) {

			puts("Invalid, try again");
		}
		else if (hours == -1) {
			hours = -1;
		}
		else if (hours < MIN_HOURS || hours > MAX_HOURS) {
			puts("Out of range, try again");
		}
		

	}


	return hours;

}

double calculatePrice(double hours) {

	double price = 0;
	price += (CHARGE_OVER_TWO_HOURS * hours) + MIN_CHARGE_FEE;


	if (price > MAX_CHARGE) {
		price = MAX_CHARGE;
	}

	return price;
}


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
