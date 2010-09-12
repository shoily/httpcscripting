/*
File Name : runtime.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains data structure and defines for runtime
*/

#ifndef _RUNTIMEENVIRONMENT_H
#define _RUNTIMEENVIRONMENT_H

#include "common.h"
#include "symtab.h"

//Data structure to keep the symbol tables' pointer for runtime storage management
typedef struct _RuntimeSymbolTableList RuntimeSymbolTableList;

struct _RuntimeSymbolTableList
{
	int storage_size;						// storage size for this symbol table
	SymbolTable *symtab;					// symbol table pointer
	LONGPARAM *data_buffer;				// pointer to actual storage
	RuntimeSymbolTableList *next;		// pointer to next runtime symbol table list
};


//Data structure for runtime storage
typedef struct _RuntimeStorage RuntimeStorage;

struct _RuntimeStorage
{
	RuntimeSymbolTableList *symtablist; // pointer to the symbol table list
};

//Function declaration for runtime storage management
RuntimeStorage *RuntimeStorage_Create();
int RuntimeStorage_Destroy(RuntimeStorage *storage);

int RuntimeStorage_AddSymbolTable(RuntimeStorage *storage, SymbolTable *symtab);
int RuntimeStorage_RemoveSymbolTable(RuntimeStorage *storage, SymbolTable *symtab);


/*
The following data structure will be used to support activation record information
which are not fully developed and not used in the univ project.
*/

typedef struct _RunTimeStack RunTimeStack;

struct _RunTimeStack
{
	LONGPARAM *buffer;
	int size;
	LONGPARAM *top;
	LONGPARAM *threshold;
};

extern void *g_RunTime_BP;

RunTimeStack *RunTimeStack_Create(int size);
int RunTimeStack_Destroy(RunTimeStack *stack);

int RunTimeStack_Push(RunTimeStack *stack, LONGPARAM element);
LONGPARAM RunTimeStack_Pop(RunTimeStack *stack);

typedef struct _ActivationRecord ActivationRecord;

struct _ActivationRecord
{
	SymbolTable *prev_table;
	SymbolTable *current_table;
	int return_type;
	RunTimeStack *stack;
	int return_size;
	SymbolTableEntry **actual_params;
	int num_of_param;
	int actual_params_size;
	//void *control_link;
	//void *access_link;
	SymbolTableEntry **local_data;
	int num_of_local_data;
	int local_data_size;
	void *activation_area;
};

ActivationRecord *ActivationRecord_Create();
int ActivationRecord_Destroy(ActivationRecord *activation_record);

int ActivationRecord_SetSymbolTable(ActivationRecord *activation_record, SymbolTable *current_table, SymbolTable *prev_table);
int ActivationRecord_AddParam(ActivationRecord *activation_record, SymbolTableEntry *entry);
int ActivationRecord_SetStack(ActivationRecord *activation_record, RunTimeStack *stack);
int ActivationRecord_Prepare(ActivationRecord *activation_record);
int ActivationRecord_Call(ActivationRecord *activation_record_callee);
int ActivationRecord_Return(ActivationRecord *activation_record_callee);
int ActivationRecord_CleanupCallee(ActivationRecord *activation_record_caller, ActivationRecord *activation_record_callee);


#endif

