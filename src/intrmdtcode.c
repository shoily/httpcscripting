/*
File Name : intrmdtcode.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Program to generate intermediate code. It employes three-address
code scheme. Also intermediate codes are stored in code holder for a given nonterminal
and its pointer is stored in the corresponding node's "Code" attribute. Also,
expression's symbol table entry is stored in the "Place" attribute.
*/

#include <stdio.h>
#include "intrmdtcode.h"
#include "tree.h"
#include "symtab.h"
#include "c-bison_tab.h"
#include "typecheck.h"

static SymbolTableEntry *g_IntrmdtCode_TRUE=NULL; // Symbol table entry for 'true' (1)
static SymbolTableEntry *g_IntrmdtCode_FALSE=NULL; // Symbol table entry for 'false' (0)
static SymbolTableEntry *g_IntrmdtCode_CHAR_1=NULL; // Symbol table entry for character 1
static SymbolTableEntry *g_IntrmdtCode_CHAR_NEG_1=NULL; // Symbol table entry for character 0

//static int g_IntrmdtCode_is_statement = COMPILER_NO;

IntrmdtCodeAccessType *IntrmdtCodeHolder_Create()
{
/*
Pre : Code storage.
Post : Creates IntermdtCodeAccessType object and returns
*/

	IntrmdtCodeAccessType *code_access;

	code_access = (IntrmdtCodeAccessType *) calloc(1, sizeof(IntrmdtCodeAccessType));

	//printf("Code Holder Create : %d\n", code_access);

	return code_access;
}

int IntrmdtCodeHolder_Destroy(IntrmdtCodeAccessType *code_access)
{
/*
Pre : IntrmdtCodeAccessType object exists
Post : Destroys the object along with all the code associated with it
*/

	IntrmdtCodeHolderAllocatedListType *allocated_code_holder_list, *remove_allocated_code_holder_list;

	allocated_code_holder_list = code_access->allocated_code_holder_list;

	while(allocated_code_holder_list)
	{
		remove_allocated_code_holder_list = allocated_code_holder_list;
		allocated_code_holder_list = allocated_code_holder_list->next;
		if(remove_allocated_code_holder_list->code_holder->code)
			free(remove_allocated_code_holder_list->code_holder->code);
		if(remove_allocated_code_holder_list->code_holder)
			free(remove_allocated_code_holder_list->code_holder);
		free(remove_allocated_code_holder_list);
	}
	free(code_access);

	return 0;
}

int IntrmdtCodeHolder_CheckSpace(IntrmdtCodeAccessType *code_access)
{
/*
Pre : Before each Emit, space is checked.
Post : If the code holder is full, then new code holder is created.
*/

	if(code_access->first_code_holder==NULL || code_access->current_code_holder->current_index >= code_access->current_code_holder->num_of_line)
	{
		IntrmdtCodeHolderType *new_code_holder;
		IntrmdtCodeHolderAllocatedListType *allocated_code_holder_list;

		new_code_holder = (IntrmdtCodeHolderType *) calloc(1, sizeof(IntrmdtCodeHolderType));
		new_code_holder->code = (ThreeAddressCode *) malloc(DEFAULT_NUM_OF_TAC_IN_CODEHOLDER * sizeof(ThreeAddressCode));
		memset(new_code_holder->code, '\0', DEFAULT_NUM_OF_TAC_IN_CODEHOLDER * sizeof(ThreeAddressCode));

		//printf("CALLOC IN CHECKSPACE : %p, %p, %p, %d\n", code_access, new_code_holder, new_code_holder->code, DEFAULT_NUM_OF_TAC_IN_CODEHOLDER);

		if(code_access->first_code_holder==NULL)
		{
			code_access->first_code_holder = code_access->current_code_holder = new_code_holder;
		}
		else
		{
			code_access->current_code_holder->next = new_code_holder;
			code_access->current_code_holder = new_code_holder;
			code_access->current_code_holder->next = NULL;
		}
		new_code_holder->num_of_line = DEFAULT_NUM_OF_TAC_IN_CODEHOLDER;
		new_code_holder->current_index = 0;
		allocated_code_holder_list = (IntrmdtCodeHolderAllocatedListType *) calloc(1, sizeof(IntrmdtCodeHolderAllocatedListType));
		allocated_code_holder_list->code_holder = new_code_holder;
		allocated_code_holder_list->next = code_access->allocated_code_holder_list;
		code_access->allocated_code_holder_list = allocated_code_holder_list;
	}
	return 0;
}

int IntrmdtCodeHolder_Emit(IntrmdtCodeAccessType *code_access, int op_code, LONGPARAM operand1, LONGPARAM operand2, LONGPARAM result)
{
/*
Pre : Emits three address code
Post : Three address code is emitted
*/

	IntrmdtCodeHolder_CheckSpace(code_access);
	code_access->current_code_holder->code[code_access->current_code_holder->current_index].op_code = op_code;
	code_access->current_code_holder->code[code_access->current_code_holder->current_index].operand1 = operand1;
	code_access->current_code_holder->code[code_access->current_code_holder->current_index].operand2 = operand2;
	code_access->current_code_holder->code[code_access->current_code_holder->current_index].result = result;
	//code_access->current_code_holder->code[code_access->current_code_holder->current_index].line_num = ++g_IntrmdtCode_CodeLineNumber;
	code_access->current_code_holder->current_index++;

	return 0;
}

int IntrmdtCodeHolder_EmitOp1(IntrmdtCodeAccessType *code_access, int op_code, LONGPARAM operand1)
{
/*
Pre : Emits three address code with one operand
Post : Three adress code is emitted
*/

	return IntrmdtCodeHolder_Emit(code_access, op_code, operand1, 0, 0);
}

int IntrmdtCodeHolder_AppendCode(IntrmdtCodeAccessType *code_access_in, IntrmdtCodeAccessType *code_access_from)
{
/*
Pre : Code access from which the code to be copied, and into where the code be copied
are supplied
Post : Codes are appended in the first supplied code access from the second
*/

	int i;
	IntrmdtCodeHolderType *code_holder_from, *code_holder_in;	

	if(code_access_in==NULL || code_access_from==NULL)
		return 0;

	if(code_access_from && code_access_from->first_code_holder && code_access_from->first_code_holder->current_index==0)
		return 0;

	if(code_access_in->first_code_holder==NULL || code_access_in->first_code_holder->current_index==0)
	{
		/*if(code_access_in->first_code_holder!=NULL)
		{
			free(code_access_in->first_code_holder->code);
			free(code_access_in->first_code_holder);
		}*/
		code_access_in->first_code_holder = code_access_in->current_code_holder = code_access_from->first_code_holder;
		//code_access_in->last_code_holder = NULL;
	}
	else
	{
		code_access_in->current_code_holder->next = code_access_from->first_code_holder;
	}

	while(code_access_in->current_code_holder && code_access_in->current_code_holder->next)
		code_access_in->current_code_holder = code_access_in->current_code_holder->next;

	return 0;

	code_holder_from = code_access_from->first_code_holder;

	//printf("IntrmdtCodeHolder_AppendCode START : %d, %d\n", code_access_in, code_access_from);
	while(code_holder_from)
	{
		code_holder_in = (IntrmdtCodeHolderType *) calloc(1, sizeof(IntrmdtCodeHolderType));
		code_holder_in->code = (ThreeAddressCode *) calloc(1, sizeof(ThreeAddressCode) * code_holder_from->current_index);
		code_holder_in->current_index = code_holder_from->current_index;
		code_holder_in->num_of_line = code_holder_in->current_index;
		//printf("IntrmdtCodeHolder_AppendCode info : %d\n", code_holder_from->current_index);
		for(i=0;i<code_holder_from->current_index;i++)
		{
			code_holder_in->code[i].op_code = code_holder_from->code[i].op_code;
			code_holder_in->code[i].operand1 = code_holder_from->code[i].operand1;
			code_holder_in->code[i].operand2 = code_holder_from->code[i].operand2;
			code_holder_in->code[i].result = code_holder_from->code[i].result;
			code_holder_in->code[i].line_num = code_holder_from->code[i].line_num;
		}
		if(code_access_in->current_code_holder==NULL)
		{
			code_access_in->first_code_holder = code_access_in->current_code_holder = code_holder_in;
		}
		else
			code_access_in->current_code_holder->next = code_holder_in;
		code_access_in->current_code_holder = code_holder_in;

		code_holder_from = code_holder_from->next;
	}

	//printf("IntrmdtCodeHolder_AppendCode END\n");

	return 0;
}
extern char * const yynonterminalname[];

int IntrmdtCode_AttachCodeAccessAttribute(ParseNode *node, IntrmdtCodeAccessType *code_access)
{
/*
Pre : Created (not inherited) code access object is supplied.
Post : Helper function to attach code access attribute and which is to be freed
when freeing this attribute
*/

	IntrmdtCodeAccessType *check_code_access;
	TreeAttribute *attribute;
	attribute = Tree_AttachAttribute(node, ATTRIB_CODE, (LONGPARAM) code_access, sizeof(IntrmdtCodeAccessType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
	TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtCodeHolder_Destroy);
	check_code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node, ATTRIB_CODE);
	//printf("AttachCodeAccess : Node : %s, code_access : %d, check : %d, index : %d\n", yynonterminalname[node->terminal_nonterminal-1], code_access, check_code_access, code_access->first_code_holder->current_index);
}

#define INTRMDTCODE_TEMPVAR_PREFIX		"###TEMP"	// Temporary variable prefix
static g_IntrmdtCode_CurrentTempUsed = 0;				// Number of temporary variable used

