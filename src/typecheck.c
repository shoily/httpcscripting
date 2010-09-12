/*
File Name : typecheck.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Installs identifiers and constants into the symbol table along
with their type information. It traverses the tree to find for global and local
declaration of identifiers, functions.
*/

#include "typecheck.h"
#include "tree.h"
#include "common.h"
#include "symtab.h"
#include "c-bison_tab.h"

Type *g_typecheck_void_type = NULL;
Type *g_typecheck_int_type = NULL;
Type *g_typecheck_short_type = NULL;
Type *g_typecheck_float_type = NULL;
Type *g_typecheck_double_type = NULL;
Type *g_typecheck_char_type = NULL;

static int g_typecheck_is_statement = COMPILER_NO;	// Global variables to check for the statements
static int g_typecheck_is_declaration = COMPILER_NO; // Global variables to check for the declarations

static TypeEntry *g_typecheck_TypeEntry = NULL;


//Helper macro to create a type. It is here mainly to extended the type information for future.
#define NEW_TYPE(op)	{ Type newType; newType.op = op; TypeCheck_CreateType(&newType, NULL); }

void TypeCheck_addTypeEntry(Type *type)
{
	TypeEntry *typeEntry;

	typeEntry = calloc(1, sizeof(TypeEntry));
	typeEntry->type = type;
	typeEntry->next = g_typecheck_TypeEntry;
	g_typecheck_TypeEntry = typeEntry;
}

Type *TypeCheck_CreateType(Type *newType, Type *linkType)
{
/*
Pre : None
Post : Creates new type
*/

	SymbolTableEntry *entry;
	Type *type = NULL;
	char *strType;

	newType->type = linkType;
	
	strType = TypeCheck_GetTypeString(newType);
	
	if((newType->op !=TYPE_STRUCT) && (entry = SymbolTable_LookUp(g_SymbolTable_CurrentTable, strType, SYMBOL_CLASS_TYPE)))
	{
		type = entry->type;
	}
	else
	{
		TypeEntry *type_entry;		

		entry = SymbolTable_AddEntry(g_SymbolTable_CurrentTable, strType, SYMBOL_CLASS_TYPE, NULL);
		type = (Type *) calloc(1, sizeof(Type));
		type->size = TypeCheck_GetSize(newType);
		type->op = newType->op;
		type->entry = entry;
		type->type = linkType;
		type->info = newType->info;
		entry->type = type;

		type_entry = calloc(1, sizeof(TypeEntry));
		type_entry->next = g_typecheck_TypeEntry;
		g_typecheck_TypeEntry = type_entry;
	}

	return type;
}

int TypeCheck_Init()
{
/*
Pre : None
Post : Initializes type checking module
*/
	TypeCheck_Install_Types();
	return 0;
}

int TypeCheck_Deinit()
{
/*
Pre : None
Post : None
*/
	TypeEntry *typeEntry;

	while(g_typecheck_TypeEntry)
	{
		typeEntry = g_typecheck_TypeEntry->next;
		free(g_typecheck_TypeEntry);
		g_typecheck_TypeEntry = typeEntry;
	}

	g_typecheck_TypeEntry = NULL;

	return 0;
}

int TypeCheck_Install_Types()
{
/*
Pre : Symbol table module should be initialized before
Post : Installs basic types
*/
	Type t;

	t.op = TYPE_VOID; g_typecheck_void_type = TypeCheck_CreateType(&t, NULL);
	t.op = TYPE_INT; g_typecheck_int_type = TypeCheck_CreateType(&t, NULL);
	t.op = TYPE_SHORT; g_typecheck_short_type = TypeCheck_CreateType(&t, NULL);
	t.op = TYPE_FLOAT; g_typecheck_float_type = TypeCheck_CreateType(&t, NULL);
	t.op = TYPE_DOUBLE; g_typecheck_double_type = TypeCheck_CreateType(&t, NULL);
	t.op = TYPE_CHAR; g_typecheck_char_type = TypeCheck_CreateType(&t, NULL);

	return 0;
}

int TypeCheck_DestroyType(Type *type)
{
/*
Pre : Type info is present
Post : Destroys type
*/
	free(type);
}

