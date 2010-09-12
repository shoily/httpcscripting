/*
File Name : intrmdtcode.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains data structure and defines for intermediate code
*/

#ifndef _INTRMDTCODE_H
#define _INTRMDTCODE_H

#include "common.h"
#include "typecheck.h"

//op code
#define OP_POST_INC						1	// post increment (++)
#define OP_POST_DEC						2	// post decrement (--)
#define OP_ADD							3	// addition
#define OP_SUB							4	// subtraction
#define OP_MUL							5	// multiplication
#define OP_DIV							6	// division
#define OP_MOD							7	// modulus
#define OP_SHL							8	// shift left
#define OP_SHR							9	// shift right
#define OP_ASSIGN						10	// assignment
#define OP_GOTO							11	// goto
#define OP_LT							12	// less than
#define OP_GT							13	// greater than
#define OP_LE							14	// less than or equal to
#define OP_GE							15	// greater than or equal to
#define OP_EQ							16	// equal to
#define OP_NE							17	// not equal to
#define OP_BITOR						18	// bitwise or
#define OP_BITXOR						19	// bitwise xor
#define OP_BITAND						20	// bitwise and
#define OP_CONTINUE						21	// continue
#define OP_INDIRECTION					22  // * (pointer indirection)
#define OP_ADDRESSOF					23  // & (address of)
#define OP_ARRAYACCESS					24	// array element access
#define OP_BREAK						25	// break
#define OP_PARAM						26	// used in argument for calling a fucntion
#define OP_CALL							27	// call a function
#define OP_RETURN						28	// return
#define OP_REQUEST_QUERYSTRING			29	// Request_QueryString
#define OP_RESPONSE_WRITE				30	// Response_Write
#define OP_SYMBOLTABLE_ADD				31	// symbol table add
#define OP_SYMBOLTABLE_REMOVE			32	// symbol table remove
#define OP_END							33	// end
#define OP_INTTOFLOAT					34	// integer to float
#define OP_CHARTOINT					35	// character to integer
#define OP_CHARTOFLOAT					36	// character to float
#define OP_INTTOCHAR					37	// integer to character
#define OP_FLOATTOCHAR					38	// float to character
#define OP_FLOATTOINT					39	// float to integer
#define OP_UNARYMINUS					40	// (-) unary minus
#define OP_ONESCOMPLEMENT				41  // ~ (one's complement)
#define OP_LOGICALNEGATION				42	// ! (logical negation)

//Instruction of goto to a line is three kinds
#define GOTO_ABSOLUTE		1	// Goto to the line number specified
#define GOTO_FORWARD		2	// Goto to the line forward from this line specifier
#define GOTO_BACKWARD		3	// Goto to the line backward from this line specifier

#define DEFAULT_NUM_OF_TAC_IN_CODEHOLDER 6	// Number of three-address code in a code holder


//Data structure for three-address code
typedef struct _ThreeAddressCode ThreeAddressCode;

struct _ThreeAddressCode
{
	int op_code;			// op code
	LONGPARAM operand1;	// operand1
	LONGPARAM operand2;	// operand2
	LONGPARAM result;		// result
	int line_num;			// line number
};

//Data structure for intermediate code holder
typedef struct _IntrmdtCodeHolderType IntrmdtCodeHolderType;

struct _IntrmdtCodeHolderType
{
	ThreeAddressCode *code;			// Pointer to three address code
	int num_of_line;					// Number of codes can be accommodate in this code holder
	int current_index;				// Number of code filled in this code holder so far
	IntrmdtCodeHolderType *next;	// Pointer to the next code holder
};


//Data structure for allocated code holder list
typedef struct _IntrmdtCodeHolderAllocatedListType IntrmdtCodeHolderAllocatedListType;

struct _IntrmdtCodeHolderAllocatedListType
{
	IntrmdtCodeHolderType *code_holder;				// Pointer to the allocated code holder
	IntrmdtCodeHolderAllocatedListType *next;		// Pointer to the next list
};