SymbolTableEntry *IntrmdtCode_GetNewTempVariable(SymbolTable *symtab, Type *type)
{
/*
Pre : Symbol table in which the temporary variable to be entered
Post : Creates temporary variable in the supplied symbol table
*/

	SymbolTableEntry *temp_entry;
	char temp_var_name[100];

	g_IntrmdtCode_CurrentTempUsed++;

	sprintf(temp_var_name, "%s%d", INTRMDTCODE_TEMPVAR_PREFIX, g_IntrmdtCode_CurrentTempUsed);
	temp_entry = SymbolTable_AddEntry(symtab, temp_var_name, SYMBOL_CLASS_IDENTIFIER, NULL);
	temp_entry->type = type;

	return temp_entry;
}

int IntrmdtCode_ForceType(IntrmdtCodeAccessType *code_access, SymbolTableEntry **force_entry, SymbolTableEntry **converted_entry)
{
	Type *type = NULL;
	SymbolTableEntry *temp_entry;
	int op;
	int force_type_op, converted_type_op;

	switch((*converted_entry)->symbol_class)
	{
		case SYMBOL_CLASS_IDENTIFIER: converted_type_op = (*converted_entry)->type->op; break;
		case SYMBOL_CLASS_CONST_INTEGER: converted_type_op = TYPE_INT; break;
		case SYMBOL_CLASS_CONST_FLOAT: converted_type_op = TYPE_FLOAT; break;
		case SYMBOL_CLASS_CONST_CHAR: converted_type_op = TYPE_CHAR; break;
		default: return 0;
	}

	force_type_op = (*force_entry)->type->op;
		

	if(force_type_op == converted_type_op)
		return 0;

	if(force_type_op==TYPE_INT && converted_type_op==TYPE_FLOAT)
	{
		type = g_typecheck_int_type;
		op = OP_FLOATTOINT;
	}
	else if(force_type_op==TYPE_FLOAT && converted_type_op==TYPE_INT)
	{
		type = g_typecheck_float_type;		
		op = OP_INTTOFLOAT;
	}
	else if(force_type_op==TYPE_CHAR && converted_type_op==TYPE_INT)
	{
		type = g_typecheck_char_type;
		op = OP_INTTOCHAR;
	}
	else if(force_type_op==TYPE_INT && converted_type_op==TYPE_CHAR)
	{
		type = g_typecheck_int_type;		
		op = OP_CHARTOINT;
	}
	else if(force_type_op==TYPE_CHAR && converted_type_op==TYPE_FLOAT)
	{
		type = g_typecheck_char_type;
		op = OP_FLOATTOCHAR;
	}
	else if(force_type_op==TYPE_FLOAT && converted_type_op==TYPE_CHAR)
	{
		type = g_typecheck_float_type;
		op = OP_CHARTOFLOAT;
	}
	
	if(type)
	{
		temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
		IntrmdtCodeHolder_Emit(code_access, op, (LONGPARAM) *converted_entry, (LONGPARAM) NULL, (LONGPARAM) temp_entry);
		*converted_entry = temp_entry;
	}

	return 0;
}

int IntrmdtCode_ConvertType(IntrmdtCodeAccessType *code_access, SymbolTableEntry **operand1_entry, SymbolTableEntry **operand2_entry, SymbolTableEntry *result_entry)
{
/*
Pre : Helper function to convert types.
Post :
*/

	SymbolTableEntry *temp_entry, **converted_entry;
	Type *type = NULL;
	int op;

	/*data_type = (*operand1_entry)->data_type;*/
	int operand1_type_op, operand2_type_op;

	switch((*operand1_entry)->symbol_class)
	{
		case SYMBOL_CLASS_IDENTIFIER: operand1_type_op = (*operand1_entry)->type->op; break;
		case SYMBOL_CLASS_CONST_INTEGER: operand1_type_op = TYPE_INT; break;
		case SYMBOL_CLASS_CONST_FLOAT: operand1_type_op = TYPE_FLOAT; break;
		case SYMBOL_CLASS_CONST_CHAR: operand1_type_op = TYPE_CHAR; break;
		default: return 0;
	}

	switch((*operand2_entry)->symbol_class)
	{
		case SYMBOL_CLASS_IDENTIFIER: operand2_type_op = (*operand2_entry)->type->op; break;
		case SYMBOL_CLASS_CONST_INTEGER: operand2_type_op = TYPE_INT; break;
		case SYMBOL_CLASS_CONST_FLOAT: operand2_type_op = TYPE_FLOAT; break;
		case SYMBOL_CLASS_CONST_CHAR: operand2_type_op = TYPE_CHAR; break;
		default: return 0;
	}

	if(operand1_type_op == operand2_type_op)
		return 0;

	if(operand1_type_op==TYPE_INT && operand2_type_op==TYPE_FLOAT)
	{
		type = g_typecheck_float_type;
		converted_entry = operand1_entry;
		op = OP_INTTOFLOAT;
	}
	else if(operand1_type_op==TYPE_FLOAT && operand2_type_op==TYPE_INT)
	{
		type = g_typecheck_float_type;		
		converted_entry = operand2_entry;
		op = OP_INTTOFLOAT;
	}
	else if(operand1_type_op==TYPE_CHAR && operand2_type_op==TYPE_INT)
	{
		type = g_typecheck_int_type;
		converted_entry = operand1_entry;
		op = OP_CHARTOINT;
	}
	else if(operand1_type_op==TYPE_INT && operand2_type_op==TYPE_CHAR)
	{
		type = g_typecheck_int_type;		
		converted_entry = operand2_entry;
		op = OP_CHARTOINT;
	}
	else if(operand1_type_op==TYPE_CHAR && operand2_type_op==TYPE_FLOAT)
	{
		type = g_typecheck_float_type;
		converted_entry = operand1_entry;
		op = OP_CHARTOFLOAT;
	}
	else if(operand1_type_op==TYPE_FLOAT && operand2_type_op==TYPE_CHAR)
	{
		type = g_typecheck_float_type;
		converted_entry = operand2_entry;
		op = OP_CHARTOFLOAT;
	}

	if(type)
	{
		temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
		IntrmdtCodeHolder_Emit(code_access, op, (LONGPARAM) *converted_entry, (LONGPARAM) NULL, (LONGPARAM) temp_entry);
		*converted_entry = temp_entry;
		if(result_entry)
			result_entry->type = type;
	}
	/*SymbolTableEntry_SetType(result_entry, data_type);*/

	return 0;
}

int IntrmdtCode_ProcessBinaryBooleanOperation(ParseNode *node, int op_code)
{
/*
Pre : Node (corresponding to a nonterminal) into which the code to be created. op_code supplied.
Post : Generates code for boolean operation.
*/

	SymbolTableEntry *temp_entry, *operand1_entry, *operand2_entry;
	IntrmdtCodeAccessType *code_access, *code_access_child1, *code_access_child2;

	operand1_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
	operand2_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_PLACE);

	temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, g_typecheck_char_type);

	code_access = IntrmdtCodeHolder_Create();	

	code_access_child1 = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
	code_access_child2 = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);

	IntrmdtCodeHolder_AppendCode(code_access, code_access_child1);
	IntrmdtCodeHolder_AppendCode(code_access, code_access_child2);

	IntrmdtCode_ConvertType(code_access, &operand1_entry, &operand2_entry, temp_entry);

	IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) temp_entry, (LONGPARAM) g_IntrmdtCode_TRUE, (LONGPARAM) 0);
	IntrmdtCodeHolder_Emit(code_access, op_code, (LONGPARAM) operand1_entry, (LONGPARAM) operand2_entry, (LONGPARAM) 0);
	IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) GOTO_FORWARD, (LONGPARAM) 2, (LONGPARAM) 0);
	IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) temp_entry, (LONGPARAM) g_IntrmdtCode_FALSE, (LONGPARAM) 0);

	IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
	Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) temp_entry, sizeof(SymbolTableEntry *), 0, 0);

	//printf("ProcessBinaryBooleanOperation : %d, %d\n", operand1_entry, operand2_entry);
	return 0;
}

int IntrmdtCode_ProcessBinaryArithmeticOperation(ParseNode *node, int op_code)
{
/*
Pre : Node (corresponding to a nonterminal) into which the code to be created. op_code supplied.
Post : Generates code for arithmetic operation.
*/

	SymbolTableEntry *temp_entry, *operand1_entry, *operand2_entry;
	IntrmdtCodeAccessType *code_access, *code_access_child1, *code_access_child2;

	operand1_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
	operand2_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_PLACE);

	code_access = IntrmdtCodeHolder_Create();

	temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, operand1_entry->type);

	/*printf("BinArithConst : %s\t%s\t%s\t%d\t%d\t%d\t%d\n", yynonterminalname[node->terminal_nonterminal-1],
	yynonterminalname[node->first_child->terminal_nonterminal-1],
	yynonterminalname[node->first_child->next_sibling->next_sibling->terminal_nonterminal-1],
	op_code, (int)operand1_entry, (int)operand2_entry, temp_entry);*/

	code_access_child1 = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
	code_access_child2 = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);

	IntrmdtCodeHolder_AppendCode(code_access, code_access_child1);
	IntrmdtCodeHolder_AppendCode(code_access, code_access_child2);

	IntrmdtCode_ConvertType(code_access, &operand1_entry, &operand2_entry, temp_entry);

	IntrmdtCodeHolder_Emit(code_access, op_code, (LONGPARAM) operand1_entry, (LONGPARAM) operand2_entry, (LONGPARAM) temp_entry);

	IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
	Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) temp_entry, sizeof(SymbolTableEntry *), 0, 0);

	return 0;
}