ParseNode *TypeCheck_QueryNode(ParseNode *node, int nonterminal, int level)
{
	ParseNode *searchnode = node->parent;

	level--;
	while(searchnode
			&&	searchnode->type==NODE_NONTERMINAL
			&& (searchnode->terminal_nonterminal!=nonterminal || nonterminal==NONTERMINAL_NONE)
			&& level)
	{
		searchnode = searchnode->parent;
		level--;
	}

	if(searchnode==NULL
		|| (searchnode && searchnode->terminal_nonterminal!=nonterminal && nonterminal!=NONTERMINAL_NONE))
		return NULL;

	return searchnode;
}

typevar_type TypeCheck_GetInitialType(ParseNode *node)
{
/*
Pre : None
Post : Gets the basic type information
*/
	ParseNode *node_type_specifier;

	node_type_specifier = Tree_QueryFirstNodeDown(node, NONTERMINAL_type_specifier);

	return TypeCheck_GetTypeSpecifierType(node_type_specifier->first_child->terminal_nonterminal);
}

int TypeCheck_GetPointerCounter(ParseNode *node)
{
/*
Pre : None
Post : Returns how many pointer indirection is associated with this identifier
*/
	int counter = 0;
	ParseNode *node_pointer;

	node_pointer = node;

	do
	{
		node_pointer = Tree_QueryFirstNodeDown(node_pointer, NONTERMINAL_pointer);
		if(node_pointer)
		{
			node_pointer = node_pointer->first_child->next_sibling;
			counter++;
		}
	}
	while(node_pointer);

	return counter;
}

ParamInfo *TypeCheck_GetParam(ParseNode *node, int *num_of_param)
{
/*
Pre : Node is a function definition node
Post : Installs parameters of function into symbol table
*/
	ParseNode *node_parameter_declaration;
	Queue *queue;
	ParamInfo *p_info;
	int num_param = 0;

	queue = Queue_Create();

	node_parameter_declaration = Tree_QueryFirstNodeDown(node, NONTERMINAL_parameter_declaration);

	while(node_parameter_declaration)
	{
		p_info = (ParamInfo *) calloc(1, sizeof(ParamInfo));
		TypeCheck_MakeParameterType(node_parameter_declaration, &p_info->name, &p_info->data_type);
		Queue_Append(&queue, (void *) p_info);
		num_param++;

		node_parameter_declaration = Tree_QueryNextSiblingNodeDown(node_parameter_declaration, NONTERMINAL_parameter_declaration);
	}

	*num_of_param = num_param;
	return queue;
}

void TypeCheck_MakeParameterType(ParseNode *node, char **name, int *data_type)
{
/*
Pre : None
Post : Make a parameter from the basic type and number of pointer indirection
*/
	/*int pointer_counter, pval;
	typevar_type initial_type;
	ParseNode *node_identifier;

	initial_type = TypeCheck_GetInitialType(node->first_child->first_child);
	pointer_counter = TypeCheck_GetPointerCounter(node->first_child->next_sibling->first_child); // Points to pointer_opt

	*data_type = TypeCheck_MakeTypeFromPointerCounter(initial_type, pointer_counter);
	node_identifier = Tree_QueryFirstNodeDown(node, NONTERMINAL_identifier);
	*name = (char *) node_identifier->first_child->value;*/
}

