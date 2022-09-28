/*******************
 Understanding pointers
 - Using the asterisk and and symbol throughout 
 to print out the address but not only the 
 address but it also points to the variable that 
 is stored in the address itself
 - New format specifier %p is used to print out 
 an address 
 - The pointer itself has a different address 
 than the pointer is pointing to
 - If the pointer is pointing to another address, 
 it will be the same because it is referring to 
 that other address
 - Using both the & and asterisk can show the 
 same address because it is pointing to the 
 address of the pointer it is pointing to
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum;
	
	printf("houseNum %d\n", houseNum);

	printf("&houseNum %p\n\n", &houseNum);

	printf ("*houseNumPtr  %d\n", *houseNumPtr);

	printf ("houseNumPtr %p\n\n", houseNumPtr);

	printf ("&houseNumPtr %p\n\n", &houseNumPtr);

	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);

	calcHouseNum2 = 2 * (*houseNumPtr);

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);

	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);
			
	return 0;
}