int IntrmdtCode_ProcessUnaryOperation(ParseNode *node)
{
/*
Pre : Node (corresponding to a nonterminal) into which the code to be created. op_code supplied.
Post : Generates code for unary operation.
*/

	SymbolTableEntry *temp_entry = NULL;
	IntrmdtCodeAccessType *code_access, *code_access_child1;

	int op_code = 0;
	SymbolTableEntry *cast_entry;
	Type *type = NULL;

	cast_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_PLACE);

	switch(node->first_child->first_child->terminal_nonterminal)
	{
		case '&':
		{
			Type newType;

			memset(&newType, '\0', sizeof(Type));

			op_code = OP_ADDRESSOF;
			newType.op = TYPE_POINTER;			

			type = TypeCheck_CreateType(&newType, cast_entry->type);
			temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
		} break;
		case '*':
		{
			op_code = OP_INDIRECTION;
			type = cast_entry->type->type;
			temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
			temp_entry->isPtrIndirection = 1;
			temp_entry->ptrEntry = cast_entry;
		} break;
		case '-':
		{
			op_code = OP_UNARYMINUS;
			type = cast_entry->type;
			temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
		} break;
		case '~':
		{
			op_code = OP_ONESCOMPLEMENT;
			type = cast_entry->type;
			temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
		} break;
		case '!':
		{
			op_code = OP_LOGICALNEGATION;
			type = cast_entry->type;
			temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
		} break;
		default: return;
	}

	code_access = IntrmdtCodeHolder_Create();
	code_access_child1 = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);

	IntrmdtCodeHolder_AppendCode(code_access, code_access_child1);
	IntrmdtCodeHolder_Emit(code_access, op_code, (LONGPARAM) cast_entry, (LONGPARAM) 0, (LONGPARAM) temp_entry);

	IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
	Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) temp_entry, sizeof(SymbolTableEntry *), 0, 0);

	return 0;
}

int IntrmdtCode_ProcessAssignmentExpression(ParseNode *node, SymbolTableEntry *lvalue_entry, SymbolTableEntry *rvalue_entry, IntrmdtCodeAccessType *lvalue_code_access, IntrmdtCodeAccessType *rvalue_code_access, int terminal, char isPostfix)
{
/*
Pre : Processes assignment expression
Post : Generates code for all kinds of assignment expression.
*/

	SymbolTableEntry *temp_entry;
	IntrmdtCodeAccessType *code_access;
	int op_code, result = 0;

	code_access = IntrmdtCodeHolder_Create();

	IntrmdtCodeHolder_AppendCode(code_access, rvalue_code_access);
	IntrmdtCodeHolder_AppendCode(code_access, lvalue_code_access);

	switch(terminal)
	{
		case '=':
		{
			IntrmdtCode_ForceType(code_access, &lvalue_entry, &rvalue_entry);
			IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) lvalue_entry, (LONGPARAM) rvalue_entry, (LONGPARAM) result);
			IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
			Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) lvalue_entry, sizeof(SymbolTableEntry *), 0, 0);
			return;
		} break;
		case ASSIGNMENT_MUL: op_code = OP_MUL; break;
		case ASSIGNMENT_DIV: op_code = OP_DIV; break;
		case ASSIGNMENT_PERCENT: op_code = OP_MOD; break;
		case ASSIGNMENT_PLUS: op_code = OP_ADD; break;
		case ASSIGNMENT_MINUS: op_code = OP_SUB; break;
		case ASSIGNMENT_SHL: op_code = OP_SHL; break;
		case ASSIGNMENT_SHR: op_code = OP_SHR; break;
		case ASSIGNMENT_AND: op_code = OP_BITAND; break;
		case ASSIGNMENT_XOR: op_code = OP_BITXOR; break;
		case ASSIGNMENT_OR: op_code = OP_BITOR; break;
	}

	temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, lvalue_entry->type);

	IntrmdtCode_ForceType(code_access, &lvalue_entry, &rvalue_entry);

	if(lvalue_entry->type->op == TYPE_POINTER)
	{
	}

	if(isPostfix)
	{
		IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) temp_entry, (LONGPARAM) lvalue_entry, (LONGPARAM) 0);
		IntrmdtCodeHolder_Emit(code_access, op_code, (LONGPARAM) lvalue_entry, (LONGPARAM) rvalue_entry, (LONGPARAM) lvalue_entry);
		Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) temp_entry, sizeof(SymbolTableEntry *), 0, 0);
	}
	else
	{
		IntrmdtCodeHolder_Emit(code_access, op_code, (LONGPARAM) lvalue_entry, (LONGPARAM) rvalue_entry, (LONGPARAM) temp_entry);
		IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) lvalue_entry, (LONGPARAM) temp_entry, (LONGPARAM) 0);
		Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) lvalue_entry, sizeof(SymbolTableEntry *), 0, 0);
	}

	IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
	

	return 0;
}

int IntrmdtCode_Init()
{
/*
Pre : None
Post : Initializes intermediate code module
*/

	union const_value_type value;

	value.c = 0;
	g_IntrmdtCode_FALSE = SymbolTable_AddConstEntry(value, SYMBOL_CLASS_CONST_CHAR);
	value.c = 1;
	g_IntrmdtCode_TRUE = SymbolTable_AddConstEntry(value, SYMBOL_CLASS_CONST_CHAR);
	
	value.c = -1;
	g_IntrmdtCode_CHAR_NEG_1 = SymbolTable_AddConstEntry(value, SYMBOL_CLASS_CONST_CHAR);
	g_IntrmdtCode_CHAR_1 = g_IntrmdtCode_TRUE;

	return 0;
}

int IntrmdtCode_Deinit()
{
/*
Pre : None
Post : None
*/

	return 0;
}

int g_IntrmdtCode_LabelNo = 0;

SymbolTableEntry *IntrmdtCode_NewLabel()
{
/*
Pre : None
Post : Creates label. Not used in this univ project version.
*/

	SymbolTableEntry *entry;
	char label_str[100];

	sprintf(label_str, "##LABEL%d", ++g_IntrmdtCode_LabelNo);

	entry = SymbolTable_AddEntry(g_SymbolTable_CurrentTable, label_str, SYMBOL_CLASS_LABEL, NULL);

	return entry;
}

//Helper macro to print codes attached in a node (nonterminal)
#define PRINT_STATEMENT(node)	{IntrmdtCodeAccessType *code_access; IntrmdtCodeHolderType *code_holder; int i;\
										code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node, ATTRIB_CODE); \
										code_holder = code_access->first_code_holder;\
										while(code_holder) {\
											/*for(i=0;i<code_holder->current_index;i++) */ \
												/*printf("Line : %p\t%03d\t%d\t%p\t%p\t%p\n", &code_holder->code[i], code_holder->code[i].line_num, code_holder->code[i].op_code, (int)code_holder->code[i].operand1, (int)code_holder->code[i].operand2, code_holder->code[i].result); */ \
											code_holder = code_holder->next; \
										}}

