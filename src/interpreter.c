/*
File Name : interpreter.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Interpreter of the intermediate code. It fetches a given
function's instructions from the code holder and then executes. Currently supports
the following op code -
OP_ASSIGN, OP_ADD, OP_SUB, OP_MOD, OP_MUL, OP_DIV, OP_BITOR, OP_BITXOR, OP_BITAND,
OP_SHL, OP_SHR, OP_LT, OP_GT, OP_LE, OP_GE, OP_EQ, OP_NE, OP_GOTO, OP_RETURN, OP_END,
OP_REQUEST_QUERYSTRING, OP_RESPONSE_WRITE, OP_PARAM, OP_SYMBOLTABLE_ADD, OP_SYMBOLTABLE_REMOVE
*/

#include "interpreter.h"
#include "tree.h"
#include "intrmdtcode.h"
#include "HTTP.h"

static HTTPRequest *g_Interpreter_HTTPRequest = NULL; 	// Pointer to HTTP request object
static HTTPResponse *g_Interpreter_HTTPResponse = NULL;	// Pointer to HTTP response object

#define Interpreter_ProcessBinaryMathOp(op_code, data_type) {\
	data_type rvalue1, rvalue2; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &rvalue1, sizeof(data_type)); \
	Interpreter_GetSymbolTableEntryValue(operand2, (void *) &rvalue2, sizeof(data_type)); \
\
	switch(op_code) \
	{ \
		case OP_ADD: *((data_type *) (result->storage)) = rvalue1 + rvalue2; break; \
		case OP_SUB: *((data_type *) (result->storage)) = rvalue1 - rvalue2; break; \
		case OP_MOD: *((data_type *) (result->storage)) = rvalue1 % rvalue2; break; \
		case OP_MUL: *((data_type *) (result->storage)) = rvalue1 * rvalue2; break; \
		case OP_DIV: *((data_type *) (result->storage)) = rvalue1 / rvalue2; break; \
		case OP_BITAND: *((data_type *) (result->storage)) = rvalue1 & rvalue2; break; \
		case OP_BITOR: *((data_type *) (result->storage)) = rvalue1 | rvalue2; break; \
		case OP_BITXOR: *((data_type *) (result->storage)) = rvalue1 ^ rvalue2; break; \
		case OP_SHL: *((data_type *) (result->storage)) = rvalue1 << rvalue2; break; \
		case OP_SHR: *((data_type *) (result->storage)) = rvalue1 >> rvalue2; break; \
	} \
} \

#define Interpreter_ProcessBinaryMathOpFloat(op_code) {\
	float rvalue1, rvalue2; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &rvalue1, sizeof(float)); \
	Interpreter_GetSymbolTableEntryValue(operand2, (void *) &rvalue2, sizeof(float)); \
\
	switch(op_code) \
	{ \
		case OP_ADD: *((float *) (result->storage)) = rvalue1 + rvalue2; break; \
		case OP_SUB: *((float *) (result->storage)) = rvalue1 - rvalue2; break; \
		case OP_MUL: *((float *) (result->storage)) = rvalue1 * rvalue2; break; \
		case OP_DIV: *((float *) (result->storage)) = rvalue1 / rvalue2; break; \
	} \
} \

#define Interpreter_ProcessBinaryMathOpPointer(op_code) {\
	void *rvalue1, *rvalue2; \
	int size; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &rvalue1, sizeof(void *)); \
	Interpreter_GetSymbolTableEntryValue(operand2, (void *) &rvalue2, sizeof(void *)); \
\
	if(operand2->type && operand2->type->op == TYPE_POINTER) \
		size = 1; \
	else \
		size = operand1->type->type->size; \
