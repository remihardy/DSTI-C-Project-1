#include "functions.h"

//global variable declared in the main
//1: if the malloc was successfull, 0: if the malloc failed
extern int okmalloc;


//***************************************************
// Main function
//***************************************************
//Input		: Infix form as a string of characters
//Output	: computation result as a double
//using 2 functions internally : Infix2Polish and Polish2Calc
double ReversePolish(const char* strExpression)
{
	St_List Polish;					//linked list of the POSTFIX form of operands and operators
	Var_List VariablesList;			//list of variables including their value 
	double result;					//computed result that is returned by the function

	StListInit(&Polish);			//INIT linked list used to build the POSTFIX form
	StListInit(&VariablesList);		//INIT linked list containing the variables and their value

									//Converts INFIX string to POSTFIX (Reversed Polish Notation) form, 
									//NOTICE : 
									//------
									//The variables list is built during this parsing, 
									//But they are not replaced by their values in the POSTFIX expression :
									//the variables are replaced by their value only during calculation 
									//(as it is easier to support negative values at this point because they are directly used as numbers, not as strings)
	Infix2Polish(strExpression, &Polish, &VariablesList);

#ifdef DEBUG
	printf("[#DEBUG] Postfix expression : ");
	StListDisplay(&Polish);				//Print postfox form for Debug/Control
#endif

										//Use the POSTFIX form, to compute the result, including the replacement of the variables by their values
	result = (double)Polish2Calc(&Polish, &VariablesList);

	StListRemove(&Polish);				//for safety, as it is already empty from processing (pop)
	VarListRemove(&VariablesList);		//mandatory, free the variables data structure

	return result;
}


//***************************************************
// Input/Output functions
//***************************************************
//get string expression from the console
int GetInputString(char *readbuffer)
{
	char mystring[MAX_LINE_SIZE];
	int stop;

	printf("New Expression (. to exit) : ");
	do
	{

		gets(mystring);
	} while (strcmp(mystring, "") == 0);

	if (strcmp(mystring, ".") != 0) stop = 1; else stop = 0;
	strcpy(readbuffer, mystring);

	return stop;
}


//***************************************************
// Postfix to Calculation
//***************************************************
//Input		: List of strings of the operands and operators in Postfix form ; List of the variables and their value
//Output	: computed result as a double
float Polish2Calc(St_List * PolishQueue, Var_List* VariablesList)
{
	/*
	for each token in the postfix expression :
	if token is an operator :
	operand_2 ← pop from the stack
	operand_1 ← pop from the stack
	result ← evaluate token with operand_1 and operand_2
	push result back onto the stack
	else if token is an operand :
	push token onto the stack
	result ← pop from the stack
	*/

	//main variables
	char token[MAX_OP_SIZE];	//operator or operand on top of the Polish Queue
	Fl_List EvalStack;			//evaluation stack
	float result;				//evaluation result to be returned by the function

								//temporary variables
	float operand1;
	float operand2;
	float tmp_eval;				//temporary result of the operands operation
	float var_value;


	FlListInit(&EvalStack);							//initialization of the evaluation stack
	if (PolishQueue->First != NULL)					//the postfix list must not be empty to start its processing
	{
		while (PolishQueue->First != NULL)			//if not empty, travel the postfix expression and pop elements, until it becomes empty
		{
			strcpy(token, StListPop(PolishQueue));	//pop the token == operator/operand from the Polish Queue  										

													//************************
													// OPERATORS
													//************************
			if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
			{
				operand2 = FlListPop(&EvalStack);				//pop the 2 operands from the evaluation stack  
				operand1 = FlListPop(&EvalStack);

				switch (token[0]) {								//and do the calculation, depending on the detected operator

				case '+':
					tmp_eval = operand1 + operand2;
					break;

				case '-':
					tmp_eval = operand1 - operand2;
					break;

				case '*':
					tmp_eval = operand1 * operand2;
					break;

				default:
					tmp_eval = operand1 / operand2;
				}
				okmalloc = FlListPush(&EvalStack, tmp_eval);		//this result is pushed back to the evaluation stack
			}//end if operators

			 //************************
			 // OPERANDS
			 //************************
			else
			{
				if (isdigit(token[0]))								//it is a digit then ...
				{
					okmalloc = FlListPush(&EvalStack, atof(token));	//... the current operand is pushed to the evaluation stack
				}
				//if it is not a digit, it is a letter and thus a variable
				else
				{
					//if the variable (token) exists already in the variable list, 
					//its value (var_value), that is returned, is pushed to the evaluation stack  
					if (ExistVariable(VariablesList, token, &var_value) != 0)
					{
						okmalloc = FlListPush(&EvalStack, var_value);
					}
					//if the variable (token) does not exist in the variable list,
					//a 0 value is pushed to the evaluation stack 
					//HOWEVER this case is not supposed to happen as the initial string has been parsed and all variables identified
					else
					{
						okmalloc = FlListPush(&EvalStack, 0);
					}
				}
			}//end of operands
		}//end while
		 //the final result is left in the evaluation stack, it only needs to be popped out
		result = FlListPop(&EvalStack);
		FlListRemove(&EvalStack);//for safety, as it is already empty from processing (pop)
	}//end if
	return result;
}