int TypeCheck_ProcessGlobalDeclaration(ParseNode *node_external_declaration)
{
/*
Pre : None
Post : Process global declarations.
*/
	ParseNode *node_declaration, *node_init_declarator, *node_direct_declarator, *node_identifier;
	typevar_type initial_type, data_type;
	int pointer_counter;
	SymbolTableEntry *entry;

	node_declaration = node_external_declaration->first_child;
	if(node_declaration->terminal_nonterminal!=NONTERMINAL_declaration)
		return -1;

	//printf("ProcessGlobalDeclaration\n");
	initial_type = TypeCheck_GetInitialType(node_declaration);

	node_init_declarator = Tree_QueryFirstNodeDown(node_declaration, NONTERMINAL_init_declarator);
	while(node_init_declarator)
	{
		pointer_counter = TypeCheck_GetPointerCounter(node_init_declarator);
		//data_type = TypeCheck_MakeTypeFromPointerCounter(initial_type, pointer_counter);
		node_identifier = Tree_QueryFirstNodeDown(node_init_declarator, NONTERMINAL_identifier);

		entry = SymbolTable_AddEntry(g_SymbolTable_CurrentTable, (char *) node_identifier->first_child->value, SYMBOL_CLASS_IDENTIFIER, NULL);
		//Check whether it is a function or ordinary variable declaration
		node_direct_declarator = Tree_QueryFirstNodeDown(node_init_declarator, NONTERMINAL_direct_declarator);

		if(node_direct_declarator->first_child->terminal_nonterminal == NONTERMINAL_direct_declarator
			&& node_direct_declarator->first_child->next_sibling
			&& node_direct_declarator->first_child->next_sibling->type == NODE_TERMINAL
			&& node_direct_declarator->first_child->next_sibling->terminal_nonterminal == '(')
		{
			SymbolTable *symtab;
			TypeCheck_Function *func;

			SymbolTableEntry_SetType(entry, TYPE_FUNCTION);

			symtab = SymbolTable_Create();
			SymbolTable_Add(g_SymbolTable_CurrentTable, symtab);

			func = (TypeCheck_Function *) calloc(1, sizeof(TypeCheck_Function));
			func->return_type = data_type;
			func->func_symtab = symtab;
			SymbolTableEntry_SetParam(entry, func, (ParamFreeFuncType) TypeCheck_Free_Function);

			TypeCheck_HandleFuncParams(node_init_declarator, symtab, entry, func);
		}
		else
		{
				SymbolTableEntry_SetType(entry, data_type);
		}

		node_init_declarator = Tree_QueryNextSiblingNodeDown(node_init_declarator, NONTERMINAL_init_declarator);
	}

	return 0;
}

int TypeCheck_ProcessLocalDeclaration(ParseNode *node)
{
/*
Pre : None
Post : Process local declarations
*/
	ParseNode *node_list, *node_declaration, *node_init_declarator, *node_direct_declarator, *node_identifier;
	int initial_type;
	int pointer_counter;
	SymbolTableEntry *entry;
	Type *type = NULL;
	Type newType;

	node_declaration = Tree_QueryFirstNodeDown(node, NONTERMINAL_declaration);
	while(node_declaration)
	{
		initial_type = TypeCheck_GetInitialType(node_declaration);
		memset(&newType, '\0', sizeof(Type));
		newType.op = initial_type;
		type = TypeCheck_CreateType(&newType, NULL);

		node_init_declarator = Tree_QueryFirstNodeDown(node_declaration, NONTERMINAL_init_declarator);
		while(node_init_declarator)
		{
			pointer_counter = TypeCheck_GetPointerCounter(node_init_declarator);
			while(pointer_counter--)
			{
				Type newType;
				memset(&newType, '\0', sizeof(Type));
				newType.op = TYPE_POINTER;
				type = TypeCheck_CreateType(&newType, type);
			}
	
			node_direct_declarator = Tree_QueryFirstNodeDown(node_init_declarator, NONTERMINAL_direct_declarator);
			type = TypeCheck_Process_direct_declarator(node_direct_declarator, type);

			node_identifier = Tree_QueryFirstNodeDown(node_direct_declarator, NONTERMINAL_identifier);

			entry = (SymbolTableEntry *) Tree_GetAttributeValue(node_identifier, ATTRIB_PLACE);

			SymbolTableEntry_SetType(entry, initial_type);
			SymbolTableEntry_SetDataType(entry, type);


			//printf("Local declaration for %s, %p, %p\n", entry->symbol, entry, g_SymbolTable_CurrentTable);

			node_init_declarator = Tree_QueryNextSiblingNodeDown(node_init_declarator, NONTERMINAL_init_declarator);
		}

		node_declaration = Tree_QueryNextSiblingNodeDown(node_declaration, NONTERMINAL_declaration);
	}

	return 0;
}