\
	switch(op_code) \
	{ \
		case OP_ADD: *((void **) (result->storage)) = (void *) (((int) rvalue1) + (((int) rvalue2) * size)); break; \
		case OP_SUB: *((void **) (result->storage)) = (void *) (((int) rvalue1) - (((int) rvalue2) * size)); break; \
		/*case OP_MUL: *((void **) (result->storage)) = rvalue1 * (rvalue2 * size); break; \
		case OP_DIV: *((void **) (result->storage)) = rvalue1 / (rvalue2 * size); break; \
		case OP_BITAND: *((void **) (result->storage)) = rvalue1 & rvalue2; break; \
		case OP_BITOR: *((void **) (result->storage)) = rvalue1 | rvalue2; break; \
		case OP_BITXOR: *((void **) (result->storage)) = rvalue1 ^ rvalue2; break; \
		case OP_SHL: *((void **) (result->storage)) = rvalue1 << rvalue2; break; \
		case OP_SHR: *((void **) (result->storage)) = rvalue1 >> rvalue2; break; \*/ \
	} \
} \

#define Interpreter_ProcessBinaryLogicalOp(op_code, data_type)  { \
	data_type rvalue1; \
	data_type rvalue2; \
	char temp_result; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &rvalue1, sizeof(data_type)); \
	Interpreter_GetSymbolTableEntryValue(operand2, (void *) &rvalue2, sizeof(data_type)); \
\
	switch(op_code) \
	{ \
		case OP_LT: temp_result = rvalue1 < rvalue2; break; \
		case OP_GT: temp_result = rvalue1 > rvalue2; break; \
		case OP_LE: temp_result = rvalue1 <= rvalue2; break; \
		case OP_GE: temp_result = rvalue1 >= rvalue2; break; \
		case OP_EQ: temp_result = rvalue1 == rvalue2; break; \
		case OP_NE: temp_result = rvalue1 != rvalue2; break; \
	} \
\
	if(!temp_result) (*line_num)++; \
} \

#define Interpreter_ConvertType(type_from, type_to) { \
	type_from from; \
	type_to to; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &from, sizeof(type_from)); \
	to = (type_to) from; \
	memcpy(result->storage, (void *) &to, sizeof(type_to)); \
} \

#define Interpreter_ProcessUnaryOperator(data_type) { \
	data_type rvalue; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &rvalue, sizeof(data_type)); \
	switch(code->op_code) \
	{ \
		case OP_UNARYMINUS: *((data_type *) (result->storage)) = -rvalue; break; \
		case OP_ONESCOMPLEMENT: *((data_type *) (result->storage)) = ~rvalue; break; \
		case OP_LOGICALNEGATION: *((data_type *) (result->storage)) = !rvalue; break; \
	} \
} \


#define Interpreter_ProcessUnaryOperatorFloat() { \
	float rvalue; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &rvalue, sizeof(float)); \
	switch(code->op_code) \
	{ \
		case OP_UNARYMINUS: *((float *) (result->storage)) = -rvalue; break; \
		case OP_LOGICALNEGATION: *((float *) (result->storage)) = !rvalue; break; \
	} \
} \


#define Interpreter_ProcessUnaryOperatorPointer() { \
	void *rvalue; \
\
	Interpreter_GetSymbolTableEntryValue(operand1, (void *) &rvalue, sizeof(void *)); \
	switch(code->op_code) \
	{ \
		case OP_LOGICALNEGATION: *((void **) (result->storage)) = !rvalue; break; \
	} \
} \


