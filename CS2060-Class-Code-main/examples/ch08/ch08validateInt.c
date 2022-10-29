
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 13

bool exploreValidateInt(const char* buff);
bool validateInt(char* buff, int* const validInt);
void printLimits();

int main(void)
{
	char inputStr[LENGTH]; // create char arintray
	bool isValid = false;
	int integerValue = 0;
	size_t inputLength = 0;

	printLimits();

	

	for (unsigned int counter = 1; counter < 6; counter++)
	{
		puts("\nEnter an integer");
		fgets(inputStr, LENGTH, stdin);
		exploreValidateInt(inputStr);

	}



}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


bool  exploreValidateInt(const char* buff)
{
	char* end;
	errno = 0;
	int validInt = 0;
	bool state = true;
	long intTest = strtol(buff, &end, 10);

	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
		fprintf(stderr, "%ld is not valid\n", intTest);
		state = false;
	}
	else if ('\0' != *end && '\n' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
		fprintf(stderr, "%ld is valid\n", intTest);
	}
	else if (intTest > INT_MAX || intTest < INT_MIN) {
		fprintf(stderr, "%ld not in range\n", intTest);
		fprintf(stderr, "%ld is not valid\n", intTest);
		state = false;
	}
	else {
		validInt = (int)intTest;
		printf("%ld is integer value\n", intTest);
		printf("%ld is a valid integer\n", intTest);
	}

	return state;

}