void TypeCheck_HandleFuncParams(ParseNode *node, SymbolTable *symtab, SymbolTableEntry *func_entry, TypeCheck_Function *func)
{
/*
Pre : None
Post : Handles function parameters
*/
	int i;
	SymbolTableEntry *param_entry;
	ParseNode *param_type_list_node;
	int num_of_func_param;
	ParamInfo *p_info;
	Queue *queue_param;

	param_type_list_node = Tree_QueryFirstNodeDown(node, NONTERMINAL_parameter_type_list_opt);

	queue_param = TypeCheck_GetParam(param_type_list_node, &num_of_func_param);

	func->num_of_func_param = num_of_func_param;
	func->func_params = (SymbolTableEntry **) malloc(sizeof(SymbolTableEntry *) * func->num_of_func_param);

	//printf("Function Definition information...\n");
	//printf("Function name : %s, Return type : %d\n", func_entry->symbol, func->return_type);
	//printf("Number of param : %d\n", num_of_func_param);
	for(i=0;i<num_of_func_param;i++)
	{
		p_info = (ParamInfo *) Queue_RemoveFromFront(&queue_param);
		param_entry = SymbolTable_AddEntry(symtab, p_info->name, SYMBOL_CLASS_IDENTIFIER, NULL);
		SymbolTableEntry_SetType(param_entry, p_info->data_type);
		param_entry->is_param = COMPILER_YES;
		func->func_params[i] = param_entry;
		//printf("\tParam name : %s, data_type : %d\n", p_info->name, p_info->data_type);
		free(p_info);
	}

	Queue_Destroy(&queue_param);
}

int TypeCheck_PopulateType(ParseNode *node)
{
/*
Pre : None
Post : Populates type information
*/
	ParseNode *child = NULL;
	ParseNode *prev_sibling = NULL;

	child = node->first_child;

	//if(g_typecheck_is_declaration == COMPILER_NO)
	//	goto TypeCheck_Populate_EnumChildren;

	switch(node->type)
	{
		case NODE_TERMINAL: break;
		case NODE_NONTERMINAL:
		{
			switch(node->terminal_nonterminal)
			{
				case NONTERMINAL_statement_list_opt:
				{
					//g_typecheck_is_statement = COMPILER_YES;
				} break;
				case NONTERMINAL_function_definition:
				{
					int pointer_counter;
					typevar_type initial_type;
					SymbolTableEntry *func_entry;
					ParseNode *func_name_node;
					SymbolTable *symtab;
					TypeCheck_Function *func;

					func_name_node = Tree_QueryFirstNodeDown(node, NONTERMINAL_identifier);

					if((func_entry = SymbolTable_LookUp(g_SymbolTable_CurrentTable, (char *) func_name_node->first_child->value, SYMBOL_CLASS_IDENTIFIER))!=NULL
						&& func_entry->data_type!=0)
					{
						symtab = ((TypeCheck_Function *)(func_entry->param))->func_symtab;
						SymbolTable_SetCurrentTable(symtab);
						Tree_AttachAttribute(node, ATTRIB_SYMBOLTABLE, (LONGPARAM) symtab, sizeof(SymbolTable *), 0, 0);
						break;
					}

					initial_type = TypeCheck_GetInitialType(node->first_child);
					pointer_counter = TypeCheck_GetPointerCounter(node->first_child->next_sibling->first_child); // Points to pointer_opt

					func_entry = SymbolTable_AddEntry(g_SymbolTable_CurrentTable, (char *) func_name_node->first_child->value, SYMBOL_CLASS_IDENTIFIER, NULL);
					SymbolTableEntry_SetType(func_entry, TYPE_FUNCTION);

					symtab = SymbolTable_Create();
					SymbolTable_Add(g_SymbolTable_CurrentTable, symtab);

					func = (TypeCheck_Function *) calloc(1, sizeof(TypeCheck_Function));
					func->return_type = initial_type;
					func->func_symtab = symtab;
					SymbolTableEntry_SetParam(func_entry, func, (ParamFreeFuncType) TypeCheck_Free_Function);

					//TypeCheck_HandleFuncParams(node, symtab, func_entry, func);

					//printf("Function definition : %p, %p\n", g_SymbolTable_CurrentTable, symtab);
					SymbolTable_SetCurrentTable(symtab);

					Tree_AttachAttribute(node, ATTRIB_SYMBOLTABLE, (LONGPARAM) symtab, sizeof(SymbolTable *), 0, 0);
				} break;
				case NONTERMINAL_compound_statement:
				{
					//if(node->parent->terminal_nonterminal != NONTERMINAL_function_definition)
					//{
						SymbolTable *symtab = SymbolTable_Create();
						SymbolTable_Add(g_SymbolTable_CurrentTable, symtab);
						//printf("Compound statement : %p, %p\n", g_SymbolTable_CurrentTable, symtab);
						SymbolTable_SetCurrentTable(symtab);
						Tree_AttachAttribute(node, ATTRIB_SYMBOLTABLE, (LONGPARAM) symtab, sizeof(SymbolTable *), 0, 0);
					//}
				} break;
				case NONTERMINAL_external_declaration:
				{
					//TypeCheck_ProcessGlobalDeclaration(node);
				} break;
				case NONTERMINAL_declaration_list_opt:
				{
					g_typecheck_is_declaration = COMPILER_YES;
				} break;
			}
		} break;
	}

TypeCheck_Populate_EnumChildren:

	while(child)
	{
		TypeCheck_PopulateType(child);

		prev_sibling = child;
		child = child->next_sibling;
	}

	if(g_typecheck_is_declaration == COMPILER_NO)
		return;

	switch(node->type)
	{
		case NODE_TERMINAL: break;
		case NODE_NONTERMINAL:
		{
			switch(node->terminal_nonterminal)
			{
				case NONTERMINAL_function_definition:
				{
					SymbolTable_SetCurrentTable(g_SymbolTable_CurrentTable->parent);
				} break;
				case NONTERMINAL_statement_list_opt:
				{
					g_typecheck_is_statement = COMPILER_NO;
				} break;
				case NONTERMINAL_compound_statement:
				{
					//if(node->parent->terminal_nonterminal != NONTERMINAL_function_definition)
					//{
						SymbolTable_SetCurrentTable(g_SymbolTable_CurrentTable->parent);
					//}
				} break;
				case NONTERMINAL_declaration_list_opt:
				{
					TypeCheck_ProcessLocalDeclaration(node);
				} break;
			}
		} break;
	}

	return 0;
}

