/*
File Name : symtab.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Contains symbol table manipulation functions. It involves creation
of symbol tables, its entries, looks up an entry in symbol table etc.
*/

#include "symtab.h"
#include <string.h>

SymbolTable *g_SymbolTable_RootTable = NULL; 	// Root symbol table
SymbolTable *g_SymbolTable_CurrentTable = NULL; //Current symbol table

int SymbolTable_Init()
{
/*
Pre : None
Post : Initializes symbol table
*/

	g_SymbolTable_RootTable = SymbolTable_Create(NULL);
	g_SymbolTable_CurrentTable = g_SymbolTable_RootTable;

	SymbolTable_AddEntry(g_SymbolTable_RootTable, SYMBOL_REQUEST_QUERYSTRING, SYMBOL_CLASS_KEYWORD, NULL);
	SymbolTable_AddEntry(g_SymbolTable_RootTable, SYMBOL_RESPONSE_WRITE, SYMBOL_CLASS_KEYWORD, NULL);

	return 0;
}

int SymbolTable_Deinit()
{
/*
Pre : Symbol table is initialized
Post : All the symbol tables along with their entries are destroyed.
*/

	SymbolTable *symtab = NULL;
	if(g_SymbolTable_RootTable)
		SymbolTable_Destroy(g_SymbolTable_RootTable);

	return 0;
}

SymbolTable *SymbolTable_Create()
{
/*
Pre : None
Post : Creates and returns symbol table
*/

	SymbolTable *symtab;
	symtab = (SymbolTable *) calloc(1, sizeof(SymbolTable));
	return symtab;
}

int SymbolTable_Destroy(SymbolTable *symtab)
{
/*
Pre : Symbol table to be destroyed is supplied
Post : Symbol table 'symtab', all its children symbol tables and their entries are destroyed
*/

	int i;
	SymbolTable *child = NULL;
	SymbolTable *next_sibling = NULL;

	if(symtab==NULL)
		return -1;

	child = symtab->first_child;
	while(child)
	{
		next_sibling = child->next_sibling;
		SymbolTable_Destroy(child);
		child = next_sibling;
	}

	for(i=0;i<symtab->num_of_entry;i++)
		if(symtab->entries[i])
			SymbolTableEntry_Destroy(symtab->entries[i], 0);

	if(symtab->symbols_chunk)
		free(symtab->symbols_chunk);

	free(symtab);

	return 0;
}

int SymbolTable_Add(SymbolTable *parent, SymbolTable *new_child)
{
/*
Pre : Parent and new child symbol table is supplied
Post : Sets the 'new_child' as the child of the symbol table 'parent'
*/

	if(!parent->first_child)
	{
		parent->first_child = new_child;
		parent->last_child = new_child;
	}
	else
	{
		parent->last_child->next_sibling = new_child;
		new_child->prev_sibling = parent->last_child;
	}
	parent->last_child =  new_child;
	new_child->parent = parent;
	parent->num_of_child++;

	return 0;
}

SymbolTableEntry *SymbolTable_AddConstEntry(union const_value_type const_value, int symbol_class)
{
/*
Pre : Constant information is supplied
Post : Constant information are stored as entries in the root symbol table
*/

	SymbolTableEntry *entry = NULL;

	entry = SymbolTableEntry_Create(g_SymbolTable_RootTable, symbol_class);
	entry->symbol_class = symbol_class;
	entry->const_value.l = 0L;

	switch(symbol_class)
	{
		case SYMBOL_CLASS_CONST_STRING:
		{
			entry->const_value.s = (char *) malloc(strlen(const_value.s) + 1);
			strcpy(entry->const_value.s, const_value.s);
		} break;
		case SYMBOL_CLASS_CONST_INTEGER:	entry->const_value.i = const_value.i; break;
		case SYMBOL_CLASS_CONST_FLOAT:	entry->const_value.f = const_value.f; break;
		case SYMBOL_CLASS_CONST_CHAR:	entry->const_value.c = const_value.c; break;
	}
	
	g_SymbolTable_RootTable->num_of_entry++;
	g_SymbolTable_RootTable->entries = (SymbolTable **) realloc(g_SymbolTable_RootTable->entries, sizeof(SymbolTable *) * g_SymbolTable_RootTable->num_of_entry);
	g_SymbolTable_RootTable->entries[g_SymbolTable_RootTable->num_of_entry-1] = entry;

	return entry;
}

