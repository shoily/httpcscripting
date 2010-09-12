/*
File Name : tree.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains data structure and defines for tree (ParseNode)
*/

#ifndef TREE_H
#define TREE_H

#include "common.h"
#include "typecheck.h"
#include "symtab.h"

#define NODE_TERMINAL 		1	// It is a terminal node
#define NODE_NONTERMINAL   2	// It is a nonterminal node

#define ATTRIBUTE_FREE_CONTENT_VALUE		2 	//Dont change this value to any other

//Defines for various attributes
#define ATTRIB_PLACE								"Place"		// Expression's symbol table entry
#define ATTRIB_CODE								"Code"		// Code access
#define ATTRIB_NDIM								"NDim"		// Number of dimension
#define ATTRIB_DIM_PREFIX						"Dimension"	// Dimension
#define ATTRIB_TRUE								"True"		// True label
#define ATTRIB_FALSE								"False"		// False label
#define ATTRIB_STATEMENT_FIRST				"StatementFirst" // Statement first label
#define ATTRIB_STATEMENT_NEXT					"StatementNext"  // Statement next label
#define ATTRIB_STATEMENT_BEGIN				"StatementBegin" // Statement begin label
#define ATTRIB_SYMBOLTABLE						"SymbolTable"	  // Symbol table pointer

#define alloca malloc

typedef int (*TreeAttributeFreeFuncType) (void *);

//Data structure for tree attribute
struct _TreeAttribute
{
	char *attrib_name;			// attribute name
	LONGPARAM value;				// attribute value
	int value_len;					// value length
	int attrib_freeable;			// is attribute name freeable
	int value_freeable;			// is attribute value freeable
	ParseNode *node;				// Attribute associated with the node
	TreeAttributeFreeFuncType free_func;	// Free function
	TreeAttribute *next;			// Next attribute
};

//Data structure for ParseNode (Tree)
struct _ParseNode
{
	ParseNode *parent;			// Parent node
	int num_of_child;				// Number of children
	ParseNode *first_child;		// First child node
	ParseNode *last_child;		// Last child node
	ParseNode *next_sibling;	// Next sibling node
	ParseNode *prev_sibling;	// Prev sibling node
	int nonterminal;				// Nonterminal
	int rule_in_nonterminal;	// rule no
	int terminal_nonterminal;	// terminal / nonterminal id
	int type;						// terminal or nonterminal
	LONGPARAM value;				// Node value
	int value_len;					// Value length
	int alloc_bytes;				// Allocated length of value (may be 0)

	TreeAttribute *attribute;	// Pointer to attributes
};

extern ParseNode *g_Tree_RootNode;

/*Function declaration for tree manipulation */
int Tree_Init();
int Tree_Deinit();
ParseNode *Tree_CreateNode();
Tree_DestroyNode(ParseNode *node);

TreeAttribute *Tree_AttachAttribute(ParseNode *node, char *attrib_name, LONGPARAM value, int value_len, int attrib_freeable, int value_freeable);
int Tree_UpdateAttributeValue(ParseNode *node, char *attrib_name, LONGPARAM value, int value_len, int attrib_freeable, int value_freeable);
int TreeAttribute_UpdateValue(TreeAttribute *attribute, LONGPARAM value, int value_len, int value_freeable);
LONGPARAM Tree_GetAttributeValue(ParseNode *node, char *attrib_name);
int TreeAttribute_SetFreeFunc(TreeAttribute *attribute, TreeAttributeFreeFuncType free_func);

int Tree_AddChild(ParseNode *parent, ParseNode *new_child);
int Tree_AddChildAtFirst(ParseNode *parent, ParseNode *new_child);
int Tree_SetNodeValue(ParseNode *node, int nonterminal, int rule_in_nonterminal, int terminal_nonterminal, int type, LONGPARAM value, int value_len);

ParseNode *Tree_QueryFirstNodeDown(ParseNode *node, int nonterminal);
ParseNode *Tree_QueryNextSiblingNodeDown(ParseNode *node, int nonterminal);

//Data strucuture for parse node stack element. Used to construct parse tree in bottom-up parse*/
typedef struct _ParseNodeStackElem ParseNodeStackElem;

struct _ParseNodeStackElem
{
	ParseNode *node;				// Node
	ParseNodeStackElem *prev;	// Previous node stack element
	ParseNodeStackElem *next;	// Next node stack element
};


//Parse node stack
typedef struct _ParseNodeStack ParseNodeStack;

struct _ParseNodeStack
{
	ParseNodeStackElem *first;	// First node stack element
	ParseNodeStackElem *top;	// Top node stack element
};

extern ParseNodeStack *g_Tree_NodeStack;

//Function declaration for constructing parse tree in bottom-up parse
int ParseNodeStack_Push(ParseNodeStack *stack, ParseNode *node);
ParseNode *ParseNodeStack_Pop(ParseNodeStack *stack);
int MAKE_TREE(int nonterminal, int num_of_child, int rule);
int MAKE_PUSH_NODE(int nonterminal, int terminal_nonterminal, LONGPARAM value, int value_len);

//Data structure for queue
typedef struct _Queue Queue;

struct _Queue
{
	void *elem;		// Queue element
	Queue *next;	// Next queue
};

//Function declaration for queue manipulation
Queue *Queue_Create();
void Queue_Destroy(Queue **queue);
void Queue_InsertAtFront(Queue **queue, void *elem);
void *Queue_RemoveFromFront(Queue **queue);
void Queue_Append(Queue **queue, void *elem);
void Queue_InsertQueueAtFront(Queue **queue, Queue *new_queue);

#endif