int TypeCheck_GetTypeSpecifierType(int KeyWord)
{
/*
Pre : None
Post : Returns type id from a keyword
*/
	int type;

	switch(KeyWord)
	{
		case KW_VOID: type = TYPE_VOID; break;
		case KW_INT: type = TYPE_INT; break;
		case KW_CHAR: type = TYPE_CHAR; break;
		case KW_FLOAT: type = TYPE_FLOAT; break;
		case KW_DOUBLE: type = TYPE_DOUBLE; break;
		case KW_STRUCT: type = TYPE_STRUCT; break;
	}

	return type;
}

int TypeCheck_Free_Function(TypeCheck_Function *func)
{
/*
Pre : TypeCheck_Function type is provided
Post : Frees funtion parameter list
*/
	if(func==NULL)
		return -1;

	//printf("TypeCheck_Free_Function\n");

	if(func->func_params)
		free(func->func_params);

	free(func);
	return 0;
}


extern char * const yynonterminalname[];


int TypeCheck_GetSize(Type *type)
{
	int size = 0;
	switch(type->op)
	{
		case TYPE_VOID: size = 0; break;
		case TYPE_INT: size = TYPE_SIZE_INT; break;
		case TYPE_SHORT: size = TYPE_SIZE_SHORT; break;
		case TYPE_CHAR: size = TYPE_SIZE_CHAR; break;
		case TYPE_FLOAT: size = TYPE_SIZE_FLOAT; break;
		case TYPE_DOUBLE: size = TYPE_SIZE_DOUBLE; break;
		case TYPE_BOOLEAN: size = TYPE_SIZE_BOOLEAN; break;
		//case TYPE_STRUCT: size = TYPE_SIZE_INT; strcat(key_str, linkType->entry->symbol); break;
		case TYPE_POINTER: size = TYPE_SIZE_POINTER; break;
		case TYPE_ARRAY: size = TypeCheck_GetSize(type->type) * type->info.Type_Array.nelem; break;
	}

	return size;
}