SymbolTableEntry *SymbolTable_LookUpConst(union const_value_type const_value, int symbol_class)
{
/*
Pre : Constant information is supplied
Post : Constant entry is searched in the root symbol table and if found then return
*/

	SymbolTableEntry *entry = NULL;
	int i;

	for(i=0;i<g_SymbolTable_RootTable->num_of_entry;i++)
		if(g_SymbolTable_RootTable->entries[i]
			&& g_SymbolTable_RootTable->entries[i]->symbol_class==symbol_class)
		{
				switch(symbol_class)
				{
					case SYMBOL_CLASS_CONST_INTEGER:
						if(g_SymbolTable_RootTable->entries[i]->const_value.i == const_value.i)
							return g_SymbolTable_RootTable->entries[i];
					break;
					case SYMBOL_CLASS_CONST_FLOAT:
						if(g_SymbolTable_RootTable->entries[i]->const_value.f == const_value.f)
							return g_SymbolTable_RootTable->entries[i];
					break;
					case SYMBOL_CLASS_CONST_STRING:
						if(strcmp(g_SymbolTable_RootTable->entries[i]->const_value.s, const_value.s)==0)
							return g_SymbolTable_RootTable->entries[i];
					break;
				}
		}

	return NULL;
}

SymbolTableEntry *SymbolTable_AddEntry(SymbolTable *symtab, char *symbol, int symbol_class, int *error_code)
{
/*
Pre : Symbol information is supplied and in which symbol table it is to be stored
Post : Symbol is stored in the symbol table and new created entry is returned
*/

	int i;
	SymbolTableEntry *entry = NULL;

	if(symbol==NULL)
		return NULL;

	for(i=0;i<symtab->num_of_entry;i++)
		if(symtab->entries[i])
			if((symtab->entries[i]->symbol_class==symbol_class) &&
				symtab->entries[i]->symbol &&
				(strcmpi(symtab->entries[i]->symbol, symbol)==0))
				break;

	if(i<symtab->num_of_entry && symtab->num_of_entry!=0)
	{
		if(error_code)
			*error_code=SYMBOLTABLE_ENTRY_ERROR_ALREADY_EXIST;
		return NULL;
	}

	entry = SymbolTableEntry_Create(symtab, symbol_class);

	if(symtab->chunk_size < (symtab->symbols_chunk_wrote_so_far + strlen(symbol) + 1))
	{
		symtab->chunk_size += SYMBOLTABLE_CHUNK_SIZE;
		symtab->symbols_chunk = (char *) realloc(symtab->symbols_chunk, symtab->chunk_size);
	}

	strcpy(&symtab->symbols_chunk[symtab->symbols_chunk_wrote_so_far], symbol);
	entry->symbol = &symtab->symbols_chunk[symtab->symbols_chunk_wrote_so_far];
	symtab->symbols_chunk_wrote_so_far += (strlen(symbol) + 1);

	symtab->num_of_entry++;
	symtab->entries = (SymbolTable **) realloc(symtab->entries, sizeof(SymbolTable *) * symtab->num_of_entry);
	symtab->entries[symtab->num_of_entry-1] = entry;

	if(error_code)
		*error_code = SYMBOLTABLE_ENTRY_SUCCESS;

	return entry;
}

SymbolTableEntry *SymbolTable_LookUp(SymbolTable *symtab, char *symbol, int symbol_class)
{
/*
Pre : Symbol information is supplied and from which symbol table it will start searching
Post : Symbol is searched through this symbol table to the root symbol table until
the symbol is found. If found the corresponding symbol table entry is return.
*/

	SymbolTableEntry *entry = NULL;
	SymbolTable *searching_symtab = NULL;

	searching_symtab = symtab;

	while(searching_symtab)
	{
		int i;

		for(i=0;i<searching_symtab->num_of_entry;i++)
		{
			if(searching_symtab->entries[i]->symbol)
				if(searching_symtab->entries[i]->symbol_class == symbol_class &&
					strcmpi(searching_symtab->entries[i]->symbol, symbol)==0)
						return searching_symtab->entries[i];
		}
		searching_symtab = searching_symtab->parent;
	}

	return NULL;
}

int SymbolTable_Print(SymbolTable *symtab)
{
/*
Pre : Symbol table to be printed is supplied
Post : Prints this and all symbol table children of it along with their entries.
*/

	SymbolTable *child_table;
	int i;

	printf("Symbol Table : %p\n", symtab);

	for(i=0;i<symtab->num_of_entry;i++)
	{
		switch(symtab->entries[i]->symbol_class)
		{
			case SYMBOL_CLASS_IDENTIFIER: printf("\tIdentifier : %p, %d, %s, %s\n", symtab->entries[i], symtab->entries[i]->data_type, symtab->entries[i]->symbol, symtab->entries[i]->type ? symtab->entries[i]->type->entry->symbol : ""); break;
			case SYMBOL_CLASS_CONST_STRING: printf("\tString : %p, %s\n", symtab->entries[i], symtab->entries[i]->const_value.s); break;
			case SYMBOL_CLASS_CONST_INTEGER: printf("\tInteger : %p, %d\n", symtab->entries[i], symtab->entries[i]->const_value.i); break;
			case SYMBOL_CLASS_CONST_FLOAT: printf("\tFloat : %p, %f\n", symtab->entries[i], symtab->entries[i]->const_value.f); break;
			case SYMBOL_CLASS_CONST_CHAR: printf("\tChar : %p, %c\n", symtab->entries[i], symtab->entries[i]->const_value.c); break;
			case SYMBOL_CLASS_TYPE: printf("\tType : %p, %s, %d\n", symtab->entries[i], symtab->entries[i]->symbol, symtab->entries[i]->type->size); break;
		}
	}

	child_table = symtab->first_child;
	while(child_table)
	{
		SymbolTable_Print(child_table);
		child_table = child_table->next_sibling;
	}

	return 0;
}

