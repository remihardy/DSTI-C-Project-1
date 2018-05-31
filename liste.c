#include "liste.h"

//*****************************
// ST_LIST operations functions
//*****************************

//------------------------------------------------------------------------------------------------------------
//INIT
void StListInit(St_List *aList)
{
	aList->First = NULL;
	aList->Size = 0;
}

//------------------------------------------------------------------------------------------------------------
//PUSH
int StListPush(St_List *aList, char *Op)					//add (type : string) OP to the head of the list
{
	St_Elt *pNewElement;									//pointer to the newly created element
	int success;											//flag whether Element has been successfully created

	pNewElement = (St_Elt *)malloc(sizeof(St_Elt));			//allocate memory for new element
	if (pNewElement != NULL)
	{
		strcpy(pNewElement->Op, Op);				        //copy the OP to the newly created element
		pNewElement->Next = aList->First;					//the newly created element has to point to the former element pointer by list head
		aList->First = pNewElement;							//list head has to point to the newly created element
		aList->Size++;										//list size increase by 1 newly created element
		success = 1;
	}
	else
	{
		success = 0;
	}
	return success;
}

//------------------------------------------------------------------------------------------------------------
//POP
char* StListPop(St_List *aList)								//remove (type : string) OP from the head of the list
{
	St_Elt *pToBeRemoved;									//pointer to the Element to be removed
	char Op[MAX_OP_SIZE];

	if (aList->First != NULL)
	{
		pToBeRemoved = aList->First;						//we want to remove the first element
		strcpy(Op, pToBeRemoved->Op);						//Get OP
		aList->First = pToBeRemoved->Next;					//list head has now to point the the next element
		free(pToBeRemoved);									//Element can be cleared
		aList->Size--;

	}
	else
	{
		strcpy(Op, "#");									//returned error character is case the list was empty 
	}

	return Op;
}

//------------------------------------------------------------------------------------------------------------
//FILE IN
int StListFileIn(St_List *aList, char *Op)					//add (type : string) OP to the tail of the list
{
	St_Elt *pNewElement;									//pointer to the newly created element
	St_Elt *pCurrent;										//pointer used to travel along the list to find the tail of the list
	int success;											//whether Element has been successfully created

	pNewElement = (St_Elt *)malloc(sizeof(St_Elt));			//allocate memory for new element
	if (pNewElement != NULL)
	{
		success = 1;
		strcpy(pNewElement->Op, Op);						//copy the OP to the element
		pNewElement->Next = NULL;
		if (aList->First == NULL)							//No Element yet, this is the first to be added
		{
			aList->First = pNewElement;						//list head has to point to the newly created element
			aList->Size++;									//list size increase by 1 newly created element
		}
		else												//There is at least 1 element already
		{
			pCurrent = aList->First;						//go to the tail of the list
			while (pCurrent->Next != NULL)
			{
				pCurrent = pCurrent->Next;
			}
			pCurrent->Next = pNewElement;					//list tail has to point to the newly created element
			aList->Size++;
		}
	}
	else
	{
		success = 0;
	}
	return success;
}

//------------------------------------------------------------------------------------------------------------
//FREE the List from Memory
void StListRemove(St_List *aList)
{
	St_Elt *ToBeRemoved;					//pointer to the Element to be removed

	while (aList->First != NULL)
	{
		ToBeRemoved = aList->First;			//we want to remove the first element
		aList->First = ToBeRemoved->Next;	//list head has now to point the the second element
		free(ToBeRemoved);					//Element can be cleared, no need to check NULL pointer, we know we have something here
		aList->Size--;						//List size decrease by 1 element
	}
}

//------------------------------------------------------------------------------------------------------------
//DISPLAY
//print complete List, was developped for Debug 
void StListDisplay(St_List *aList)
{
	St_Elt *pReadElement = aList->First;				//start from list head

	while (pReadElement != NULL)						//while the tail of the list has not been reached
	{
		printf("%s ", pReadElement->Op);
		pReadElement = pReadElement->Next;
	}
	printf("\n");
}



//***************************
// Fl_LIST operations functions
//***************************

//------------------------------------------------------------------------------------------------------------
//INIT
void FlListInit(Fl_List *aList)
{
	aList->First = NULL;
	aList->Size = 0;
}

//------------------------------------------------------------------------------------------------------------
//PUSH
int  FlListPush(Fl_List *aList, float aFloat)				//add (type : float) OP to the head of the list 
{
	Fl_Elt *pNewElement;									//pointer to the newly created element
	int success;											//whether Element has been successfully created

	pNewElement = (Fl_Elt *)malloc(sizeof(Fl_Elt));			//allocate memory for new element
	if (pNewElement != NULL)
	{
		pNewElement->Op = aFloat;				            //copy the OP to the element
		pNewElement->Next = aList->First;					//the newly created element has to point to the former element pointer by list head
		aList->First = pNewElement;							//list head has to point to the newly created element
		aList->Size++;										//list size increase by 1 newly created element
		success = 1;
	}
	else
	{
		success = 0;
	}
	return success;
}