char *TypeCheck_GetTypeString(Type *type)
{
	static char key_str[100];

	key_str[0] = '\0';
	switch(type->op)
	{
		case TYPE_VOID: strcpy(key_str, "void"); break;
		case TYPE_INT: strcpy(key_str, "int"); break;
		case TYPE_SHORT: strcpy(key_str, "short"); break;
		case TYPE_CHAR: strcpy(key_str, "char"); break;
		case TYPE_FLOAT: strcpy(key_str, "float"); break;
		case TYPE_DOUBLE: strcpy(key_str, "double"); break;
		case TYPE_BOOLEAN: strcpy(key_str, "boolean"); break;
		case TYPE_STRUCT: strcpy(key_str, "struct "); strcat(key_str, type->type->entry->symbol); break;
		case TYPE_POINTER: strcpy(key_str, type->type->entry->symbol); strcat(key_str, "*"); break;
		case TYPE_ARRAY:
		{
			char strSize[20];

			strcpy(key_str, type->type->entry->symbol);
			strcat(key_str, "[");
			itoa(type->info.Type_Array.nelem, strSize, 10);
			strcat(key_str, strSize);
			strcat(key_str, "]");
		} break;
	}

	return key_str;
}


int TypeCheck_Process_function_definition(ParseNode *node)
{
	Type *type;
	SymbolTableEntry *func_entry;
	SymbolTable *symtab;
	TypeCheck_Function *func;

	TypeCheck_Process_declaration_specifiers(node->first_child, &type);
	TypeCheck_Process_declarator(node->first_child->next_sibling, type, &func_entry);

	//printf("func entry : %d, %d, %s\n", type, func_entry, func_entry->symbol);

					if(func_entry->param!=NULL)
					{
						SymbolTable_SetCurrentTable(((TypeCheck_Function *)(func_entry->param))->func_symtab);
						return 0;
					}
					//func_entry = SymbolTable_AddEntry(g_SymbolTable_CurrentTable, (char *) func_name_node->first_child->value, SYMBOL_CLASS_IDENTIFIER, NULL);
					//SymbolTableEntry_SetType(func_entry, TYPE_FUNCTION);

					func_entry->type = TypeCheck_CreateType(TYPE_FUNCTION, 0, NULL, NULL);
					func_entry->type->type = type;

					symtab = SymbolTable_Create();
					SymbolTable_Add(g_SymbolTable_CurrentTable, symtab);

					/*func = (TypeCheck_Function *) calloc(1, sizeof(TypeCheck_Function));
					//func->return_type = TypeCheck_MakeTypeFromPointerCounter(initial_type, pointer_counter);
					func->func_symtab = symtab;
					SymbolTableEntry_SetParam(func_entry, func, (ParamFreeFuncType) TypeCheck_Free_Function);

					TypeCheck_HandleFuncParams(node, symtab, func_entry, func);*/

					SymbolTable_SetCurrentTable(symtab);

	TypeCheck_Process_compound_statement(node->first_child->next_sibling->next_sibling);

	return 0;
}

int TypeCheck_Process_compound_statement(ParseNode *node)
{
	SymbolTable *symtab;
	if(node->parent->terminal_nonterminal != NONTERMINAL_function_definition)
	{
		symtab = SymbolTable_Create();
		SymbolTable_Add(g_SymbolTable_CurrentTable, symtab);
		SymbolTable_SetCurrentTable(symtab);
	}

	TypeCheck_Process_declaration_list_opt(node->first_child);

	SymbolTable_SetCurrentTable(symtab->parent);

	return 0;
}

int TypeCheck_Process_declaration_list_opt(ParseNode *node)
{
	//printf("Before process declaration list 1\n");
	if(node->type == NODE_NONTERMINAL &&
		node->terminal_nonterminal == NONTERMINAL_declaration_list_opt &&
		node->first_child &&
		node->first_child->terminal_nonterminal == NONTERMINAL_declaration_list)
	{
		//printf("Before process declaration list\n");
		TypeCheck_Process_declaration_list(node->first_child);
	}

	return 0;
}

