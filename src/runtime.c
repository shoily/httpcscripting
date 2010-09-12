/*
File Name : runtime.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Handles runtime memory. Entering a function/compound block
causes storage space to be needed for their variables. So leaving the function/compound block
needs those storage to be destroyed. This file contains functions to achive those task.
*/

#include "runtime.h"


RuntimeStorage *RuntimeStorage_Create()
{
/*
Pre : None
Post : Runtime storage object is created
*/

	RuntimeStorage *storage;

	storage = (RuntimeStorage *) calloc(1, sizeof(RuntimeStorage));

	return storage;
}

int RuntimeStorage_Destroy(RuntimeStorage *storage)
{
/*
Pre : Runtime storage object to be destroyed is supplied
Post : Destroyes runtime storage object
*/

	RuntimeSymbolTableList *symtablist, *remove_symtablist;

	//if(storage->data_buffer) free(storage->data_buffer);
	symtablist = storage->symtablist;
	while(symtablist)
	{
		remove_symtablist = symtablist;
		symtablist = symtablist->next;
		if(remove_symtablist->data_buffer) free(remove_symtablist->data_buffer);
		free(remove_symtablist);
	}

	free(storage);
	return 0;
}

int RuntimeStorage_AddSymbolTable(RuntimeStorage *storage, SymbolTable *symtab)
{
/*
Pre : Adds symbol table to the storage
Post : Allocating memory for the variables of the symbol table and sets their storage
*/

	RuntimeSymbolTableList *symtablist;
	int storage_size = 0;
	int i, j;

	symtablist = (RuntimeSymbolTableList *) calloc(1, sizeof(RuntimeSymbolTableList));
	symtablist->symtab = symtab;
	symtablist->next = storage->symtablist;
	storage->symtablist = symtablist;

	//printf("Add symbol table : %p\n", symtab);

	for(i=0;i<symtab->num_of_entry;i++)
	{
		//if(symtab->entries[i]->symbol_class==SYMBOL_CLASS_IDENTIFIER)
		//	printf("Symbol : %s\n", symtab->entries[i]->symbol);
		if(symtab->entries[i]->symbol_class!=SYMBOL_CLASS_IDENTIFIER)
			continue;

		//storage_size += sizeof(LONGPARAM);
		storage_size += symtab->entries[i]->type->size;
	}

	symtablist->storage_size = storage_size;

	symtablist->data_buffer = (void *) malloc(symtablist->storage_size);

	for(i=0, j=0;i<symtab->num_of_entry;i++)
	{
		if(symtab->entries[i]->symbol_class==SYMBOL_CLASS_IDENTIFIER)
		{
			symtab->entries[i]->storage = (void *) ( (int) symtablist->data_buffer + j);
			j += symtab->entries[i]->type->size;
		}
	}
	//symtablist->storage_size = storage_size;

	return 0;
}

int RuntimeStorage_RemoveSymbolTable(RuntimeStorage *storage, SymbolTable *symtab)
{
/*
Pre : Symbol table to be removed from storage
Post : Deallocates memory for variables of supplied the symbol table
*/

	RuntimeSymbolTableList *symtablist, *prev_symtablist = NULL;

	symtablist = storage->symtablist;

	//printf("Remove symbol table : %p\n", symtab);

	while(symtablist)
	{
		if(symtablist->symtab == symtab)
		{
			//storage->storage_size -= symtablist->storage_size;
			if(prev_symtablist==NULL)
				storage->symtablist = symtablist->next;
			else
				prev_symtablist->next = symtablist->next;

			if(symtablist->data_buffer) free(symtablist->data_buffer);
			free(symtablist);
			return 0;
		}
		prev_symtablist = symtablist;
		symtablist = symtablist->next;
	}

	return -1;
}

/*
As this version of univ project does not support calling of function (other than
built-in functions), the following functions are not needed. They are here for future support
*/

RunTimeStack *RunTimeStack_Create(int size)
{
	RunTimeStack *stack;

	stack = (RunTimeStack *) calloc(1, sizeof(RunTimeStack));
	stack->buffer = (LONGPARAM *) calloc(1, size * sizeof(LONGPARAM));
	stack->top = stack->buffer;
	stack->threshold = (LONGPARAM *) ((int) stack->buffer + ((size * sizeof(LONGPARAM)) - sizeof(LONGPARAM)));
	stack->size = size * sizeof(LONGPARAM);

	return stack;
}

int RunTimeStack_Destroy(RunTimeStack *stack)
{
	free(stack->buffer);
	free(stack);

	return 0;
}

int RunTimeStack_Push(RunTimeStack *stack, LONGPARAM element)
{
	if(stack->top == stack->threshold)
		exit(1);

	*stack->top = element;
	stack->top++;

	return 0;
}

LONGPARAM RunTimeStack_Pop(RunTimeStack *stack)
{
	LONGPARAM elem;

	if(stack->top < stack->buffer)
		exit(1);

	elem = *stack->top;
	stack->top--;
	return 0;
}

ActivationRecord *ActivationRecord_Create()
{
	ActivationRecord *activation_record;

	activation_record = (ActivationRecord *) calloc(1, sizeof(ActivationRecord));

	return activation_record;
}

int ActivationRecord_Destroy(ActivationRecord *activation_record)
{
	if(activation_record->activation_area) free(activation_record->activation_area);
	if(activation_record->actual_params) free(activation_record->actual_params);
	free(activation_record);

	return 0;
}

int ActivationRecord_SetSymbolTable(ActivationRecord *activation_record, SymbolTable *current_table, SymbolTable *prev_table)
{
	activation_record->current_table = current_table;
	activation_record->prev_table = prev_table;

	return 0;
}

int ActivationRecord_AddParam(ActivationRecord *activation_record, SymbolTableEntry *entry)
{
	activation_record->actual_params = realloc(activation_record, sizeof(SymbolTableEntry *) * (activation_record->num_of_param + 1));

	activation_record->actual_params[activation_record->num_of_param] = entry;
	activation_record->num_of_param++;

	return 0;
}

int ActivationRecord_SetStack(ActivationRecord *activation_record, RunTimeStack *stack)
{
	activation_record->stack = stack;

	return 0;
}

int ActivationRecord_Prepare(ActivationRecord *activation_record)
{
	int total_size = 0, i;

	//total_size += RunTime_GetSize(
	//for(i=0; i<activation_record->num_of_param;i++)
	//	total_size += RunTime_GetSize(entry[i].data_type);



	return 0;
}