int Interpreter_Start(char *func_name)
{
/*
Pre : Function from interpreting should start is supplied
Post : Function is interpreted and contents of the storage of the function may be changed.
*/

	IntrmdtCodeAccessType *code_access;
	IntrmdtCodeHolderType *code_holder;
	ThreeAddressCode *code;
	RuntimeStorage *storage;
	SymbolTableEntry *func_entry;
	SymbolTable *func_symtab;
	TypeCheck_Function *func;
	int line_num = 1;
	int ret;

	func_entry = SymbolTable_LookUp(g_SymbolTable_RootTable, func_name, SYMBOL_CLASS_IDENTIFIER);
	func = (TypeCheck_Function *) func_entry->param;
	func_symtab = func->func_symtab;

	storage = RuntimeStorage_Create();
	RuntimeStorage_AddSymbolTable(storage, func_symtab);

	//code_access = (IntrmdtCodeAccessType *) Tree_GetAttributeValue(g_Tree_RootNode, ATTRIB_CODE);
	code_access = func->code_access;
	line_num = func->code_access->first_code_holder->code[0].line_num;

	//printf("Function name : %s, %d\n", func_name, code_access->first_code_holder->code[0].line_num);

	if(code_access == NULL)
		return -1;

	code_holder = code_access->first_code_holder;
	do
	{
		code = Interpreter_Fetch(code_access, &code_holder, line_num);
		ret = Interpreter_Execute(storage, code, &line_num);
	}
	while(ret==0);

	RuntimeStorage_RemoveSymbolTable(storage, func_symtab);

	RuntimeStorage_Destroy(storage);

	return 0;
}

ThreeAddressCode *Interpreter_Fetch(IntrmdtCodeAccessType *code_access, IntrmdtCodeHolderType **code_holder, int line_num)
{
/*
Pre : Fetches the code of the given line number
Post : Returns three-address code for the given line number
*/

	int i;

	if((*code_holder)->current_index > 0 && (*code_holder)->code[0].line_num > line_num)
	{
		*code_holder = code_access->first_code_holder;
	}
	while(*code_holder)
	{
		for(i=0;i<(*code_holder)->current_index;i++)
			if((*code_holder)->code[i].line_num == line_num)
				return &(*code_holder)->code[i];

		*code_holder = (*code_holder)->next;
	}
	return NULL;
}

struct SymbolTableEntryList
{
	SymbolTableEntry *entry;
	struct SymbolTableEntryList *next;
};