int TypeCheck_Process_declaration_list(ParseNode *node)
{
	switch(node->type)
	{
		case NODE_TERMINAL: break;
		case NODE_NONTERMINAL:
		{
			switch(node->terminal_nonterminal)
			{
				case NONTERMINAL_declaration_list:
				{
					switch(node->rule_in_nonterminal)
					{
						case 1:
						{
							TypeCheck_Process_declaration_list(node->first_child);
							TypeCheck_Process_declaration(node->first_child->next_sibling);
						} break;
						case 2:
						{
							TypeCheck_Process_declaration(node->first_child);
						} break;
					}
				} break;
			}
		} break;
	}

	return 0;
}

int TypeCheck_Process_init_declarator_list(ParseNode *node, Type *type)
{
	ParseNode *child;

	switch(node->type)
	{
		case NODE_TERMINAL: break;
		case NODE_NONTERMINAL:
		{
			switch(node->terminal_nonterminal)
			{
				case NONTERMINAL_init_declarator_list:
				{
					switch(node->rule_in_nonterminal)
					{
						case 2:
						{
							TypeCheck_Process_init_declarator_list(node->first_child, type);
							TypeCheck_Process_init_declarator(node->first_child->next_sibling, type);
						} break;
						case 1:
						{
							TypeCheck_Process_init_declarator(node->first_child, type);
						} break;
					}
				} break;
			}
		} break;
	}

	return 0;
}

int TypeCheck_Process_init_declarator(ParseNode *node, Type *type)
{
	SymbolTableEntry *entry;
	TypeCheck_Process_declarator(node->first_child, type, &entry);
}

int TypeCheck_GetConstantExpressionValue(ParseNode *node)
{
	ParseNode *node_constant;	

	node_constant = Tree_QueryFirstNodeDown(node, NONTERMINAL_constant);	
	return (int) node_constant->first_child->value;
}

Type *TypeCheck_Process_direct_declarator(ParseNode *node, Type *linkType)
{
	Type *type = NULL;

	switch(node->terminal_nonterminal)
	{
		case NONTERMINAL_direct_declarator:
		{
			switch(node->rule_in_nonterminal)
			{
				case 3:		// direct_declarator ( parameter_type_list_opt )
				{
					//TypeCheck_Process_direct_declarator(node->first_child, type, entry);
					//TypeCheck_Process_parameter_type_list_opt(node->first_child->next_sibling->next_sibling, type, entry);
					return NULL;
				} break;
				case 2:		// direct_declarator [ constant_expression_opt ]
				{
					Type newType;
					ParseNode *node_constant_expression;					

					type = TypeCheck_Process_direct_declarator(node->first_child, linkType);

					node_constant_expression = node->first_child->next_sibling->next_sibling;
					
					memset(&newType, '\0', sizeof(Type));
					newType.op = TYPE_ARRAY;					
					newType.info.Type_Array.nelem = TypeCheck_GetConstantExpressionValue(node_constant_expression);

					return TypeCheck_CreateType(&newType, type);
				} break;
				case 4:		// identifier
				{
					SymbolTableEntry *entry;

					entry = SymbolTable_AddEntry(g_SymbolTable_CurrentTable, (char *) node->first_child->first_child->value, SYMBOL_CLASS_IDENTIFIER, NULL);
					Tree_AttachAttribute(node->first_child, ATTRIB_PLACE, (LONGPARAM) entry, sizeof(SymbolTableEntry *), 0, 0);

					return linkType;
				} break;
			}

		} break;
	}

	return NULL;
}

int TypeCheck_Process_declarator(ParseNode *node, Type *type, SymbolTableEntry **entry)
{
	ParseNode *child;
	Type *ptr_type = NULL, *type2 = NULL, *enum_type;

	TypeCheck_Process_pointer_opt(node->first_child, &ptr_type);

	enum_type = ptr_type;
	while(enum_type && enum_type->type)
		enum_type = enum_type->type;

	enum_type->type = type2;
	type2->type = type;
	if(type2->op == TYPE_ARRAY)
	{
		//type2->size = type2
	}

	(*entry)->type = ptr_type;

	return 0;
}