int IntrmdtCode_PopulateCode(ParseNode *node)
{
/*
Pre : Node for which the code to be generated
Post : "Code" attribute for this node contains generated code.
"Place" attribute for this node contains symbol table entry if the node is
a nonterminal of type expression (not statement).
*/

	ParseNode *child = NULL;
	ParseNode *prev_sibling = NULL;
	ParseNode *searchnode = NULL;

	child = node->first_child;

	switch(node->type)
	{
		case NODE_TERMINAL: break;
		case NODE_NONTERMINAL:
		{
			switch(node->terminal_nonterminal)
			{
				case NONTERMINAL_function_definition:
				{
					SymbolTable *symtab;
					SymbolTableEntry *func_entry;
					ParseNode *func_name_node;

					func_name_node = Tree_QueryFirstNodeDown(node, NONTERMINAL_identifier);

					if((func_entry = SymbolTable_LookUp(g_SymbolTable_CurrentTable, (char *) func_name_node->first_child->value, SYMBOL_CLASS_IDENTIFIER))!=NULL
						&& func_entry->data_type!=0)
					{
						symtab = ((TypeCheck_Function *)(func_entry->param))->func_symtab;
						//printf("Intermediate code : Function definition : %p, %p\n", g_SymbolTable_CurrentTable, symtab);
						SymbolTable_SetCurrentTable(symtab);
						//printf("Func node : %s\n", func_entry->symbol);

						fflush(stdout);
						break;
					}
				} break;
				case NONTERMINAL_compound_statement:
				{
					IntrmdtLabelType *label_stmt_next, *label_stmt_first;
					TreeAttribute *attribute;
					SymbolTable *symtab;

					symtab = (SymbolTable *) Tree_GetAttributeValue(node, ATTRIB_SYMBOLTABLE);
					//printf("Intermediate code : Compound statement : %p, %p\n", g_SymbolTable_CurrentTable, symtab);
					SymbolTable_SetCurrentTable(symtab);

					label_stmt_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT);
					if(label_stmt_next==NULL)
					{
						label_stmt_next = IntrmdtLabel_Create();
						attribute = Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_NEXT, (LONGPARAM) label_stmt_next, sizeof(IntrmdtLabelType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
						TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtLabel_Destroy);
					}
					else
					{
						Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_NEXT, (LONGPARAM) label_stmt_next, sizeof(IntrmdtLabelType *), 0, 0);
					}
					label_stmt_first = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_FIRST);
					//printf("label_stmt_first = %d\n", label_stmt_first);
					//Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_FIRST, (LONGPARAM) label_stmt_first, sizeof(IntrmdtLabelType *), 0, 0);
				} break;
				case NONTERMINAL_statement_list_opt:
				{
					//g_IntrmdtCode_is_statement = COMPILER_YES;
					Tree_AttachAttribute(node->first_child, ATTRIB_STATEMENT_NEXT, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT), sizeof(IntrmdtLabelType *), 0, 0);
					//printf("statement_list_opt : %d\n", (int) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT));
				} break;
				case NONTERMINAL_statement_list:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// statement_list -> statement_list statement
						{
							IntrmdtLabelType *label_stmt_next;
							TreeAttribute *attribute;

							label_stmt_next = IntrmdtLabel_Create();
							attribute = Tree_AttachAttribute(node->first_child, ATTRIB_STATEMENT_NEXT, (LONGPARAM) label_stmt_next, sizeof(IntrmdtLabelType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
							TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtLabel_Destroy);
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_FIRST, (LONGPARAM) label_stmt_next, sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_NEXT, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT), sizeof(IntrmdtLabelType *), 0, 0);

							//printf("statement_list 1 : %d\n", (int) label_stmt_next);
						} break;
						case 2:	// statement_list -> statement
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_STATEMENT_NEXT, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_STATEMENT_FIRST, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_FIRST), sizeof(IntrmdtLabelType *), 0, 0);
							//printf("statement_list 2 : %d\n", (int) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT));
						} break;
					}
				} break;
				case NONTERMINAL_statement:
				{
					Tree_AttachAttribute(node->first_child, ATTRIB_STATEMENT_NEXT, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT), sizeof(IntrmdtLabelType *), 0, 0);
					Tree_AttachAttribute(node->first_child, ATTRIB_STATEMENT_FIRST, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_FIRST), sizeof(IntrmdtLabelType *), 0, 0);
					//printf("statement : %d\n", (int) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT));
				} break;
				case NONTERMINAL_iteration_statement:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// while (expression) statement
						{
							IntrmdtLabelType *label_expr_true, *label_expr_false;
							IntrmdtLabelType *label_stmt_begin, *label_stmt1_next;
							TreeAttribute *attribute;

							label_stmt_begin = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_FIRST);
							label_expr_true = IntrmdtLabel_Create();
							label_expr_false = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT);
							label_stmt1_next = label_stmt_begin;

							//printf("label_expr_false = %d\n", label_expr_false);

							attribute = Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_TRUE, (LONGPARAM) label_expr_true, sizeof(IntrmdtLabelType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
							TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtLabel_Destroy);
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_FALSE, (LONGPARAM) label_expr_false, sizeof(IntrmdtLabelType *), 0, 0);

							//NEW START
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_STATEMENT_FIRST, (LONGPARAM) label_stmt_begin, sizeof(IntrmdtLabelType *), 0, 0);
							//NEW END
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_STATEMENT_NEXT, (LONGPARAM) label_stmt1_next, sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_STATEMENT_BEGIN, (LONGPARAM) label_stmt_begin, sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_selection_statement:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:		// if ( expression ) statement
						{
							IntrmdtLabelType *label_expr_true, *label_expr_false;

							label_expr_true = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_FIRST);
							label_expr_false = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT);

							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, (LONGPARAM) label_expr_true, sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, (LONGPARAM) label_expr_false, sizeof(IntrmdtLabelType *), 0, 0);

							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_NEXT, (LONGPARAM) label_expr_false, sizeof(IntrmdtLabelType *), 0, 0);							
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_FIRST, (LONGPARAM) label_expr_true, sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:		// if ( expression ) statement else statement
						{
							IntrmdtLabelType *label_expr_true, *label_expr_false;
							TreeAttribute *attribute;
							
							label_expr_true = IntrmdtLabel_Create();							
							label_expr_false = IntrmdtLabel_Create();

							attribute = Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, (LONGPARAM) label_expr_true, sizeof(IntrmdtLabelType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
							TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtLabel_Destroy);
							attribute = Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, (LONGPARAM) label_expr_false, sizeof(IntrmdtLabelType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
							TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtLabel_Destroy);

							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_STATEMENT_NEXT, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling->next_sibling, ATTRIB_STATEMENT_NEXT, Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT), sizeof(IntrmdtLabelType *), 0, 0);

							Tree_AttachAttribute(node->first_child, ATTRIB_STATEMENT_FIRST, (LONGPARAM) label_expr_true, sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling->next_sibling, ATTRIB_STATEMENT_FIRST, (LONGPARAM) label_expr_false, sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_declaration_list_opt:
				{
					//g_IntrmdtCode_is_statement = COMPILER_NO;
				} break;
				case NONTERMINAL_logical_OR_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// logical_OR_expression || logical_AND_expression
						{
							IntrmdtLabelType *label_true;
							TreeAttribute *attribute;

							label_true = IntrmdtLabel_Create();
							attribute = Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, (LONGPARAM) label_true, sizeof(IntrmdtLabelType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
							TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtLabel_Destroy);
						} break;
					}
				} break;
				case NONTERMINAL_logical_AND_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// logical_AND_expression && inclusive_OR_expression
						{
							IntrmdtLabelType *label_false;
							TreeAttribute *attribute;

							label_false = IntrmdtLabel_Create();
							attribute = Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, (LONGPARAM) label_false, sizeof(IntrmdtLabelType *), 0, ATTRIBUTE_FREE_CONTENT_VALUE);
							TreeAttribute_SetFreeFunc(attribute, (TreeAttributeFreeFuncType) IntrmdtLabel_Destroy);
						} break;
					}
				} break;
				case NONTERMINAL_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// expression -> assignment_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// expression , assignment_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_assignment_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// unary_expression assignment_operator assignment_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// assignment_expression -> unary_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_constant_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// constant_expression -> conditional_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_conditional_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// conditional_expression -> logical_OR_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_inclusive_OR_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// inclusive_OR_expression -> exclusive_OR_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// inclusive_OR_expression '|' exclusive_OR_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_exclusive_OR_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// exclusive_OR_expression -> AND_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// exclusive_OR_expression '^' AND_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_AND_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// AND_expression -> equality_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// AND_expression '&' equality_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_equality_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// equality_expression -> relational_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// equality_expression == relational_expression
						case 3:	// equality_expression != relational_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_relational_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// relational_expression -> shift_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// relational_expression < shift_expression
						case 3:	// relational_expression > shift_expression
						case 4:	// relational_expression <= shift_expression
						case 5:	// relational_expression >= shift_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_shift_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// shift_expression -> additive_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// shift_expression << additive_expression
						case 3:	// shift_expression >> additive_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_additive_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// additive_expression -> multiplicative_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// additive_expression '+' multiplicative_expression
						case 3:	// additive_expression '-' multiplicative_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_multiplicative_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// multiplicative_expression -> cast_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// multiplicative_expression -> multiplicative_expression '*' cast_expression
						case 3:	// multiplicative_expression -> multiplicative_expression '/' cast_expression
						case 4:	// multiplicative_expression -> multiplicative_expression '%' cast_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_cast_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// cast_expression -> unary_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_unary_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// unary_expression -> postfix_expression
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 2:	// unary_expression -> ++unary_expression
						case 3:	// unary_expression -> --unary_expression
						case 4: // unary_expression -> unary_operator cast_expression
						{
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_postfix_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// postfix_expression -> primary_expression
						case 2:	// postfix_expression -> postfix_expression  [  expression ]
						case 3:	// postfix_expression -> postfix_expression ( argument_expression_list_opt )
						case 4:	// postfix_expression -> postfix_expression . identifier
						case 5:	// postfix_expression -> postfix_expression STRUCTREF identifier
						case 6:	// postfix_expression -> postfix_expression++
						case 7:	// postfix_expression -> postfix_expression--
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_primary_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:
						case 2:
						case 3:
						{
							Tree_AttachAttribute(node->first_child, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
						case 4:	// ( expression )
						{
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_TRUE, Tree_GetAttributeValue(node, ATTRIB_TRUE), sizeof(IntrmdtLabelType *), 0, 0);
							Tree_AttachAttribute(node->first_child->next_sibling, ATTRIB_FALSE, Tree_GetAttributeValue(node, ATTRIB_FALSE), sizeof(IntrmdtLabelType *), 0, 0);
						} break;
					}
				} break;
			}
		} break;
	}

	while(child)
	{
		IntrmdtCode_PopulateCode(child);

		prev_sibling = child;
		child = child->next_sibling;
	}

	/*if(g_IntrmdtCode_is_statement == COMPILER_NO)
		return 0;*/

	switch(node->type)
	{
		case NODE_TERMINAL: break;
		case NODE_NONTERMINAL:
		{
			switch(node->terminal_nonterminal)
			{
				case NONTERMINAL_translation_unit:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// translation_unit external_declaration
						{
							IntrmdtCodeAccessType *code_access, *code_access_trans, *code_access_ext_decl;

							code_access_trans = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							code_access_ext_decl = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);

							code_access = IntrmdtCodeHolder_Create();
							IntrmdtCodeHolder_AppendCode(code_access, code_access_trans);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_ext_decl);

							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
						case 2:	// translation_unit -> external_declaration
						{
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_external_declaration:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// external_declaration	->	function_definition
						{
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_function_definition:
				{
					IntrmdtCodeAccessType *code_access, *code_access_stmt;
					SymbolTableEntry *func_entry;
					ParseNode *func_name_node;
					TypeCheck_Function *func;

					func_name_node = Tree_QueryFirstNodeDown(node, NONTERMINAL_identifier);
					func_entry = SymbolTable_LookUp(g_SymbolTable_CurrentTable, (char *) func_name_node->first_child->value, SYMBOL_CLASS_IDENTIFIER);
					func = (TypeCheck_Function *) func_entry->param;

					code_access_stmt = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);
					if(code_access_stmt->current_code_holder->code[code_access_stmt->current_code_holder->current_index - 1].op_code != OP_RETURN)
					{
						code_access = IntrmdtCodeHolder_Create();
						IntrmdtCodeHolder_AppendCode(code_access, code_access_stmt);
						IntrmdtCodeHolder_Emit(code_access, OP_RETURN, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
						func->code_access = code_access;
						IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
					}
					else
					{
						func->code_access = code_access_stmt;
						Tree_AttachAttribute(node, ATTRIB_CODE, (LONGPARAM) code_access_stmt, sizeof(IntrmdtCodeAccessType *), 0, 0);
					}
					SymbolTable_SetCurrentTable(g_SymbolTable_CurrentTable->parent);

				} break;
				case NONTERMINAL_compound_statement:
				{
					IntrmdtCodeAccessType *code_access, *code_access_stmt_list_opt;

					code_access = IntrmdtCodeHolder_Create();
					//printf("OP_SYMBOL_ADD 1 : %p, %p\n", code_access, code_access->first_code_holder);
					IntrmdtCodeHolder_Emit(code_access, OP_SYMBOLTABLE_ADD, (LONGPARAM) g_SymbolTable_CurrentTable, (LONGPARAM) 0, (LONGPARAM) 0);
					//printf("OP_SYMBOL_ADD 2 : %p %p, %p, %p, %d\n", code_access->current_code_holder->code, &code_access->current_code_holder->code[code_access->current_code_holder->current_index-1], code_access->first_code_holder, code_access->current_code_holder, code_access->current_code_holder->current_index);
					code_access_stmt_list_opt = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);
					IntrmdtCodeHolder_AppendCode(code_access, code_access_stmt_list_opt);
					IntrmdtCodeHolder_Emit(code_access, OP_SYMBOLTABLE_REMOVE, (LONGPARAM) g_SymbolTable_CurrentTable, (LONGPARAM) 0, (LONGPARAM) 0);
					IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
					//if(node->parent->terminal_nonterminal != NONTERMINAL_function_definition)
					//{
						SymbolTable_SetCurrentTable(g_SymbolTable_CurrentTable->parent);
					//}
				} break;
				case NONTERMINAL_statement_list_opt:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// statement_list_opt -> statement_list
						{
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:
						{
						} break;
					}
				} break;
				case NONTERMINAL_statement_list:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// statement_list -> statement_list statement
						{
							IntrmdtCodeAccessType *code_statement_list, *code_statement, *code_access;
							//NEW START
							IntrmdtLabelType *label_stmt_next;
							//NEW END

							code_access = IntrmdtCodeHolder_Create();
							code_statement_list = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							code_statement = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);
							IntrmdtCodeHolder_AppendCode(code_access, code_statement_list);
							IntrmdtCodeHolder_AppendCode(code_access, code_statement);

							//NEW START
							label_stmt_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_STATEMENT_NEXT);
							if(label_stmt_next && code_access)
								IntrmdtLabel_SetNextInstructionLabelPos(label_stmt_next, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							//NEW END

							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
						case 2:	// statement_list -> statement
						{
							IntrmdtCodeAccessType *code_access;
							//NEW START
							IntrmdtLabelType *label_stmt_next;
							//NEW END

							code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							//NEW START
							label_stmt_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child, ATTRIB_STATEMENT_NEXT);
							if(label_stmt_next && code_access)
								IntrmdtLabel_SetNextInstructionLabelPos(label_stmt_next, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							//NEW END
							Tree_AttachAttribute(node, ATTRIB_CODE, (LONGPARAM) code_access, sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_statement:
				{
					IntrmdtCodeAccessType *code_access;
					IntrmdtLabelType *label_stmt_first;
					//NEW START
					//IntrmdtLabelType *label_stmt_next;
					//NEW END

					code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
					Tree_AttachAttribute(node, ATTRIB_CODE, (LONGPARAM) code_access, sizeof(IntrmdtCodeAccessType *), 0, 0);

					label_stmt_first = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_FIRST);
					if(label_stmt_first)
						IntrmdtLabel_SetLabelPos(label_stmt_first, code_access->first_code_holder, 0);
					//NEW START
					/*label_stmt_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT);
					if(label_stmt_next)
						IntrmdtLabel_SetLabelPos(label_stmt_next, code_access->current_code_holder, code_access->current_code_holder->current_index-1);*/
					//NEW END
				} break;
				case NONTERMINAL_web_statement:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// Response_Write ( argument_expression_list_opt )
						{
							SymbolTableEntry *callee_entry;
							IntrmdtCodeAccessType *code_access, *code_access_arg_expr_list_opt;

							callee_entry = SymbolTable_LookUp(g_SymbolTable_RootTable, SYMBOL_RESPONSE_WRITE, SYMBOL_CLASS_KEYWORD);

							code_access = IntrmdtCodeHolder_Create();

							code_access_arg_expr_list_opt = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_arg_expr_list_opt);
							IntrmdtCodeHolder_Emit(code_access, OP_RESPONSE_WRITE, (LONGPARAM) callee_entry, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) callee_entry, sizeof(SymbolTableEntry *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_iteration_statement:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// while (expression) statement
						{
							IntrmdtCodeAccessType *code_access, *code_access_expr, *code_access_stmt;
							IntrmdtLabelType *label_expr_true, *label_expr_false;
							IntrmdtLabelType *label_stmt_begin, *label_stmt_next, *label_stmt1_next;
							SymbolTableEntry *expr_entry;

							code_access_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);
							code_access_stmt = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);

							label_expr_true = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_TRUE);
							label_expr_false = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_FALSE);

							label_stmt_begin = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_BEGIN);
							label_stmt_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT);
							label_stmt1_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_STATEMENT_NEXT);

							code_access = IntrmdtCodeHolder_Create();
							IntrmdtCodeHolder_AppendCode(code_access, code_access_expr);

							expr_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_PLACE);

							IntrmdtCodeHolder_Emit(code_access, OP_EQ, (LONGPARAM) expr_entry, (LONGPARAM) g_IntrmdtCode_FALSE, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_stmt_next, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_stmt);
							IntrmdtLabel_SetLabelPos(label_expr_true, code_access_stmt->first_code_holder, 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_stmt1_next, code_access->current_code_holder, code_access->current_code_holder->current_index-1);

							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
					}
				} break;
				case NONTERMINAL_jump_statement:
				{
					switch(node->rule_in_nonterminal)
					{
						case 4:
						{
							SymbolTableEntry *expr_opt_entry = NULL;
							IntrmdtCodeAccessType *code_access, *code_access_expr_opt = NULL;

							code_access = IntrmdtCodeHolder_Create();
							if(node->first_child->next_sibling)
							{
								expr_opt_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_PLACE);
								code_access_expr_opt = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);
								IntrmdtCodeHolder_AppendCode(code_access, code_access_expr_opt);
							}

							IntrmdtCodeHolder_Emit(code_access, OP_RETURN, (LONGPARAM) expr_opt_entry, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
					}
				} break;
				case NONTERMINAL_selection_statement:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:		// if ( expression ) statement
						{
							IntrmdtCodeAccessType *code_expr, *code_stmt;
							IntrmdtLabelType *label_stmt_start, *label_stmt_next;
							IntrmdtCodeAccessType *code_access, *code_access_expr, *code_access_stmt;
							SymbolTableEntry *expr_entry;

							label_stmt_start = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child, ATTRIB_TRUE);
							label_stmt_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child, ATTRIB_FALSE);

							code_access = IntrmdtCodeHolder_Create();
							code_access_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							code_access_stmt = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);

							IntrmdtCodeHolder_AppendCode(code_access, code_access_expr);

							expr_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);

							IntrmdtCodeHolder_Emit(code_access, OP_EQ, (LONGPARAM) expr_entry, (LONGPARAM) g_IntrmdtCode_FALSE, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_stmt_next, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_stmt);
							
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
							PRINT_STATEMENT(node);
						} break;
						case 2:		// if ( expression ) statement else statement
						{
							IntrmdtLabelType *label_expr_true, *label_expr_false, *label_stmt_next;
							IntrmdtCodeAccessType *code_access, *code_access_expr, *code_access_stmt1, *code_access_stmt2;
							SymbolTableEntry *expr_entry;

							label_expr_true = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child, ATTRIB_TRUE);
							label_expr_false = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child, ATTRIB_FALSE);

							label_stmt_next = (IntrmdtLabelType *) Tree_GetAttributeValue(node, ATTRIB_STATEMENT_NEXT);

							code_access = IntrmdtCodeHolder_Create();
							code_access_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							code_access_stmt1 = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);
							code_access_stmt2 = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling->next_sibling, ATTRIB_CODE);

							IntrmdtCodeHolder_AppendCode(code_access, code_access_expr);

							expr_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);

							IntrmdtCodeHolder_Emit(code_access, OP_EQ, (LONGPARAM) expr_entry, (LONGPARAM) g_IntrmdtCode_FALSE, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_expr_false, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtLabel_SetNextInstructionLabelPos(label_expr_true, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_stmt1);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_stmt_next, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtLabel_SetNextInstructionLabelPos(label_expr_false, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_stmt2);							

							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
					}
				} break;
				case NONTERMINAL_expression_statement:
				{
					Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
				} break;
				case NONTERMINAL_expression_opt:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// expression_opt -> expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// expression_opt -> nil
						{
						} break;
					}
				} break;
				case NONTERMINAL_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// expression -> assignment_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// expression , assignment_expression
						{
							IntrmdtCodeAccessType *code_expr, *code_assignment_expr, *code_access;
							//IntrmdtCodeHolderType *code_holder;

							code_access = IntrmdtCodeHolder_Create();
							code_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							code_assignment_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);
							IntrmdtCodeHolder_AppendCode(code_access, code_expr);
							IntrmdtCodeHolder_AppendCode(code_access, code_assignment_expr);
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
					}
				} break;
				case NONTERMINAL_argument_expression_list_opt:
				{
					Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
				} break;
				case NONTERMINAL_argument_expression_list:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// argument_expression_list -> assignment_expression
						{
							SymbolTableEntry *param_entry;
							IntrmdtCodeAccessType *code_access;

							param_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);

							code_access = IntrmdtCodeHolder_Create();
							IntrmdtCodeHolder_Emit(code_access, OP_PARAM, (LONGPARAM) param_entry, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
						case 2:	// argument_expression_list , assignment_expression
						{
							SymbolTableEntry *param_entry;
							IntrmdtCodeAccessType *code_access, *code_access_arg_expr_list;

							param_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_PLACE);

							code_access = IntrmdtCodeHolder_Create();

							code_access_arg_expr_list = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_arg_expr_list);
							IntrmdtCodeHolder_Emit(code_access, OP_PARAM, (LONGPARAM) param_entry, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
					}
				} break;
				case NONTERMINAL_assignment_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// unary_expression assignment_operator assignment_expression
						{
							ParseNode *node_assignment_operator;
							IntrmdtCodeAccessType *lvalue_code_access, *rvalue_code_access;
							SymbolTableEntry *lvalue_entry, *rvalue_entry;
							int terminal;

							lvalue_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
							rvalue_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_PLACE);

							lvalue_code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							rvalue_code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);

							node_assignment_operator = node->first_child->next_sibling;
							terminal = node_assignment_operator->first_child->terminal_nonterminal;

							IntrmdtCode_ProcessAssignmentExpression(node, lvalue_entry, rvalue_entry, lvalue_code_access, rvalue_code_access, terminal, 0);
						} break;
						case 2:	// assignment_expression -> unary_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_constant_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// constant_expression -> conditional_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_conditional_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// conditional_expression -> logical_OR_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_logical_OR_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// logical_OR_expression -> logical_AND_expression
						{
							IntrmdtCodeAccessType *code_access;

							code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, (LONGPARAM) code_access, sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// logical_OR_expression || logical_AND_expression
						{
							IntrmdtCodeAccessType *code_access, *code_access_or_expr, *code_access_and_expr;
							IntrmdtLabelType *label_true, *label_false;
							SymbolTableEntry *temp_entry;
							SymbolTableEntry *child1_entry, *child2_entry;
							SymbolTableEntry *entry_0, *entry_1;

							entry_0 = g_IntrmdtCode_FALSE; entry_1 = g_IntrmdtCode_TRUE;

							code_access = IntrmdtCodeHolder_Create();

							code_access_or_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);

							code_access_and_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);

							label_true = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child, ATTRIB_TRUE);

							temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, g_typecheck_char_type);
							child1_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
							child2_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_PLACE);

							IntrmdtCode_ConvertType(code_access, &child1_entry, &child2_entry, NULL);
							IntrmdtCode_ConvertType(code_access, &child1_entry, &entry_0, NULL);							
							IntrmdtCodeHolder_AppendCode(code_access, code_access_or_expr);
							IntrmdtCodeHolder_Emit(code_access, OP_NE, (LONGPARAM) child1_entry, (LONGPARAM) entry_0, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_true, code_access->current_code_holder, code_access->current_code_holder->current_index-1);							
							IntrmdtCodeHolder_AppendCode(code_access, code_access_and_expr);
							IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) temp_entry, (LONGPARAM) g_IntrmdtCode_FALSE, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_EQ, (LONGPARAM) child2_entry, (LONGPARAM) entry_0, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) GOTO_FORWARD, (LONGPARAM) 2, (LONGPARAM) 0);
							IntrmdtLabel_SetNextInstructionLabelPos(label_true, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) temp_entry, (LONGPARAM) g_IntrmdtCode_TRUE, (LONGPARAM) 0);

							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) temp_entry, sizeof(SymbolTableEntry *), 0, 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
					}
				} break;
				case NONTERMINAL_logical_AND_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// logical_AND_expression -> inclusive_OR_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// logical_AND_expression && inclusive_OR_expression
						{
							IntrmdtCodeAccessType *code_access, *code_access_inc_or_expr, *code_access_and_expr;
							IntrmdtLabelType *label_true, *label_false;
							SymbolTableEntry *temp_entry;
							SymbolTableEntry *child1_entry, *child2_entry;
							SymbolTableEntry *entry_0, *entry_1;

							entry_0 = g_IntrmdtCode_FALSE; entry_1 = g_IntrmdtCode_TRUE;

							code_access = IntrmdtCodeHolder_Create();

							code_access_and_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							code_access_inc_or_expr = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);

							label_false = (IntrmdtLabelType *) Tree_GetAttributeValue(node->first_child, ATTRIB_FALSE);

							temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, g_typecheck_char_type);

							child1_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
							child2_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_PLACE);

							IntrmdtCode_ConvertType(code_access, &child1_entry, &child2_entry, NULL);
							IntrmdtCode_ConvertType(code_access, &child1_entry, &entry_0, NULL);
							IntrmdtCode_ConvertType(code_access, &child1_entry, &entry_1, NULL);
							
							IntrmdtCodeHolder_AppendCode(code_access, code_access_and_expr);
							IntrmdtCodeHolder_Emit(code_access, OP_NE, (LONGPARAM) child1_entry, (LONGPARAM) entry_0, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) GOTO_FORWARD, (LONGPARAM) 2, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_false, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_inc_or_expr);							
							IntrmdtCodeHolder_Emit(code_access, OP_EQ, (LONGPARAM) child2_entry, (LONGPARAM) entry_0, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtLabel_AddToGotoList(label_false, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) temp_entry, (LONGPARAM) g_IntrmdtCode_TRUE, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_GOTO, (LONGPARAM) GOTO_FORWARD, (LONGPARAM) 2, (LONGPARAM) 0);
							IntrmdtLabel_SetNextInstructionLabelPos(label_false, code_access->current_code_holder, code_access->current_code_holder->current_index-1);
							IntrmdtCodeHolder_Emit(code_access, OP_ASSIGN, (LONGPARAM) temp_entry, (LONGPARAM) g_IntrmdtCode_FALSE, (LONGPARAM) 0);

							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) temp_entry, sizeof(SymbolTableEntry *), 0, 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
						} break;
					}
				} break;
				case NONTERMINAL_inclusive_OR_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// inclusive_OR_expression -> exclusive_OR_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// inclusive_OR_expression '|' exclusive_OR_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_BITOR);
						} break;
					}
				} break;
				case NONTERMINAL_exclusive_OR_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// exclusive_OR_expression -> AND_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// exclusive_OR_expression '^' AND_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_BITXOR);
						} break;
					}
				} break;
				case NONTERMINAL_AND_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// AND_expression -> equality_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// AND_expression '&' equality_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_BITAND);
						} break;
					}
				} break;
				case NONTERMINAL_equality_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// equality_expression -> relational_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// equality_expression == relational_expression
						{
							IntrmdtCode_ProcessBinaryBooleanOperation(node, OP_EQ);
						} break;
						case 3:	// equality_expression != relational_expression
						{
							IntrmdtCode_ProcessBinaryBooleanOperation(node, OP_NE);
						} break;
					}
				} break;
				case NONTERMINAL_relational_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// relational_expression -> shift_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// relational_expression < shift_expression
						{
							IntrmdtCode_ProcessBinaryBooleanOperation(node, OP_LT);
						} break;
						case 3:	// relational_expression > shift_expression
						{
							IntrmdtCode_ProcessBinaryBooleanOperation(node, OP_GT);
						} break;
						case 4:	// relational_expression <= shift_expression
						{
							IntrmdtCode_ProcessBinaryBooleanOperation(node, OP_LE);
						} break;
						case 5:	// relational_expression >= shift_expression
						{
							IntrmdtCode_ProcessBinaryBooleanOperation(node, OP_GE);
						} break;
					}
				} break;
				case NONTERMINAL_shift_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// shift_expression -> additive_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// shift_expression << additive_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_SHL);
						} break;
						case 3:	// shift_expression >> additive_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_SHR);
						} break;
					}
				} break;
				case NONTERMINAL_additive_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// additive_expression -> multiplicative_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// additive_expression '+' multiplicative_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_ADD);
						} break;
						case 3:	// additive_expression '-' multiplicative_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_SUB);
						} break;
					}
				} break;
				case NONTERMINAL_multiplicative_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// multiplicative_expression -> cast_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// multiplicative_expression -> multiplicative_expression '*' cast_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_MUL);
						} break;
						case 3:	// multiplicative_expression -> multiplicative_expression '/' cast_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_DIV);
						} break;
						case 4:	// multiplicative_expression -> multiplicative_expression '%' cast_expression
						{
							IntrmdtCode_ProcessBinaryArithmeticOperation(node, OP_MOD);
						} break;
					}
				} break;
				case NONTERMINAL_cast_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// cast_expression -> unary_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_unary_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// unary_expression -> postfix_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// unary_expression -> ++unary_expression
						case 3:	// unary_expression -> --unary_expression
						{
							IntrmdtCodeAccessType *lvalue_code_access;
							SymbolTableEntry *lvalue_entry, *rvalue_entry;
							int terminal = -1;

							terminal = (node->rule_in_nonterminal == 2) ? ASSIGNMENT_PLUS : ASSIGNMENT_MINUS;

							lvalue_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_PLACE);
							rvalue_entry = terminal == ASSIGNMENT_PLUS ? g_IntrmdtCode_CHAR_1 : g_IntrmdtCode_CHAR_NEG_1;

							lvalue_code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_CODE);

							IntrmdtCode_ProcessAssignmentExpression(node, lvalue_entry, rvalue_entry, lvalue_code_access, NULL, terminal, 0);
						} break;
						case 4: // unary_expression -> unary_operator cast_expression
						{
							IntrmdtCode_ProcessUnaryOperation(node);
						} break;
					}
				} break;
				case NONTERMINAL_postfix_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// postfix_expression -> primary_expression
						{
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, Tree_GetAttributeValue(node->first_child, ATTRIB_CODE), sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
						case 2:	// postfix_expression -> postfix_expression  [  expression ]
						{
							IntrmdtCodeAccessType *code_access, *expression_code_access, *postfix_code_access;
							SymbolTableEntry *expr_entry, *postfix_entry, *temp_entry;
							Type *type, newType;

							expression_code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);
							postfix_code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);

							postfix_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
							expr_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_PLACE);

							code_access = IntrmdtCodeHolder_Create();
							IntrmdtCodeHolder_AppendCode(code_access, expression_code_access);
							IntrmdtCodeHolder_AppendCode(code_access, postfix_code_access);

							type = postfix_entry->type->type;
							newType.op = TYPE_POINTER;
							newType.type = NULL;
							type = TypeCheck_CreateType(&newType, type);

							temp_entry = IntrmdtCode_GetNewTempVariable(g_SymbolTable_CurrentTable, type);
							IntrmdtCodeHolder_Emit(code_access, OP_ARRAYACCESS, (LONGPARAM) postfix_entry, (LONGPARAM) expr_entry, (LONGPARAM) temp_entry);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) temp_entry, sizeof(SymbolTableEntry *), 0, 0);

						} break;
						case 3:	// postfix_expression -> postfix_expression ( argument_expression_list_opt )
						{
							SymbolTableEntry *callee_entry;
							IntrmdtCodeAccessType *code_access, *code_access_arg_expr_list_opt;

							callee_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);

							code_access = IntrmdtCodeHolder_Create();

							code_access_arg_expr_list_opt = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child->next_sibling->next_sibling, ATTRIB_CODE);
							IntrmdtCodeHolder_AppendCode(code_access, code_access_arg_expr_list_opt);
							IntrmdtCodeHolder_Emit(code_access, OP_CALL, (LONGPARAM) callee_entry, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) callee_entry, sizeof(SymbolTableEntry *), 0, 0);
							//PRINT_STATEMENT(node);
						} break;
						case 4:	// postfix_expression -> postfix_expression . identifier
						{
						} break;
						case 5:	// postfix_expression -> postfix_expression STRUCTREF identifier
						{
						} break;
						case 6:	// postfix_expression -> postfix_expression++
						case 7:	// postfix_expression -> postfix_expression--
						{
							IntrmdtCodeAccessType *lvalue_code_access;
							SymbolTableEntry *lvalue_entry, *rvalue_entry;
							int terminal = -1;

							terminal = (node->rule_in_nonterminal == 6) ? ASSIGNMENT_PLUS : ASSIGNMENT_MINUS;

							lvalue_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
							rvalue_entry = terminal == ASSIGNMENT_PLUS ? g_IntrmdtCode_CHAR_1 : g_IntrmdtCode_CHAR_NEG_1;

							lvalue_code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);

							IntrmdtCode_ProcessAssignmentExpression(node, lvalue_entry, rvalue_entry, lvalue_code_access, NULL, terminal, 1);
						} break;
						case 8:	// Request_QueryString ( string )
						{
							SymbolTableEntry *string_entry, *callee_entry;
							IntrmdtCodeAccessType *code_access;

							callee_entry = SymbolTable_LookUp(g_SymbolTable_RootTable, SYMBOL_REQUEST_QUERYSTRING, SYMBOL_CLASS_KEYWORD);
							string_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child->next_sibling, ATTRIB_PLACE);

							code_access = IntrmdtCodeHolder_Create();

							IntrmdtCodeHolder_Emit(code_access, OP_PARAM, (LONGPARAM) string_entry, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtCodeHolder_Emit(code_access, OP_REQUEST_QUERYSTRING, (LONGPARAM) callee_entry, (LONGPARAM) 0, (LONGPARAM) 0);
							IntrmdtCode_AttachCodeAccessAttribute(node, code_access);
							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) callee_entry, sizeof(SymbolTableEntry *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_primary_expression:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:	// identifier
						{
							SymbolTableEntry *entry;

							entry = SymbolTable_LookUp(g_SymbolTable_CurrentTable, (char *) node->first_child->first_child->value, SYMBOL_CLASS_IDENTIFIER);
							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) entry, sizeof(SymbolTableEntry *), COMPILER_NO, COMPILER_NO);
						} break;
						case 2:	// constant
						{
							int symbol_class;
							union const_value_type const_value;
							SymbolTableEntry *entry = NULL;

							const_value.l = 0L;

							switch(node->first_child->first_child->terminal_nonterminal)
							{
								case CONSTANT_INTEGER: const_value.i = (int) node->first_child->first_child->value; symbol_class = SYMBOL_CLASS_CONST_INTEGER; break;
								case CONSTANT_FLOATING: const_value.f = (float) node->first_child->first_child->value; symbol_class = SYMBOL_CLASS_CONST_FLOAT; break;
								case CONSTANT_CHAR: const_value.c = (char) node->first_child->first_child->value; symbol_class = SYMBOL_CLASS_CONST_CHAR; break;
							}

							if((entry=SymbolTable_LookUpConst(const_value, symbol_class))==NULL)
								entry = SymbolTable_AddConstEntry(const_value, symbol_class);

							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) entry, sizeof(SymbolTableEntry *), COMPILER_NO, COMPILER_NO);
						} break;
						case 3:	// string				
						{
							/*union const_value_type const_value;
							int symbol_class;
							SymbolTableEntry *entry = NULL;

							symbol_class = SYMBOL_CLASS_CONST_STRING;
							const_value.s = (char *) node->first_child->first_child->value;

							if((entry=SymbolTable_LookUpConst(const_value, symbol_class))==NULL)
								entry = SymbolTable_AddConstEntry(const_value, symbol_class);

							Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) entry, sizeof(SymbolTableEntry *), COMPILER_NO, COMPILER_NO);*/

							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
						} break;
						case 4:	// ( expression )
						{
							IntrmdtCodeAccessType *code_access;
							SymbolTableEntry *place_entry;

							place_entry = (SymbolTableEntry *) Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE);
							code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node->first_child, ATTRIB_CODE);
							Tree_AttachAttribute(node, ATTRIB_PLACE, Tree_GetAttributeValue(node->first_child, ATTRIB_PLACE), sizeof(SymbolTableEntry *), 0, 0);
							Tree_AttachAttribute(node, ATTRIB_CODE, (LONGPARAM) code_access, sizeof(IntrmdtCodeAccessType *), 0, 0);
						} break;
					}
				} break;
				case NONTERMINAL_string:
				{
					union const_value_type const_value;
					int symbol_class;
					SymbolTableEntry *entry = NULL;

					symbol_class = SYMBOL_CLASS_CONST_STRING;
					const_value.s = (char *) node->first_child->value;

					if((entry=SymbolTable_LookUpConst(const_value, symbol_class))==NULL)
						entry = SymbolTable_AddConstEntry(const_value, symbol_class);

					Tree_AttachAttribute(node, ATTRIB_PLACE, (LONGPARAM) entry, sizeof(SymbolTableEntry *), COMPILER_NO, COMPILER_NO);
				} break;
			}
		} break;
	}
}