//Data structure to access code
struct _IntrmdtCodeAccessType
{
	IntrmdtCodeHolderType *first_code_holder;			// Pointer to first code holder
	IntrmdtCodeHolderType *current_code_holder;		// Pointer to current code holder
	IntrmdtCodeHolderAllocatedListType *allocated_code_holder_list;	// Pointer to allocated code holder list
};

//Function declarations for code holder
IntrmdtCodeAccessType *IntrmdtCodeHolder_Create();
int IntrmdtCodeHolder_Destroy(IntrmdtCodeAccessType *code_access);
int IntrmdtCodeHolder_Emit(IntrmdtCodeAccessType *code_access, int op_code, LONGPARAM operand1, LONGPARAM operand2, LONGPARAM result);
int IntrmdtCodeHolder_EmitOp1(IntrmdtCodeAccessType *code_access, int op_code, LONGPARAM operand1);
int IntrmdtCodeHolder_AppendCode(IntrmdtCodeAccessType *code_access_in, IntrmdtCodeAccessType *code_access_from);
int IntrmdtCodeHolder_CheckSpace(IntrmdtCodeAccessType *code_access);
int IntrmdtCode_AttachCodeAccessAttribute(ParseNode *node, IntrmdtCodeAccessType *code_access);

//Function declarations for intermediate code
ParseNode *IntrmdtCode_QueryNode(ParseNode *node, int nonterminal);
int IntrmdtCode_PopulateCode(ParseNode *node);
int IntrmdtCode_ProcessBinaryArithmeticOperation(ParseNode *node, int op_code);
int IntrmdtCode_ProcessUnaryOperation(ParseNode *node);
int IntrmdtCode_ProcessAssignmentExpression(ParseNode *node, SymbolTableEntry *lvalue_entry, SymbolTableEntry *rvalue_entry, IntrmdtCodeAccessType *lvalue_code_access, IntrmdtCodeAccessType *rvalue_code_access, int terminal, char isPostfix);
int IntrmdtCode_ConvertType(IntrmdtCodeAccessType *code_access, SymbolTableEntry **operand1_entry, SymbolTableEntry **operand2_entry, SymbolTableEntry *result_entry);

int IntrmdtCode_Init();
int IntrmdtCode_Deinit();

int IntrmdtCode_GenerateLineNumber();
int IntrmdtCode_Backpatch();

int IntrmdtCode_Print(ParseNode *node);
int IntrmdtCode_PrintVerbose(ParseNode *node);

//Data structure for label link
typedef struct _IntrmdtLabelLinkType IntrmdtLabelLinkType;

struct _IntrmdtLabelLinkType
{
	IntrmdtCodeHolderType *code_holder;	// Pointer to code holder
	int code_index;							// Code index
	IntrmdtLabelLinkType *next;			// Pointer to the next list
};

typedef struct _IntrmdtLabelType IntrmdtLabelType;

//Data structure for label
struct _IntrmdtLabelType
{
	IntrmdtCodeHolderType *label_pos_code_holder;	// Code holder for the label
	int label_pos_code_index;						// Code index for the label
	IntrmdtLabelLinkType *label_link;				// Pointer to the label link
	char next_instruction;							// Points to the next instruction
};

//Data structure for label list
typedef struct _IntrmdtLabelListType IntrmdtLabelListType;

struct _IntrmdtLabelListType
{
	IntrmdtLabelType *label;		// Pointer to label
	IntrmdtLabelListType *next;	// Pointer to the next label list
};

//Function declaration for the intermediate label
IntrmdtLabelType *IntrmdtLabel_Create();
int IntrmdtLabel_Destroy(IntrmdtLabelType *label);

int IntrmdtLabel_SetLabelPos(IntrmdtLabelType *label, IntrmdtCodeHolderType *code_holder, int code_index);
int IntrmdtLabel_SetNextInstructionLabelPos(IntrmdtLabelType *label, IntrmdtCodeHolderType *code_holder, int code_index);
int IntrmdtLabel_AddToGotoList(IntrmdtLabelType *label,  IntrmdtCodeHolderType *code_holder, int code_index);
int IntrmdtLabel_UpdateGlobalLabelList(IntrmdtLabelType *label);

#endif