SymbolTableEntry *SymbolTableEntry_Create(SymbolTable *symtab, int symbol_class)
{
/*
Pre : Symbol table into which the entry to be created
Post : Symbol table entry is created and set it as an entry of the supplied symbol table
*/

	SymbolTableEntry *entry = NULL;

	entry = (SymbolTableEntry *) calloc(1, sizeof(SymbolTableEntry));
	entry->symtab = symtab;
	entry->symbol_class = symbol_class;
	entry->isPtrIndirection = 0;
	entry->ptrEntry = NULL;

	return entry;
}

int SymbolTableEntry_Destroy(SymbolTableEntry *entry, int update_symtab)
{
/*
Pre : Symbol table entry to be destroyed is supplied
Post : Symbol table entry is destroyed and free its value if freeable
*/

	int i;

	if(update_symtab)
	{
		for(i=0;i<entry->symtab->num_of_entry;i++)
			if(entry==entry->symtab->entries[i])
				break;
		if(i==entry->symtab->num_of_entry)
			return -1;

		entry->symtab->entries[i] = NULL;
	}
	if(entry->param && entry->param_free_func)
		(*entry->param_free_func)((void *) entry->param);

	if(entry->symbol_class == SYMBOL_CLASS_CONST_STRING)
		if(entry->const_value.s)
			free((char *) entry->const_value.s);

	/*if(entry->symbol_class == SYMBOL_CLASS_TYPE)
	{
		free(entry->type);
		entry->type = NULL;
	}*/

	if(entry->type)
	{
		/*Type *remove_type, *type;
		type = entry->type;

		while(type)
		{
			if(type->op==TYPE_POINTER || type->op==TYPE_ARRAY)
			{
				remove_type = type;
				type = type->type;
				free(remove_type);
			}
			else
				type = NULL;
		}*/
	}
	free(entry);
	return 0;
}

int SymbolTableEntry_SetDataType(SymbolTableEntry *entry, Type *type)
{
/*
Pre : Entry is an identifier
Post : Sets the data type of the entry
*/

	entry->type = type;
	return 0;
}

int SymbolTableEntry_SetType(SymbolTableEntry *entry, typevar_type type)
{
/*
Pre : Entry is an identifier
Post : Sets the data type of the entry
*/

	entry->data_type = type;
	return 0;
}

int SymbolTableEntry_SetParam(SymbolTableEntry *entry, void *param, ParamFreeFuncType param_free_func)
{
/*
Pre : Sets extra parameter
Post : Sets extra parameter for this entry and its free function
*/

	entry->param = param;
	entry->param_free_func = param_free_func;

	return 0;
}

int SymbolTable_SetCurrentTable(SymbolTable *symtab)
{
/*
Pre : A symbol table is supplied
Post : This symbol table is set to the current symbol table
*/

	g_SymbolTable_CurrentTable = symtab;
}

/*----Not used in the univ project. will be used for further development----*/

int SymbolTable_CalculateAllRelativePos(SymbolTable *symtab)
{
	SymbolTable *child = symtab->first_child;

	while(child)
	{
		SymbolTable_CalculateAllRelativePos(child);
		child = child->next_sibling;
	}
	SymbolTable_CalculateRelativePos(symtab);
}

int SymbolTable_CalculateRelativePos(SymbolTable *symtab)
{
	SymbolTableEntry *entry = NULL;
	int i;
	int relative_pos = 0, size = 0;

	for(i=0;i<symtab->num_of_entry;i++)
	{
		if(symtab->entries[i]->symbol_class == SYMBOL_CLASS_IDENTIFIER)
		{
			symtab->entries[i]->relative_pos_in_mem = relative_pos;
			switch(symtab->entries[i]->data_type)
			{
				case TYPE_INT: size = sizeof(int); break;
				case TYPE_FLOAT: size = sizeof(float); break;
				case TYPE_DOUBLE: size = sizeof(double); break;
				case TYPE_CHAR: size = sizeof(char); break;
				//case TYPE_STRUCT: size = sizeof(int); break;
				default: if((symtab->entries[i]->data_type & TYPE_POINTER) == 1) size = sizeof(int *); break;
			}
			relative_pos += size;
		}
	}

	return 0;
}

