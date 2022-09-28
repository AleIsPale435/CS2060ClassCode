// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>

int cubePass1(int number);
int cubePass2(int * numberPtr);

int main(void) {

	int numberMain = 5;
	int result = 0;
	
	// In these two print statements, the value of 
	// numberMain is shown and the second print statement, 
	// it is showing the address that the value inside of numberMain is located
	printf ("In main before cubePass1  numberMain = %d\n", numberMain);
	printf("&numberMain = %p\n", &numberMain);

	// First cube pass function is called and it passes the value number main
	result = cubePass1(numberMain);

	// First print statement shows the number 5 still because although the value was passed in, 
	// it was not changed in the method Instead it happens in the second print method where it 
	// displays the result which was returned in the method.
	printf ("In main after cubePass1  numberMain = %d\n", numberMain);
	printf ("Result = %d\n", result);
	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain);
	
	// Second cubepass function passed but this time the address of the value was passed in 
	// rather than the value itself. Passed by reference
	result = cubePass2(&numberMain);
	
	// The numberMain value printed is now the same as the result 
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain);
	printf("result = %d\n", result);

} // main


// Passing in by value
int cubePass1 (int number) 
{
	int cube = 0;
	puts("\nIn cubePass1");
	printf("number = %d\n", number);
	printf("&number = %p\n", &number);
	cube = number * number * number;
	printf("cube  = %d\n", cube);

	// Since number is being sent a copy of the numberMain and it is not returned, the value 
	// itself is not changed and that is why the value is the same when it goes back to main
	number = cube;
	printf("number = %d\n", number);
	return cube;
} 

// Still passing a value but instead it is passing a pointer 
int cubePass2 (int * const numberPtr) 
{
	int cube = 0;
	puts ("\nIn cubePass2");
	printf("numberPtr = %p\n", numberPtr);
	printf ("*numberPtr = %d\n", *numberPtr);
	printf("&numberPtr = %p\n", &numberPtr);

	// Compared to cubePass1, instead of the value itself being changed and then being left the 
	// same in main, it is passing the address of the value which means it is able to change the 
	// value that is in that address
	cube = (* numberPtr )* (* numberPtr )* (* numberPtr); 

	// Pointer pointing to address now changes the value inside the address 
	*numberPtr = cube;
	printf ("*numberPtr = %d\n", *numberPtr);
	return cube;
} 


