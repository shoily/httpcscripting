/*
File Name : symtab.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains data structure and defines for symbol table
*/

#ifndef SYMTAB_H
#define SYMTAB_H

#include "common.h"
#include "typecheck.h"

#define SYMBOLTABLE_ENTRY_SUCCESS 0						// Entry is successfully created
#define SYMBOLTABLE_ENTRY_ERROR_ALREADY_EXIST -1	// Entry is already


// Maximum number of characters including null of identifiers in a symbol table
#define SYMBOLTABLE_CHUNK_SIZE	400

#define SYMBOL_CLASS_TYPE						1	// Entry is a type
#define SYMBOL_CLASS_IDENTIFIER				2	// Entry is an identifer
#define SYMBOL_CLASS_KEYWORD					3	// Entry is a keyword
#define SYMBOL_CLASS_LABEL						4	// Entry is a label
#define SYMBOL_CLASS_CONST_INTEGER			5	// Entry is an integer
#define SYMBOL_CLASS_CONST_FLOAT				6	// Entry is a float
#define SYMBOL_CLASS_CONST_CHAR				7	// Entry is a character
#define SYMBOL_CLASS_CONST_STRING			8	// Entry is a string of character
#define SYMBOL_CLASS_CONST_BOOLEAN			9

#define SYMBOL_REQUEST_QUERYSTRING			"Request_QueryString"
#define SYMBOL_RESPONSE_WRITE					"Response_Write"

typedef int (*ParamFreeFuncType) (void *);

//Data structure  of constant value
union const_value_type {
	int i;							// Integer
	char c;							// Character
	float f;						// Float
	char *s;						// String
	LONGPARAM l;
};


//Data structure for symbol table entry
struct _SymbolTableEntry
{
	char *symbol;				// Symbol
	int symbol_class;			// Symbol class
	void *storage;				// Pointer to storage
	typevar_type data_type;		// Data type
	Type *type;					// New Data Type
	SymbolTable *symtab;		// Pointer to symbol table
	union const_value_type const_value;	// Constant value
	char is_param;				// Is it a parameter
	void *param;				// Pointer to extra parameter
	ParamFreeFuncType param_free_func;	// Free function of parameter
	int relative_pos_in_mem;		// Not used in this univ project
	char isPtrIndirection;			// Does pointer indirection happen
	SymbolTableEntry *ptrEntry;		// Pointer to the indirection entry
};

//Data structure for symbol table
struct _SymbolTable
{
	SymbolTable *parent;					// Pointer to parent symbol table
	int chunk_size;						// Chunk size
	char *symbols_chunk;					// Pointer to symbol chunk
	int symbols_chunk_wrote_so_far;	// Index to current write ptr of symbol chunk
	int num_of_entry;						// Number of entries
	SymbolTableEntry **entries;		// Pointer to entries
	int num_of_child;						// Number of symbol table children
	SymbolTable *first_child;			// Pointer to first symbol table child
	SymbolTable *last_child;			// Pointer to last symbol table child
	SymbolTable *prev_sibling;			// Pointer to previous symbol table sibling
	SymbolTable *next_sibling;			// Pointer to next symbol table sibling	
};

extern SymbolTable *g_SymbolTable_RootTable;	// Pointer to root symbol table
extern SymbolTable *g_SymbolTable_CurrentTable;	// Pointer to current symbol table

/*Function declaration for symbol table maniplation */

int SymbolTable_Init();
int SymbolTable_Deinit();

SymbolTable *SymbolTable_Create();
int SymbolTable_Destroy(SymbolTable *symtab);

int SymbolTable_Add(SymbolTable *parent, SymbolTable *new_child);

int SymbolTable_SetCurrentTable(SymbolTable *symtab);

int SymbolTable_Print(SymbolTable *symtab);

SymbolTableEntry *SymbolTable_AddEntry(SymbolTable *symtab, char *symbol, int symbol_class, int *error_code);
SymbolTableEntry *SymbolTable_AddConstEntry(union const_value_type const_value, int symbol_class);

SymbolTableEntry *SymbolTableEntry_Create(SymbolTable *symtab, int symbol_class);
int SymbolTableEntry_Destroy(SymbolTableEntry *entry, int update_symtab);

int SymbolTable_CalculateRelativePos(SymbolTable *symtab);
int SymbolTable_CalculateAllRelativePos(SymbolTable *symtab);

SymbolTableEntry *SymbolTable_LookUp(SymbolTable *symtab, char *symbol, int symbol_class);
SymbolTableEntry *SymbolTable_LookUpConst(union const_value_type const_value, int symbol_class);

int SymbolTableEntry_SetType(SymbolTableEntry *entry, typevar_type type);
int SymbolTableEntry_SetParam(SymbolTableEntry *entry, void *param, ParamFreeFuncType param_free_func);
int SymbolTableEntry_SetDataType(SymbolTableEntry *entry, Type *type);

#endif