IntrmdtLabelListType *g_IntrmdtCode_GlobalLabelList = NULL;

int IntrmdtCode_GenerateLineNumber()
{
/*
Pre : None
Post : Generates line number for all code
*/

	IntrmdtCodeAccessType *code_access;
	IntrmdtCodeHolderType *code_holder;
	ParseNode *node_statement_list_opt;
	int i, line_num = 1;

		code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(g_Tree_RootNode, ATTRIB_CODE);

		IntrmdtCodeHolder_Emit(code_access, OP_END, (LONGPARAM) 0, (LONGPARAM) 0, (LONGPARAM) 0);
		code_holder = code_access->first_code_holder;
		while(code_holder)
		{
			for(i=0;i<code_holder->current_index;i++)
			{
				code_holder->code[i].line_num = line_num++;
				//printf("%p\t%03d\t%d\t%p\t%p\t%p\n", &code_holder->code[i], code_holder->code[i].line_num, code_holder->code[i].op_code, (int)code_holder->code[i].operand1, (int)code_holder->code[i].operand2, code_holder->code[i].result);
			}
			code_holder = code_holder->next;
		}

	return 0;
}

int IntrmdtCode_Backpatch()
{
/*
Pre : None
Post : Backpatches the code
*/

	IntrmdtLabelListType *label_list;
	IntrmdtLabelLinkType *label_link;
	ThreeAddressCode *label_code, *jump_code;
	ParseNode *node_statement_list_opt;
	IntrmdtCodeAccessType *code_access;


	code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(g_Tree_RootNode, ATTRIB_CODE);

	label_list = g_IntrmdtCode_GlobalLabelList;
	while(label_list)
	{
		if(label_list->label->label_pos_code_holder!=NULL)
		{
			label_link = label_list->label->label_link;
			label_code = &label_list->label->label_pos_code_holder->code[label_list->label->label_pos_code_index];
			while(label_link)
			{
				jump_code = &label_link->code_holder->code[label_link->code_index];
				label_link = label_link->next;
				jump_code->operand1 = (LONGPARAM) GOTO_ABSOLUTE;
				jump_code->operand2 = (LONGPARAM) label_code->line_num;
				if(label_list->label->next_instruction)
					jump_code->operand2++;
			}
		}

		label_list = label_list->next;
	}

	return 0;
}