int TypeCheck_Process_pointer_opt(ParseNode *node, Type **type)
{
	int pointer_counter;
	Type *new_type, *op_type = NULL;

	pointer_counter = TypeCheck_GetPointerCounter(node);

	while(pointer_counter--)
	{
		new_type = TypeCheck_CreateType(TYPE_POINTER, sizeof(void *), NULL, NULL);
		new_type->type = op_type;
		op_type = new_type;
	}
	*type = new_type;

	return 0;
}

int TypeCheck_Process_parameter_type_list_opt(ParseNode *node)
{
	if(node->type == NODE_NONTERMINAL &&
		node->terminal_nonterminal == NONTERMINAL_parameter_type_list_opt &&
		node->first_child &&
		node->first_child->terminal_nonterminal == NONTERMINAL_parameter_list)
	{
		TypeCheck_Process_parameter_list(node->first_child);
	}

	return 0;

}

int TypeCheck_Process_parameter_list(ParseNode *node)
{
}

int TypeCheck_Process_parameter_declaration(ParseNode *node)
{
}

int TypeCheck_Process_declaration(ParseNode *node)
{
	Type *type;

	TypeCheck_Process_declaration_specifiers(node->first_child, &type);
	TypeCheck_Process_init_declarator_list(node->first_child->next_sibling, type);

	return 0;
}

int TypeCheck_Process_declaration_specifiers(ParseNode *node, Type **type)
{
	SymbolTableEntry *entry;
	char *KeyWord;

	KeyWord = TypeCheck_GetTypeString((int) node->first_child->first_child->terminal_nonterminal);
	entry = SymbolTable_LookUp(g_SymbolTable_CurrentTable, KeyWord, SYMBOL_CLASS_TYPE);
	//printf("TYPE NAME : %s, %d, %s\n", (int) KeyWord, node->first_child->first_child->terminal_nonterminal, yynonterminalname[node->first_child->terminal_nonterminal-1]);

	if(entry) *type = entry->type;

	return 0;
}

int TypeCheck_Process_constant_expression(ParseNode *node, SymbolTableEntry **entry)
{
	ParseNode *child;

	child = node->first_child;
	while(child)
	{
		TypeCheck_Process_constant_expression(child, entry);
		child = child->next_sibling;
	}

	if(node->type == NODE_TERMINAL)
		return -1;

	switch(node->terminal_nonterminal)
	{
		case NONTERMINAL_constant:
		{
			TypeCheck_Process_constant(node, entry);
		} break;
		case NONTERMINAL_identifier:
		{
			TypeCheck_Process_identifier(node, entry);
		} break;
	}
}

int TypeCheck_Process_constant(ParseNode *node, SymbolTableEntry **entry)
{
	int symbol_class;
	union const_value_type const_value;

	switch(node->first_child->terminal_nonterminal)
	{
		case CONSTANT_INTEGER: const_value.i = (int) node->first_child->value; symbol_class = SYMBOL_CLASS_CONST_INTEGER; break;
		case CONSTANT_FLOATING: const_value.f = (float) node->first_child->value; symbol_class = SYMBOL_CLASS_CONST_FLOAT; break;
		case CONSTANT_CHAR: const_value.c = (char) node->first_child->value; symbol_class = SYMBOL_CLASS_CONST_CHAR; break;
	}

	if((*entry=SymbolTable_LookUpConst(const_value, symbol_class))==NULL)
		*entry = SymbolTable_AddConstEntry(const_value, symbol_class);

	return 0;
}

int TypeCheck_Process_identifier(ParseNode *node, SymbolTableEntry **entry)
{

	if((*entry = SymbolTable_LookUp(g_SymbolTable_CurrentTable, (char *) node->first_child->value, SYMBOL_CLASS_IDENTIFIER))==NULL)
	{
		*entry = SymbolTable_AddEntry(g_SymbolTable_CurrentTable, (char *) node->first_child->value, SYMBOL_CLASS_IDENTIFIER, NULL);
	}

	return 0;
}