//***************************************************
// Infix to Postfix (reversed Polish form) Conversion
//***************************************************
//Input		: Infix form as a string of characters ; 
//Output	: List of strings of the operands and operators in Postfix form ; Variables list built from parsing
void Infix2Polish(char *InfixBuffer, St_List* PolishQueue, Var_List* VariablesList)
{
	St_List OperatorsStack;		//operators stack
	St_Elt* TopStackOp;			//pointer to 1st element of operator stack
	char TopOp[MAX_OP_SIZE];	//operator on top of the operator stack
	char op[MAX_LINE_SIZE];		//current operator
	char sbuffer[MAX_LINE_SIZE];//used to convert float into string
	float var_value;
	int i = 0;

	StListInit(&OperatorsStack);		//init list head pointer=NULL and size=0

	while (i < strlen(InfixBuffer))		//travel along the buffer for parsing
	{
		strcpy(op, InfixBuffer + i);	//op is the current operator or operand

										//************************
										// OPERATORS
										//************************
		if (op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/')
		{
			op[1] = '\0';
			if (OperatorsStack.First != NULL) { //case : operator stack is not empty
				TopStackOp = OperatorsStack.First;
				while (
					//idea is to pop the previously stored operators and add them to the output queue
					//while there are operators in the stack 
					(OperatorsStack.First != NULL)
					&&
					//AND it is not a (
					(strcmp(TopStackOp->Op, "(") != 0)
					&&
					//AND the operator is stronger than the current one
					(strcmp(TopStackOp->Op, "*") || strcmp(TopStackOp->Op, "/"))
					&&
					(strcmp(op, "+") || strcmp(op, "-"))
					)
				{
					strcpy(TopOp, StListPop(&OperatorsStack));	//pop the operator from the stack  
					okmalloc = StListFileIn(PolishQueue, TopOp);	//add it to the output queue
					TopStackOp = OperatorsStack.First;
				}
				okmalloc = StListPush(&OperatorsStack, op);		//the current operator can be pushed to the operator stack
				i++;											//increment the buffer for parsing
			}
			else //case :  the operator stack is empty, simply push the current operator into it
			{
				okmalloc = StListPush(&OperatorsStack, op);
				i++;
			}
		} //end of OPERATOR

		  //************************
		  // ( (LEFT BRACKET)
		  //************************
		else if (op[0] == '(')
		{
			op[1] = '\0';
			okmalloc = StListPush(&OperatorsStack, op);			//simply push the ( to the operator stack
			i++;												//increment the buffer for parsing
		}
		//************************
		// ) (RIGHT BRACKET)
		//************************
		else if (op[0] == ')')
		{
			if (OperatorsStack.First != NULL) {					//operator stack is not empty
				TopStackOp = OperatorsStack.First;
				// idea is to process the operators until we find the left bracket in the stack
				while (strcmp(TopStackOp->Op, "(") != 0 && OperatorsStack.First != NULL)
				{
					strcpy(TopOp, StListPop(&OperatorsStack));	//pop the operator from the stack  
					okmalloc = StListFileIn(PolishQueue, TopOp);	//add it to the output queue
					TopStackOp = OperatorsStack.First;
				}
				//the left bracket is dropped (it is not added to the output queue)
				StListPop(&OperatorsStack);
				i++;											//increment the buffer for parsing
			}
		}
		//************************
		// WHITESPACE
		//************************
		else if (op[0] == ' ')
		{
			i++;	//whitespace is don t care, simply increment the buffer for parsing
		}
		else
			//************************
			// OPERANDS
			//************************
		{
			strcpy(op, "");
			int j = 0;
			//operands are anything else, but more specifically can be several digits or 1 char variable
			//end of the buffer (Strlen(InfixBuffer) needs to be checked in case a multi digit operand is at the end of the string
			//while digits are detected, the new digit is copied character by character to the variabel "op" 

			if (isalpha(InfixBuffer[i])) //case it is a variable
			{
				op[0] = InfixBuffer[i];
				op[1] = '\0';
				//if the variable does not exist, the new variable is added to the variables list and its value is requested from the user
				//the variable is not replaced in the postfix form (PolishQueue), "op" as variable name is kept in the postfix list (PolishQueue) 
				if (ExistVariable(VariablesList, op, &var_value) == 0)
				{
					okmalloc = VarListPush(VariablesList, op, &var_value);
				}
				else
				{
#ifdef DEBUG
					printf("[#DEBUG] variable %s already exists\n", op);
#endif
				}
				//in any case (whether the variable exists or not), "op" is added to the output queue
				okmalloc = StListFileIn(PolishQueue, op);
				i++;
			}
			else if (isdigit(InfixBuffer[i]))  //case it is a digit, it may be a multi digit operand
			{
				while (isdigit(InfixBuffer[i]) && InfixBuffer[i] != ' ' && i < strlen(InfixBuffer))
				{
					op[j++] = InfixBuffer[i++];
				}
				op[j] = '\0';
				//eventually the operands is added to the output queue
				okmalloc = StListFileIn(PolishQueue, op);
			}
			else //it is NOT an accepted character
			{
				op[0] = InfixBuffer[i];
				op[1] = '\0';
				printf("The expression is incorrect, %s not accepted\n", op);
				strcpy(op, "0");
				okmalloc = StListFileIn(PolishQueue, op);
				i++;

			}
		}//end of operands
	}
	//Finally 
	//the complete buffer has been parsed but there may be some operators left in the operators stack
	//all the remaining operators are poped and added to the output queue
	if (OperatorsStack.First != NULL)
	{
		TopStackOp = OperatorsStack.First;
		while (OperatorsStack.First != NULL)
		{
			strcpy(TopOp, StListPop(&OperatorsStack));	//pop the operator from the stack  
			okmalloc = StListFileIn(PolishQueue, TopOp);	//add it to the output queue
			TopStackOp = OperatorsStack.First;
		}
	}
	StListRemove(&OperatorsStack);//for safety, as it is already empty from processing (pop)

}



