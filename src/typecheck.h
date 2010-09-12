/*
File Name : typecheck.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains data structure and defines for typecheck.
*/

#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "common.h"
#include "symtab.h"

//Data type
#define TYPE_VOID			0x1	// void
#define TYPE_INT			0x2	// integer
#define TYPE_SHORT			0x3	// float
#define TYPE_FLOAT			0x4	// float
#define TYPE_DOUBLE			0x5	// double
#define TYPE_CHAR			0x6	// char
#define TYPE_BOOLEAN		0x7	// char
#define TYPE_ARRAY			0x8	// array
#define TYPE_STRUCT			0x9	// structure
#define TYPE_FUNCTION		0xA	// function
#define TYPE_POINTER		0xB	// pointer

#define TYPE_SIZE_VOID		sizeof(void)	// void size
#define TYPE_SIZE_INT		sizeof(int)		// integer size
#define TYPE_SIZE_SHORT		sizeof(short)	// float size
#define TYPE_SIZE_FLOAT		sizeof(float)	// float size
#define TYPE_SIZE_DOUBLE	sizeof(double)	// double size
#define TYPE_SIZE_CHAR		sizeof(char)	// char size
#define TYPE_SIZE_POINTER	sizeof(void *)	// pointer size
#define TYPE_SIZE_BOOLEAN	sizeof(char)	// pointer size


//Data structure for type.
struct _Type
{
	int op;
	int size;
	Type *type;	
	union _Info
	{
		struct _Type_Function
		{
			Type *return_type;
			int num_of_func_param;
			SymbolTable *func_symtab;
			SymbolTableEntry **func_params;
			IntrmdtCodeAccessType *code_access;
		} Type_Function;
		struct _Type_Array
		{
			int nelem;
		} Type_Array;
	} info;
	SymbolTableEntry *entry;
};

struct _TypeEntry
{
	Type *type;
	TypeEntry *next;
};

//Data structure for function
struct _TypeCheck_Function
{
	typevar_type return_type;		// Return type
	int num_of_func_param;			// Number of parameters
	SymbolTable *func_symtab;		// Symbol table entry for the function
	SymbolTableEntry **func_params;	// Symbol table entries for parameters
	IntrmdtCodeAccessType *code_access;	// Pointer to the code access for this function
};

//Data structure for argument in calling a function
struct _ParamInfo
{
	char *name;		// Parameter name
	typevar_type data_type;	// Parameter type
};

extern Type *g_typecheck_void_type, *g_typecheck_int_type;
extern Type *g_typecheck_short_type, *g_typecheck_float_type;
extern Type *g_typecheck_double_type, *g_typecheck_char_type;

/*Function declarations*/

int TypeCheck_Init();
int TypeCheck_Deinit();

int TypeCheck_DestroyType(Type *type);
int TypeCheck_Install_Types();

typevar_type TypeCheck_GetInitialType(ParseNode *node);
int TypeCheck_GetPointerCounter(ParseNode *node);
void TypeCheck_MakeParameterType(ParseNode *node, char **name, int *data_type);
ParamInfo *TypeCheck_GetParam(ParseNode *node, int *num_of_param);
void TypeCheck_HandleFuncParams(ParseNode *node, SymbolTable *symtab, SymbolTableEntry *func_entry, TypeCheck_Function *func);

int TypeCheck_Free_Function(TypeCheck_Function *func);

char *TypeCheck_GetTypeString(int KeyWord);

void TypeCheck_addTypeEntry(Type *type);
Type *TypeCheck_Process_direct_declarator(ParseNode *node, Type *linkType);

#endif