int IntrmdtLabel_UpdateGlobalLabelList(IntrmdtLabelType *label)
{
/*
Pre : label object is supplied
Post : Updates global label list
*/

	IntrmdtLabelListType *label_list;

	if(label==NULL)
		return 0;

	label_list = calloc(1, sizeof(IntrmdtLabelListType));
	label_list->label = label;
	if(g_IntrmdtCode_GlobalLabelList==NULL)
	{
		g_IntrmdtCode_GlobalLabelList = label_list;
	}
	else
	{
		label_list->next = g_IntrmdtCode_GlobalLabelList->next;
		g_IntrmdtCode_GlobalLabelList->next = label_list;
	}

	return 0;
}

IntrmdtLabelType *IntrmdtLabel_Create()
{
/*
Pre : None
Post : Creates label object and returns it to the caller
*/

	IntrmdtLabelType *label;

	label = (IntrmdtLabelType *) calloc(1, sizeof(IntrmdtLabelType));
	IntrmdtLabel_UpdateGlobalLabelList(label);

	return label;
}

int IntrmdtLabel_Destroy(IntrmdtLabelType *label)
{
/*
Pre : label to be destroyed is supplied
Post : Destroys label object
*/

	if(label)
		free(label);

	return 0;
}

int IntrmdtLabel_SetNextInstructionLabelPos(IntrmdtLabelType *label, IntrmdtCodeHolderType *code_holder, int code_index)
{
/*
Pre : Supplies label object and code
Post : Points the next instruction to be the label of the code
*/

	if(label==NULL)
		return 0;

	label->label_pos_code_holder = code_holder;
	label->label_pos_code_index = code_index;
	label->next_instruction = 1;

	return 0;
}