int Interpreter_Execute(RuntimeStorage *storage, ThreeAddressCode *code, int *line_num)
{
/*
Pre : Executes the given code.
Post : Contents of the storage may be changed or output is generated by the effect of
executing the code
*/

	SymbolTableEntry *operand1, *operand2, *result;
	//LONGPARAM *lvalue, rvalue1, rvalue2, temp_result;
	static struct SymbolTableEntryList *param_list = NULL;

	operand1 = (SymbolTableEntry *) code->operand1;
	operand2 = (SymbolTableEntry *) code->operand2;
	result = (SymbolTableEntry *) code->result;

	//printf("Execute : %d\n", *line_num);

	switch(code->op_code)
	{
		case OP_CALL:
		{
			Interpreter_FreeParam(&param_list);
		} break;
		case OP_REQUEST_QUERYSTRING:
		{
			struct SymbolTableEntryList *param_entry;
			char field_name[100], *p_field_name;
			HTTPRequest_Field *query_field;
			union const_value_type const_value;
			//SymbolTableEntry *const_entry,
			SymbolTableEntry *req_querystring_entry;

			p_field_name = field_name;

			param_entry = param_list;
			switch(param_entry->entry->symbol_class)
			{
				case SYMBOL_CLASS_IDENTIFIER:
				{
					/*switch(param_entry->entry->data_type)
					{
						case TYPE_INT: break;
						case TYPE_FLOAT: break;
						case TYPE_CHAR: break;
					}*/
				} break;
				case SYMBOL_CLASS_CONST_STRING:
				{
					strcpy(field_name, param_entry->entry->const_value.s);
					if(strlen(p_field_name) > 1)
					{
						p_field_name++;
						p_field_name[strlen(p_field_name)-1] = '\0';
						strcpy(field_name, p_field_name);
					}
				} break;
			}

			const_value.i = 0;
			req_querystring_entry = operand1;
			req_querystring_entry->const_value = const_value;

			query_field = g_Interpreter_HTTPRequest->query_field;
			while(query_field)
			{
				if(strcmp(query_field->name, field_name)==0)
					break;
				query_field = query_field->next;
			}

			if(query_field==NULL || (query_field && query_field->value==NULL))
			{
				Interpreter_FreeParam(&param_list);
				break;
			}

			const_value.i = atoi(query_field->value);

			//if((const_entry = SymbolTable_LookUpConst(const_value, SYMBOL_CLASS_CONST_INTEGER))==NULL)
			//	const_entry = SymbolTable_AddConstEntry(const_value, SYMBOL_CLASS_CONST_INTEGER);
			
			req_querystring_entry->const_value = const_value;

			/*{
				char buffer[100];

				HTTPResponse_HTMLText(g_Interpreter_HTTPResponse, "Field name : ");
				HTTPResponse_HTMLText(g_Interpreter_HTTPResponse, field_name);
				HTTPResponse_HTMLText(g_Interpreter_HTTPResponse, " Field value : ");
				
				HTTPResponse_HTMLText(g_Interpreter_HTTPResponse, query_field->value);
			}*/
			//printf("Field name : %s\n", field_name);

			Interpreter_FreeParam(&param_list);
		} break;
		case OP_RESPONSE_WRITE:
		{
			struct SymbolTableEntryList *param_entry;
			char buffer[500], *p_buffer, temp_buf[100], *p_temp_buf;

			p_buffer = buffer;

			param_entry = param_list;
			while(param_entry)
			{
				p_temp_buf = temp_buf;
				memset(temp_buf, '\0', sizeof(temp_buf));
				switch(param_entry->entry->symbol_class)
				{
					case SYMBOL_CLASS_IDENTIFIER:
					{
						switch(param_entry->entry->data_type)
						{
							case TYPE_INT: itoa(*((int *)param_entry->entry->storage), temp_buf, 10); break;
							case TYPE_FLOAT: sprintf(temp_buf, "%0.2f", *((float *)param_entry->entry->storage)); break;
							case TYPE_CHAR: temp_buf[0] = *((char *) param_entry->entry->storage); break;
						}
					} break;
					case SYMBOL_CLASS_CONST_INTEGER: itoa(param_entry->entry->const_value.i, temp_buf, 10); break;
					case SYMBOL_CLASS_CONST_FLOAT: sprintf(temp_buf, "%0.2f", param_entry->entry->const_value.f); break;
					case SYMBOL_CLASS_CONST_CHAR: temp_buf[0] = param_entry->entry->const_value.c; break;
					case SYMBOL_CLASS_CONST_STRING:
					{
						strcpy(temp_buf, param_entry->entry->const_value.s);
						if(strlen(p_temp_buf) > 1)
						{
							p_temp_buf++;
							p_temp_buf[strlen(p_temp_buf)-1] = '\0';
						}
					} break;
				}
				while(*p_buffer++=*p_temp_buf++);
				*(p_buffer-1) = ' ';

				param_entry = param_entry->next;
			}
			if(p_buffer > buffer)
				*(p_buffer-1) = '\0';
			else
				*p_buffer = '\0';

			if(g_Interpreter_HTTPResponse==NULL)
				printf("%s\n", buffer);
			else
				HTTPResponse_HTMLText(g_Interpreter_HTTPResponse, buffer);

			Interpreter_FreeParam(&param_list);
		} break;
		case OP_PARAM:
		{
			struct SymbolTableEntryList *param_entry, *last_entry;
			param_entry = (struct SymbolTableEntryList *) calloc(1, sizeof(struct SymbolTableEntryList));
			param_entry->entry = operand1;
			last_entry = param_list;
			while(last_entry && last_entry->next)
				last_entry = last_entry->next;

			if(last_entry)
				last_entry->next = param_entry;
			else
				param_list = param_entry;
		} break;
		case OP_SYMBOLTABLE_ADD:
		{
			RuntimeStorage_AddSymbolTable(storage, (SymbolTable *) operand1);
		} break;
		case OP_SYMBOLTABLE_REMOVE:
		{
			RuntimeStorage_RemoveSymbolTable(storage, (SymbolTable *) operand1);
		} break;
		case OP_ASSIGN:
		{
			Interpreter_Assignment(operand1, operand2);			
			if(operand1->isPtrIndirection == 1)
			{
				SymbolTableEntry *entry = *((SymbolTableEntry **) operand1->ptrEntry->storage);
				Interpreter_Assignment(entry, operand2);
			}
		} break;
		case OP_ADD:
		case OP_SUB:
		case OP_MOD:
		case OP_MUL:
		case OP_DIV:
		case OP_BITAND:
		case OP_BITOR:
		case OP_BITXOR:
		case OP_SHL:
		case OP_SHR:
		{
			switch(operand1->type->op)
			{
				case TYPE_SHORT: Interpreter_ProcessBinaryMathOp(code->op_code, short); break;
				case TYPE_INT: Interpreter_ProcessBinaryMathOp(code->op_code, int); break;
				case TYPE_FLOAT: Interpreter_ProcessBinaryMathOpFloat(code->op_code); break;
				case TYPE_CHAR: Interpreter_ProcessBinaryMathOp(code->op_code, char); break;
				case TYPE_POINTER: Interpreter_ProcessBinaryMathOpPointer(code->op_code); break;
			}
		} break;
		case OP_LT:
		case OP_GT:
		case OP_LE:
		case OP_GE:
		case OP_EQ:
		case OP_NE:
		{
			switch(operand1->type->op)
			{
				case TYPE_SHORT: Interpreter_ProcessBinaryLogicalOp(code->op_code, short); break;
				case TYPE_INT: Interpreter_ProcessBinaryLogicalOp(code->op_code, int); break;
				case TYPE_FLOAT: Interpreter_ProcessBinaryLogicalOp(code->op_code, float); break;
				case TYPE_CHAR: Interpreter_ProcessBinaryLogicalOp(code->op_code, char); break;
				case TYPE_POINTER: Interpreter_ProcessBinaryLogicalOp(code->op_code, void*); break;
			}
		} break;
		case OP_CHARTOINT: Interpreter_ConvertType(char, int); break;
		case OP_CHARTOFLOAT: Interpreter_ConvertType(char, float); break;
		case OP_INTTOFLOAT: Interpreter_ConvertType(int, float); break;
		case OP_INTTOCHAR: Interpreter_ConvertType(int, char); break;
		case OP_FLOATTOCHAR: Interpreter_ConvertType(float, char); break;
		case OP_FLOATTOINT: Interpreter_ConvertType(float, int); break;
		case OP_GOTO:
		{
			int goto_flag, line;

			goto_flag = (int) code->operand1; line = (int) code->operand2;
			switch(goto_flag)
			{
				case GOTO_BACKWARD: (*line_num) -= line; break;
				case GOTO_FORWARD: (*line_num) += line; break;
				case GOTO_ABSOLUTE: (*line_num) = line; break;
			}
			//printf("OP_GOTO : %d\n", *line_num);
			return 0;
		} break;
		case OP_INDIRECTION:
		{
			if(operand1 && operand1->storage)
			{
				Interpreter_GetSymbolTableEntryValue(*((SymbolTableEntry **) operand1->storage), (void *) result->storage, result->type->size);
			}
		} break;
		case OP_ADDRESSOF:
		{
			if(result->storage && operand1)			
				memcpy(result->storage, (void *) &operand1, result->type->size);
		} break;
		case OP_UNARYMINUS:
		case OP_ONESCOMPLEMENT:
		case OP_LOGICALNEGATION:
		{
			switch(operand1->type->op)
			{
				case TYPE_SHORT: Interpreter_ProcessUnaryOperator(short); break;
				case TYPE_INT: Interpreter_ProcessUnaryOperator(int); break;
				case TYPE_CHAR: Interpreter_ProcessUnaryOperator(char); break;
				case TYPE_FLOAT: Interpreter_ProcessUnaryOperatorFloat(); break;
				case TYPE_POINTER: Interpreter_ProcessUnaryOperatorPointer(); break;
			}
		} break;
		case OP_RETURN:
		case OP_END:
		{
			return -1;
		} break;
		default:	;
	}

	(*line_num)++;

	return 0;
}

