#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_OP_SIZE 7 //max size of the operand or operator in the list

//*****************************
// St_List Type
//*****************************
//element type of the string list
typedef struct St_Elt St_Elt;
struct St_Elt
{
	char Op[MAX_OP_SIZE];
	St_Elt *Next;
};

//string list head
typedef struct St_List St_List;
struct St_List
{
	St_Elt *First;
	int Size;
};


//*****************************
// Fl_List Type
//*****************************
//element type of the float list
typedef struct Fl_Elt Fl_Elt;
struct Fl_Elt
{
	float Op;
	Fl_Elt *Next;
};

//float list head
typedef struct Fl_List Fl_List;
struct Fl_List
{
	Fl_Elt *First;
	int Size;
};


//*****************************
// Var_List Type
//*****************************
//element type of the variable list
typedef struct Var_Elt Var_Elt;
struct Var_Elt
{
	char Var[MAX_OP_SIZE];
	float Value;
	Var_Elt *Next;
};

//Var list head
typedef struct Var_List Var_List;
struct Var_List
{
	Var_Elt *First;
	int Size;
};

//*****************************
// St_List operations functions
//*****************************
void StListInit(St_List *);				//list initialization, size and head pointer
int  StListPush(St_List *, char *);		//add OP to the head of the list 
char* StListPop(St_List *);				//remove OP from the head of the list
int StListFileIn(St_List *, char *);	//add OP to the tail of the list
void StListDisplay(St_List *);			//display full list
void StListRemove(St_List *);			//clear - memory-free the list

										//******************************
										// Fl_List operations functions
										//*****************************
void FlListInit(Fl_List *);				//list initialization, size and head pointer
int  FlListPush(Fl_List *, float);		//add OP to the head of the list 
float FlListPop(Fl_List *);				//remove OP from the head of the list
void FlListRemove(Fl_List *);			//clear - memory-free the list

										//******************************
										// Var_List operations functions
										//*****************************
void VarListInit(Var_List *);						//list initialization, size and head pointer
int  VarListPush(Var_List *, char *, float *);		//add OP to the head of the list 
int ExistVariable(Var_List*, char *, float *);		//test the existence of a variable in the list
void VarListRemove(Var_List *);						//clear - memory-free the list
void VarListDisplay(Var_List *);					//display full list