int IntrmdtLabel_SetLabelPos(IntrmdtLabelType *label, IntrmdtCodeHolderType *code_holder, int code_index)
{
/*
Pre : Supplies label object and code
Post : Points the label to that code
*/

	if(label==NULL)
		return 0;

	label->label_pos_code_holder = code_holder;
	label->label_pos_code_index = code_index;
	label->next_instruction = 0;

	return 0;
}

int IntrmdtLabel_AddToGotoList(IntrmdtLabelType *label,  IntrmdtCodeHolderType *code_holder, int code_index)
{
/*
Pre : Supplies label object and code
Post : This code object contains a goto which points to this label.
*/

	IntrmdtLabelLinkType *label_link;

	if(label==NULL)
		return 0;

	label_link = (IntrmdtLabelLinkType *) calloc(1, sizeof(IntrmdtLabelLinkType));
	label_link->code_holder = code_holder;
	label_link->code_index = code_index;

	label_link->next = label->label_link;
	label->label_link = label_link;

	return 0;
}

int IntrmdtCode_Print(ParseNode *node)
{
/*
Pre : Code associated with this node to be printed
Post : Codes printed
*/

	IntrmdtCodeAccessType *code_access;
	IntrmdtCodeHolderType *code_holder;
	int i;

	code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node, ATTRIB_CODE);
	code_holder = code_access->first_code_holder;
	while(code_holder)
	{
		for(i=0;i<code_holder->current_index;i++)
			//printf("%p\t%03d\t%d\t%p\t%p\t%p\n", &code_holder->code[i], code_holder->code[i].line_num, code_holder->code[i].op_code, (int)code_holder->code[i].operand1, (int)code_holder->code[i].operand2, code_holder->code[i].result);
			printf("%03d\t%d\t%p\t%p\t%p\n", code_holder->code[i].line_num, code_holder->code[i].op_code, (int)code_holder->code[i].operand1, (int)code_holder->code[i].operand2, code_holder->code[i].result);

		code_holder = code_holder->next;
	}
}