void Interpreter_GetSymbolTableEntryValue(SymbolTableEntry *entry, void *buffer, int size)
{
/*
Pre : Symbol table entry and buffer sre supplied
Post : Gets the content of the entry and copies into the buffer
*/

	switch(entry->symbol_class)
	{
		case SYMBOL_CLASS_IDENTIFIER: memcpy(buffer, entry->storage, size); break;
		case SYMBOL_CLASS_CONST_INTEGER: *((int *) buffer) = entry->const_value.i; break;
		case SYMBOL_CLASS_CONST_FLOAT: *((float *) buffer) = entry->const_value.f; break;
		case SYMBOL_CLASS_CONST_CHAR: *((char *) buffer) = entry->const_value.c; break;
		case SYMBOL_CLASS_CONST_STRING: *((char **) buffer) = entry->const_value.s; break;
	}	
}

void Interpreter_Assignment(SymbolTableEntry *lvalue_entry, SymbolTableEntry *rvalue_entry)
{
/*
Pre : Symbol table entry for lvalue and rvalue are supplied
Post : Gets the content of the rvalue entry and copies into the lvalue entry location
*/

	switch(rvalue_entry->symbol_class)
	{
		case SYMBOL_CLASS_IDENTIFIER:
		{
			if(lvalue_entry->type->op == TYPE_POINTER && rvalue_entry->type && rvalue_entry->type->op == TYPE_ARRAY)
				memcpy(lvalue_entry->storage, (void *) &rvalue_entry, lvalue_entry->type->size);
			else
				memcpy(lvalue_entry->storage, rvalue_entry->storage, lvalue_entry->type->size);
		} break;
		case SYMBOL_CLASS_KEYWORD: *((int *) lvalue_entry->storage) = rvalue_entry->const_value.i; break;
		case SYMBOL_CLASS_CONST_INTEGER: *((int *) lvalue_entry->storage) = rvalue_entry->const_value.i; break;
		case SYMBOL_CLASS_CONST_FLOAT: *((float *) lvalue_entry->storage) = rvalue_entry->const_value.f; break;
		case SYMBOL_CLASS_CONST_CHAR: *((char *) lvalue_entry->storage) = rvalue_entry->const_value.c; break;
		case SYMBOL_CLASS_CONST_STRING: *((char **) lvalue_entry->storage) = rvalue_entry->const_value.s; break;		
	}	
}