//------------------------------------------------------------------------------------------------------------
//POP
float FlListPop(Fl_List *aList)								//remove (type : float) OP from the head of the list
{
	Fl_Elt *pToBeRemoved;									//pointer to the Element to be removed
	float Op = 0;

	if (aList->First != NULL)
	{
		pToBeRemoved = aList->First;						//we want to remove the first element
		Op = pToBeRemoved->Op;								//Get OP
		aList->First = pToBeRemoved->Next;					//list head has now to point the the next element
		free(pToBeRemoved);									//Element can be cleared
		aList->Size--;

	}
	return Op;
}

//------------------------------------------------------------------------------------------------------------
//FREE the List from Memory
void FlListRemove(Fl_List *aList)
{
	Fl_Elt *ToBeRemoved;					//pointer to the Element to be removed

	while (aList->First != NULL)
	{
		ToBeRemoved = aList->First;			//we want to remove the first element
		aList->First = ToBeRemoved->Next;	//list head has now to point the the second element
		free(ToBeRemoved);					//Element can be cleared, no need to check NULL pointer, we know we have something here
		aList->Size--;						//List size decrease by 1 element
	}
}



//***************************
// Var_List operations functions
//***************************

//------------------------------------------------------------------------------------------------------------
//INIT
void VarListInit(Var_List *aList)
{
	aList->First = NULL;
	aList->Size = 0;
}


//------------------------------------------------------------------------------------------------------------
//PUSH
int VarListPush(Var_List *aList, char *Op, float *var_value) //add (type : Var) OP to the head of the list
{
	Var_Elt *pNewElement;									//pointer to the newly created element
	int success;											//whether Element has been successfully created
	float value;


	pNewElement = (Var_Elt *)malloc(sizeof(Var_Elt));		//allocate memory for new element
	if (pNewElement != NULL)
	{
		strcpy(pNewElement->Var, Op);				        //copy the OP to the element
		printf("Variable %s value : ", Op);					//CONSOLE INTERACTION to capture the value of the variable from the user
		scanf("%f", &value);
		pNewElement->Value = value;
		pNewElement->Next = aList->First;					//the newly created element has to point to the former element pointer by list head
		aList->First = pNewElement;							//list head has to point to the newly created element
		aList->Size++;										//list size increase by 1 newly created element
		*(var_value) = value;								//the value is returned in the var_value parameter of the function
		success = 1;
	}
	else
	{
		success = 0;
	}
	return success;
}


//------------------------------------------------------------------------------------------------------------
//VARIABLE EXISTENCE TEST
//inputs: aList : List of variables, Op : variable name whose existence has to be tested
//outputs : variable existence from the function, aValue : its value 
int ExistVariable(Var_List* aList, char *Op, float *aValue)
{
	Var_Elt *pCurrent;							//Element pointer while traveling the list
	int exist = 0;								//"exist" flag, will be returned by the function 

	pCurrent = aList->First;					//start from list head

	while (pCurrent != NULL && exist == 0)		//travel the list as long as the tail has not been reached and element has not been found
	{
		if (strcmp(Op, pCurrent->Var) == 0)		//compare the variable name to test the existence
		{
			exist = 1;
			*(aValue) = pCurrent->Value;		//if found, the function returns its value in the parameters
		}
		pCurrent = pCurrent->Next;
	}
	return exist;
}


//------------------------------------------------------------------------------------------------------------
//FREE the List from Memory
void VarListRemove(Var_List *aList)
{
	Var_Elt *ToBeRemoved;					//pointer to the Element to be removed

	while (aList->First != NULL)
	{
		ToBeRemoved = aList->First;			//we want to remove the first element
		aList->First = ToBeRemoved->Next;	//list head has now to point the the second element
		free(ToBeRemoved);					//Element can be cleared, no need to check NULL pointer, we know we have something here
		aList->Size--;						//List size decrease by 1 element
	}
}


//------------------------------------------------------------------------------------------------------------
//DISPLAY
//print complete List, was developped for Debug 
void VarListDisplay(Var_List *aList)
{
	Var_Elt *pReadElement = aList->First;				//start from list head

	while (pReadElement != NULL)						//while the tail of the list has not been reached
	{
		printf("%s %f\n", pReadElement->Var, pReadElement->Value);
		pReadElement = pReadElement->Next;
	}
	printf("\n");
}