//OP code in string form
static char *g_IntrmdtCode_OPCode_str[] =
{
"",
"INC                ","DEC                ","ADD                ","SUB                ",
"MUL                ","DIV                ","MOD                ","SHL                ",
"SHR                ",
"ASSIGN             ","GOTO               ","LT                 ","GT                 ",
"LE                 ","GE                 ","EQ                 ","NE                 ",
"BITOR              ","BITXOR             ","BITAND             ","CONTINUE           ",
"INDIRECTION        ","ADDRESSOF          ","ARRAYACCESS        ",
"BREAK              ","PARAM              ","CALL               ","RETURN             ",
"REQUEST_QUERYSTRING","RESPONSE_WRITE     ","SYMBOLTABLE_ADD    ","SYMBOLTABLE_REMOVE ",
"END                ","INTTOFLOAT         ","CHARTOINT          ","CHARTOFLOAT        ",
"INTTOCHAR          ","FLOATTOCHAR        ","FLOATTOINT         ","UNARYMINUS         ",
"ONESCOMPLEMENT     ","LOGICALNEGATION    "
};

void IntrmdtCode_PrintSymTabEntry(SymbolTableEntry *entry)
{
/*
Pre : Symbol table entry supplied
Post : Prints symbol or constant associated with this entry
*/

	if(entry==NULL) return;

	switch(entry->symbol_class)
	{
		case SYMBOL_CLASS_TYPE: printf("%s", entry->symbol); break;
		case SYMBOL_CLASS_KEYWORD: printf("%s", entry->symbol); break;
		case SYMBOL_CLASS_IDENTIFIER: printf("%s", entry->symbol); break;
		case SYMBOL_CLASS_CONST_INTEGER: printf("%d", entry->const_value.i); break;
		case SYMBOL_CLASS_CONST_FLOAT: printf("%f", entry->const_value.f); break;
		case SYMBOL_CLASS_CONST_CHAR: printf("%d", entry->const_value.c); break;
		case SYMBOL_CLASS_CONST_STRING: printf("%s", entry->const_value.s); break;
	}
}

int IntrmdtCode_PrintVerbose(ParseNode *node)
{
/*
Pre : Code associated with this node to be printed
Post : Verbose code printed
*/

	SymbolTableEntry *operand1, *operand2, *result;
	IntrmdtCodeAccessType *code_access;
	IntrmdtCodeHolderType *code_holder;
	int i;

	code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(node, ATTRIB_CODE);
	code_holder = code_access->first_code_holder;
	while(code_holder)
	{
		for(i=0;i<code_holder->current_index;i++)
		{
			operand1 = (SymbolTableEntry *) code_holder->code[i].operand1;
			operand2 = (SymbolTableEntry *) code_holder->code[i].operand2;
			result = (SymbolTableEntry *) code_holder->code[i].result;

			printf("%03d\t%s\t", code_holder->code[i].line_num, g_IntrmdtCode_OPCode_str[code_holder->code[i].op_code]);
			switch(code_holder->code[i].op_code)
			{
				case OP_ASSIGN:
				{
					printf("%s\t", operand1->symbol);
					IntrmdtCode_PrintSymTabEntry(operand2);
				} break;
				case OP_ADD:
				case OP_SUB:
				case OP_MUL:
				case OP_DIV:
				case OP_MOD:
				case OP_BITOR:
				case OP_BITXOR:
				case OP_BITAND:
				case OP_SHL:
				case OP_SHR:
				{
					IntrmdtCode_PrintSymTabEntry(operand1);
					printf("\t");
					IntrmdtCode_PrintSymTabEntry(operand2);
					printf("\t");
					printf("%s", result->symbol);
				} break;
				case OP_LT:
				case OP_GT:
				case OP_LE:
				case OP_GE:
				case OP_EQ:
				case OP_NE:
				{
					IntrmdtCode_PrintSymTabEntry(operand1);
					printf("\t");
					IntrmdtCode_PrintSymTabEntry(operand2);
				} break;
				case OP_CHARTOINT:
				case OP_CHARTOFLOAT:
				case OP_INTTOFLOAT:
				case OP_INTTOCHAR:
				case OP_FLOATTOCHAR:
				case OP_FLOATTOINT:
				{
					IntrmdtCode_PrintSymTabEntry(operand1);
					printf("\t\t");
					printf("%s", result->symbol);
				} break;
				case OP_RETURN:
				case OP_PARAM:
				{
					IntrmdtCode_PrintSymTabEntry(operand1);
				} break;
				case OP_SYMBOLTABLE_ADD:
				case OP_SYMBOLTABLE_REMOVE:
				{
					printf("%p", operand1);
				} break;
				case OP_GOTO:
				{
					int goto_flag, line;

					goto_flag = (int) code_holder->code[i].operand1;
					line = (int) code_holder->code[i].operand2;
					switch(goto_flag)
					{
						case GOTO_BACKWARD: printf("BACKWARD"); break;
						case GOTO_FORWARD: printf("FORWARD"); break;
						case GOTO_ABSOLUTE: printf("ABSOLUTE"); break;
					}

					printf("\t%d", line);

				} break;
			}
			printf("\n");
			//printf("%03d\t%d\t%p\t%p\t%p\n", code_holder->code[i].line_num, code_holder->code[i].op_code, (int)code_holder->code[i].operand1, (int)code_holder->code[i].operand2, code_holder->code[i].result);
		}

		code_holder = code_holder->next;
	}
}