/*LONGPARAM Interpreter_GetSymbolTableEntryValue(SymbolTableEntry *entry)
{

	LONGPARAM rvalue = 0;

	switch(entry->symbol_class)
	{
		case SYMBOL_CLASS_IDENTIFIER: rvalue = *((LONGPARAM *)entry->storage); break;
		case SYMBOL_CLASS_CONST_INTEGER:
		case SYMBOL_CLASS_CONST_FLOAT:
		case SYMBOL_CLASS_CONST_CHAR:
		case SYMBOL_CLASS_CONST_STRING:
		case SYMBOL_CLASS_KEYWORD:
		{
			rvalue = entry->const_value.l;
		} break;
	}
	//printf("GetRValue : symbol_class = %d, rvalue = %d\n", entry->symbol_class, (int) rvalue);
	return rvalue;

}*/

int Interpreter_SetHTTPObject(HTTPRequest *request, HTTPResponse *response)
{
/*
Pre : Helper function
Post : Sets the HTTP request and response object
*/

	g_Interpreter_HTTPRequest = request;
	g_Interpreter_HTTPResponse = response;

	return 0;
}

int Interpreter_FreeParam(struct SymbolTableEntryList **param_list)
{
/*
Pre : Parameter list to be freed is supplied
Post : Frees the parameter list
*/

	struct SymbolTableEntryList *param_entry, *remove_entry;

	param_entry = *param_list;
	while(param_entry)
	{
		remove_entry = param_entry;
		param_entry = param_entry->next;
		free(remove_entry);
	}
	*param_list = NULL;
}

