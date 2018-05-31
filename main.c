#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

//global variable
//1: if the malloc was successfull, 0: if the malloc failed
int okmalloc = 1;

int main()
{
	char ReadBuffer[MAX_LINE_SIZE];		//read buffer from the console
	double result;						//operations result
	int more;

	//Read INFIX form equation from the console ; typing "." (with function GetInputString returning 0) will exit
	while (GetInputString(ReadBuffer)) {
		result = ReversePolish(ReadBuffer);
		printf("Result = %f\n", result);
	}

	//malloc error management
	if (okmalloc == 0) { printf("Error related to memory allocation (malloc)\n"); }

	system("pause");
	return okmalloc;
}




