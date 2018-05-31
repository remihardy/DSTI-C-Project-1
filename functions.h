#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

#define MAX_LINE_SIZE 256 //max size for the buffer read from the console
#define DEBUG

//***************************************************
// Main function
//***************************************************
//Input		: Infix form as a string of characters
//Output	: computation result as a double
//using 2 functions internally : Infix2Polish and Polish2Calc
double ReversePolish(const char*);


//***************************************************
// Input/Output functions
//***************************************************
//get string expression from the console
int GetInputString(char *);



//***************************************************
// Infix to Postfix (reversed Polish form) Conversion
//***************************************************
//Input		: Infix form as a string of characters ; 
//Output	: List of strings of the operands and operators in Postfix form ; Variables list built from parsing
void Infix2Polish(char *, St_List*, Var_List*);



//***************************************************
// Postfix to Calculation
//***************************************************
//Input		: List of strings of the operands and operators in Postfix form ; List of the variables and their value
//Output	: computed result as a double
float Polish2Calc(St_List *, Var_List*);






