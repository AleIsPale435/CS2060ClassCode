/*
Chapter 5 Class Exploration 

Description: Functions, automatic conversions, pass by value
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// define function prototypes
int autoConvertToInt (int first, int second);
void swap(int a, int b);
void testStaticVar(void);


//Add your own comments to explain the code

int main() 
{

	//initialize variables
	int baseNum = 3;
	int powerNum = 4;
	float powerResult = 0;
	
	float first = 10.5;
	float second = 5.5;	
 	float third = 0;
 		
	// AutoConversion
	// Works, no compiler error ? 
    puts("Part 1: Conversion");
	//double pow(double x, double y)
	powerResult = pow(baseNum, powerNum);
	printf("powerResult %f \n", powerResult);
	printf("powerResult %d \n\n", powerResult);
	
	//int autoConvertToInt (int first, int second);
	third = autoConvertToInt(first, second);

	printf("third = %.2f\n", third);
	printf("third= %d\n", third);
			
	// part 2 pass by value
	puts ("\nPart 2 Pass by Value");
	int number1 = 7;
	int number2 = 82;

	printf ("Before swap number1 = %d\n", number1);
	printf ("Before swap number2 = %d\n", number2);

	//swap function will not change number1 or number2
	swap(number1, number2);

	printf ("After swap number1 = %d\n", number1);
	printf ("After swap number2 = %d\n\n", number2);
		
	//part 3
    puts("Part 3 static and non-static variables");
	testStaticVar();
	testStaticVar();
	testStaticVar();
	
	return 0;
}

//see how autoconvert works when types do not match
int autoConvertToInt (int first, int second)

{

   return first + second;

}// end autoconvert

// Function to swap two integers values
void swap (int a, int b) 
{
	//a and b are copies
	puts ("\n***Inside swap function***");
	printf ("Before swap a = %d\n", a);
	printf ("Before swap b = %d\n", b);

	// Swap the values
	int tmp = a;
	a = b;
	b = tmp;

	printf ("After swap a = %d\n", a);
	printf ("After swap b = %d\n", b);
	puts ("***End of swap function***\n");
	
	
} // end swap

void testStaticVar(void)
{
	int notStaticVar = 1;
    static int staticVar = 100;
    printf("notStaticVar = %d\n", notStaticVar);
    printf("staticVar = %d\n\n", staticVar);
    notStaticVar++;
    staticVar++;
}








