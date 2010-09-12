/*
File Name : tree.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Contains tree and attributes on given node manipulation function.
Initializes/deinitializes tree and its attributes, adding child to nodes.
Creates tree using bottom-parsing technique employed by the parser module.
*/

#include <stdio.h>

#include "tree.h"
#include "c-bison_tab.h"

ParseNode *g_Tree_RootNode = NULL;	// Root node of the tree
ParseNodeStack *g_Tree_NodeStack = NULL; // Stack to create the tree in bottom-parse

// Nonterminal names. Used at the time of printing the node of the tree
const char * const yynonterminalname[] = {
"translation_unit","external_declaration","function_definition","declaration",
"declaration_list","declaration_specifiers_opt","declaration_specifiers",
"type_specifier","struct_or_union_specifier","struct_or_union","struct_declaration_list",
"init_declarator_list","init_declarator_list_opt","init_declarator","struct_declaration",
"specifier_qualifier_list","specifier_qualifier_list_opt","struct_declarator_list",
"struct_declarator","declarator","direct_declarator","pointer","pointer_opt",
"parameter_type_list","parameter_type_list_opt","parameter_list","parameter_declaration",
"","","initializer","","type_name","","","","","statement","labeled_statement",
"expression_statement","compound_statement","declaration_list_opt","statement_list_opt",
"statement_list","selection_statement","iteration_statement","jump_statement",
"expression","assignment_expression","assignment_operator","constant_expression",
"constant_expression_opt","conditional_expression","logical_OR_expression",
"logical_AND_expression","inclusive_OR_expression","exclusive_OR_expression",
"AND_expression","equality_expression","relational_expression","shift_expression",
"additive_expression","multiplicative_expression","cast_expression","unary_expression",
"unary_operator","postfix_expression","primary_expression","argument_expression_list",
"argument_expression_list_opt","constant","string","identifier","identifier_opt",
"expression_opt","web_statement"
};


int Tree_Init()
{
/*
Pre : None
Post : Initializes tree module by creating the root node and the stack to hold
		 the nodes at bottom-up parse.
*/

	g_Tree_RootNode = Tree_CreateNode(NULL);
	g_Tree_NodeStack = (ParseNodeStack *) calloc(1, sizeof(ParseNodeStack));

	return 0;
}

int Tree_Deinit()
{
/*
Pre : Tree is created
Post : Calls function to destroy nodes.
*/

	ParseNode *node = NULL;
	if(g_Tree_RootNode)
		Tree_DestroyNode(g_Tree_RootNode);

	/*if(g_Tree_NodeStack)
	{
		while((node = ParseNodeStack_Pop(g_Tree_NodeStack))!=NULL)
			Tree_DestroyNode(node);
		free(g_Tree_NodeStack);
	}*/


	return 0;
}

ParseNode *Tree_CreateNode()
{
/*
Pre : None
Post : Creates a node
*/

	ParseNode *node = NULL;

	node = (ParseNode *) calloc(1, sizeof(ParseNode));
	return node;
}

int Tree_DestroyNode(ParseNode *node)
{
/*
Pre : Node exists
Post : Destroys the node and its child nodes along with their attributes.
*/

	int i;
	//ParseNode *parent = NULL;
	ParseNode *child = NULL;
	//ParseNode *first_child = NULL;
	ParseNode *next_sibling = NULL;
	TreeAttribute *attrib = NULL, *next_attrib = NULL;

	if(node==NULL)
		return -1;

	/*if(node->parent)
	{
		child = node->parent->first_child;
		while(child)
		{
			if(child==node)
				break;
			else
				child = child->next_sibling;
		}
		if(child->prev_sibling)
			child->prev_sibling->next_sibling = child->next_sibling;
		if(child->next_sibling)
			child->next_sibling->prev_sibling = child->prev_sibling;

		node->parent->num_of_child--;
	}*/

	child = node->first_child;
	while(child)
	{
		next_sibling = child->next_sibling;
		Tree_DestroyNode(child);
		child = next_sibling;
	}

#ifdef DEBUG
	printf("Deleting node : Type=%d, ID=%d", node->type, node->terminal_nonterminal);
	if(node->type==NODE_NONTERMINAL)
		printf(", nonterminal=%s", yynonterminalname[node->terminal_nonterminal-1]);
	printf("\n");
#endif

	attrib = node->attribute;
	while(attrib)
	{
		next_attrib = attrib->next;

#ifdef DEBUG
		printf("Attrib name: %s, ", attrib->attrib_name);
		if(strcmp(attrib->attrib_name, ATTRIB_DATA_TYPE)==0)
			printf("value = %d\n", (int) attrib->value);
		else
			printf("value = %d\n", (int) attrib->value);

		fflush(stdout);
#endif

		if(attrib->attrib_freeable)
			free(attrib->attrib_name);

		if(attrib->value_freeable && attrib->value)
		{
			if(attrib->value_freeable==ATTRIBUTE_FREE_CONTENT_VALUE && attrib->free_func)
				(*attrib->free_func)((void *) attrib->value);
			else
				free((void *)attrib->value);
		}

		free(attrib);

		attrib = next_attrib;
	}

	if((node->alloc_bytes > 0) && node->value)
		free((void *) node->value);

	free(node);

	return 0;
}

int Tree_AddChild(ParseNode *parent, ParseNode *new_child)
{
/*
Pre : Two nodes are supplied
Post : Second node is the child of the first node
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

int Tree_AddChildAtFirst(ParseNode *parent, ParseNode *new_child)
{
/*
Pre : Two nodes are supplied
Post : Second node is the child of the first node
*/

	if(!parent->first_child)
	{
		parent->first_child = new_child;
		parent->last_child = new_child;
	}
	else
	{
		parent->first_child->prev_sibling = new_child;
		new_child->next_sibling = parent->first_child;
	}
	parent->first_child =  new_child;
	new_child->parent = parent;
	parent->num_of_child++;

	return 0;
}

int Tree_SetNodeValue(ParseNode *node, int nonterminal, int rule_in_nonterminal, int terminal_nonterminal, int type, LONGPARAM value, int value_len)
{
/*
Pre : Node as well as all the information (nonterminal, rule no, type, value, value length supplied
Post : Sets the above information in the node. Allocating memory if necessary to hold the values
*/

	int alloc_bytes;

	//alloc_bytes = value_len;
	if(value_len==-1 && ((char *) value)!=NULL)
	{
		alloc_bytes = strlen((char *) value) + 1;
		value_len = strlen((char *) value);
	}
	else
		alloc_bytes = 0;

	if(alloc_bytes > 0)
	{
		node->value = (LONGPARAM) calloc(1, alloc_bytes);
		memcpy((void *) node->value, (void *) value, value_len);
	}
	else if(value_len!=-1)
		node->value = (LONGPARAM) value;
	else
		node->value = NULL;

	node->nonterminal = nonterminal;
	node->rule_in_nonterminal = rule_in_nonterminal;
	node->terminal_nonterminal = terminal_nonterminal;
	node->type = type;
	node->value_len = value_len;
	node->alloc_bytes = alloc_bytes;

	return 0;
}

/*static const char * const yyterminalname[] = {
"CONSTANT_INTEGER","CONSTANT_FLOATING","CONSTANT_CHAR","CONSTANT_STRING","IDENTIFIER",
"KW_BREAK","KW_CHAR","KW_CONTINUE","KW_DO","KW_DOUBLE","KW_ELSE","KW_ENUM","KW_FLOAT",
"KW_FOR","KW_GOTO","KW_IF","KW_INT","KW_LONG","KW_RETURN","KW_SHORT","KW_SIZEOF",
"KW_STRUCT","KW_TYPEDEF","KW_VOID","KW_WHILE","PLUSPLUS","MINUSMINUS","SHL","SHR",
"EQ","NE","GE","LE","STRUCTREF","LOGICALAND","LOGICALOR","ASSIGNMENT_MUL","ASSIGNMENT_DIV",
"ASSIGNMENT_PERCENT","ASSIGNMENT_PLUS","ASSIGNMENT_MINUS","ASSIGNMENT_SHL","ASSIGNMENT_SHR",
"ASSIGNMENT_AND","ASSIGNMENT_XOR","ASSIGNMENT_OR","';'","'{'","'}'","','","'='",
"'('","')'","'['","']'","'*'","':'","'?'","'|'","'^'","'&'","'<'","'>'","'+'",
"'-'","'/'","'%'","'~'","'!'","'.'"
};
*/

int ParseNodeStack_Push(ParseNodeStack *stack, ParseNode *node)
{
/*
Pre : A node is to be pushed on the stack
Post : Node is pushed onto the stack
*/

	ParseNodeStackElem *stack_elem = NULL;

	stack_elem = (ParseNodeStackElem *) calloc(1, sizeof(ParseNodeStackElem));
	stack_elem->node = node;
	if(stack->first==NULL)
	{
		stack_elem->prev = NULL;
		stack->first = stack_elem;
	}
	else
		stack_elem->prev = stack->top;

	stack_elem->next = NULL;
	if(stack->top)
		stack->top->next = stack_elem;
	stack->top = stack_elem;

	/*if(stack_elem->node->type==NODE_NONTERMINAL)
	{
		printf("PUSH : nonterminal=%s, ID=%d", yynonterminalname[stack_elem->node->nonterminal-1], stack_elem->node->terminal_nonterminal);
	}
	else
	{
		printf("PUSH : terminal=%d", stack_elem->node->terminal_nonterminal);
		if(stack_elem->node->terminal_nonterminal==2)
			printf(" nonterminal=%s, ID=%d", yynonterminalname[stack_elem->node->nonterminal-1], stack_elem->node->terminal_nonterminal);
	}

	//if(stack_elem->node->type==NODE_TERMINAL && (stack_elem->node->terminal_nonterminal==CONSTANT_STRING || stack_elem->node->terminal_nonterminal==IDENTIFIER))
	if(stack_elem->node->type==NODE_TERMINAL && stack_elem->node->value)
			printf(" value=%s", (char *)stack_elem->node->value);

	printf("\n");*/
	return 0;
}

ParseNode *ParseNodeStack_Pop(ParseNodeStack *stack)
{
/*
Pre : Stack may contain one or more elements
Post : Pops off the topmost node from the stack
*/

	ParseNode *ret_node = NULL;
	ParseNodeStackElem *top_elem = NULL;

	if(stack->top==NULL)
		return NULL;

	ret_node = stack->top->node;
	top_elem = stack->top->prev;

	free(stack->top);
	stack->top = top_elem;

	/*if(ret_node->type==NODE_NONTERMINAL)
	{
		printf("POP : nonterminal=%s, ID=%d", yynonterminalname[ret_node->nonterminal-1], ret_node->terminal_nonterminal);
	}
	else
	{
		printf("POP : terminal=%d", ret_node->terminal_nonterminal);
		if(ret_node->terminal_nonterminal==IDENTIFIER)
			printf(" identifier=%s", (char *) ret_node->value);
	}

	printf("\n");*/

	return ret_node;
}

int MAKE_TREE(int nonterminal, int num_of_child, int rule)
{
/*
Pre : Nodes exist at the stack
Post : Pops the nodes. Creates a new node and make the popped nodes the children
of the newly created node. Finally push the created node into the stack.
*/

	ParseNode *node = NULL, *child_node = NULL;

	node = Tree_CreateNode();
	Tree_SetNodeValue(node, nonterminal, rule, nonterminal, NODE_NONTERMINAL, NULL, 0);
	while(num_of_child)
	{
		child_node = ParseNodeStack_Pop(g_Tree_NodeStack);
		Tree_AddChildAtFirst(node, child_node);
		num_of_child--;
	}
	ParseNodeStack_Push(g_Tree_NodeStack, node);

	return 0;
}

int MAKE_PUSH_NODE(int nonterminal, int terminal_nonterminal, LONGPARAM value, int value_len)
{
/*
Pre : node information is supplied
Post : Create a node, sets its values and then push the node into the stack.
*/

	ParseNode *node = Tree_CreateNode();
	Tree_SetNodeValue(node, nonterminal, 0, terminal_nonterminal, NODE_TERMINAL, value, value_len);
	/*if(type==NODE_NONTERMINAL)
	{
		ParseNode *child_node;
		while((g_Tree_NodeStack->top) && ((child_node=g_Tree_NodeStack->top->node)!=NULL))
		{
			if(child_node->nonterminal!=terminal_nonterminal)
				break;

			ParseNodeStack_Pop(g_Tree_NodeStack);
			Tree_AddChildAtFirst(node, child_node);
		}
	}*/
	ParseNodeStack_Push(g_Tree_NodeStack, node);
}

#define YYTABIDX 78
int g_Tree_Tab = 0;

int Tree_Print(ParseNode *node)
{
/*
Pre : Tree existed
Post : Given a node, prints the node along with its child nodes.
*/

	int i;
	ParseNode *child = NULL;
	if(node==NULL)
		return 0;
	for(i=0;i<g_Tree_Tab;i++)
		printf("\t");
	g_Tree_Tab++;
	if(node->type==NODE_NONTERMINAL)
		printf("%s\n", yynonterminalname[node->terminal_nonterminal-1]);
	else
		printf("%d\n", node->terminal_nonterminal);
	child = node->first_child;
	while(child)
	{
		Tree_Print(child);
		child = child->next_sibling;
	}
	g_Tree_Tab--;
}

TreeAttribute *Tree_AttachAttribute(ParseNode *node, char *attrib_name, LONGPARAM value, int value_len, int attrib_freeable, int value_freeable)
{
/*
Pre : Attribute name, value etc. is given for a node
Post : TreeAttribute object is created, sets the attribute information supplied
and attach the attribute object to the node.
*/

	TreeAttribute *attrib = NULL;

	if(value==0)
		return 0;

	attrib = (TreeAttribute *) calloc(1, sizeof(TreeAttribute));

	attrib->attrib_freeable = attrib_freeable;
	if(attrib_freeable)
	{
		attrib->attrib_name = (char *) malloc(strlen(attrib_name)+1);
		strcpy(attrib->attrib_name, attrib_name);
	}
	else
		attrib->attrib_name = attrib_name;

	attrib->value_freeable = value_freeable;
	if(value_freeable==1)
	{
		if(value_len > 0)
		{
			attrib->value = (LONGPARAM) malloc(value_len + 1);
			memcpy(attrib->value, value, value_len);
		}
		//printf("######Tree_AttachAttribute : %s\n", (char *) attrib->value);
	}
	else if(value_freeable==ATTRIBUTE_FREE_CONTENT_VALUE)
	{
		attrib->value = value;
	}
	else
	{
		attrib->value = value;
		//printf("######Tree_AttachAttribute : %s=%d\n", attrib->attrib_name, (int) attrib->value);
	}

	attrib->value_len = value_len;
	attrib->node = node;
	attrib->next = node->attribute;
	node->attribute = attrib;


	return attrib;
}

int Tree_UpdateAttributeValue(ParseNode *node, char *attrib_name, LONGPARAM value, int value_len, int attrib_freeable, int value_freeable)
{
/*
Pre : Attribute object may present
Post : If attribute object is present for given attribute name, then the attribute
is updated, otherwise new attribute is created for the given node.
*/

	TreeAttribute *attrib = NULL;

	attrib = node->attribute;
	while(attrib)
	{
		if(strcmp(attrib->attrib_name, attrib_name)==0)
			break;
		attrib = attrib->next;
	}

	if(attrib)
		TreeAttribute_UpdateValue(attrib, value, value_len, value_freeable);
	else
		attrib = Tree_AttachAttribute(node, attrib_name, value, value_len, attrib_freeable, value_freeable);

	return 0;
}

int TreeAttribute_UpdateValue(TreeAttribute *attribute, LONGPARAM value, int value_len, int value_freeable)
{
/*
Pre : TreeAttribute object exists.
Post : Attribute value is updated. The old value is freed if the value is freeable.
*/

	if(attribute->value_freeable && attribute->value)
	{
		if(attribute->value_freeable==ATTRIBUTE_FREE_CONTENT_VALUE && attribute->free_func)
			(*attribute->free_func)((void *) attribute->value);
		else
			free((void *)attribute->value);
	}

	attribute->value_freeable = value_freeable;
	attribute->value_len = value_len;
	if(value_freeable)
	{
		if(value_len > 0)
		{
			attribute->value = (LONGPARAM) malloc(value_len + 1);
			memcpy(attribute->value, value, value_len);
		}
	}
	else
		attribute->value = value;

	return 0;
}

int TreeAttribute_SetFreeFunc(TreeAttribute *attribute, TreeAttributeFreeFuncType free_func)
{
/*
Pre : None
Post : Sets free function for a given attribute
*/

	attribute->free_func = free_func;
	return 0;
}

LONGPARAM Tree_GetAttributeValue(ParseNode *node, char *attrib_name)
{
/*
Pre : Attribute may present
Post : If attribute is present then return the attribute value
*/

	TreeAttribute *attrib = NULL;

	attrib = node->attribute;
	while(attrib)
	{
		if(strcmp(attrib->attrib_name, attrib_name)==0)
			break;
		attrib = attrib->next;
	}

	if(attrib)
	{
		if(attrib->value_freeable==1)
			return *((LONGPARAM *) attrib->value);
		else
			return attrib->value;
	}
	else
		return NULL;
}

ParseNode *Tree_QueryFirstNodeDown(ParseNode *node, int nonterminal)
{
/*
Pre : A node associated with the given nonterminal should exists
Post : Returns the node associated with given nonterminal if exists
*/

	Queue *queue, *child_queue;
	ParseNode *child, *current_node;

	queue = Queue_Create();
	Queue_InsertAtFront(&queue, (void *) node);

	do
	{
		current_node = (ParseNode *) Queue_RemoveFromFront(&queue);
		if(current_node && current_node->type==NODE_NONTERMINAL)
		{
			if(current_node->terminal_nonterminal!=nonterminal)
			{
				child = current_node->first_child;
				child_queue = Queue_Create();
				while(child)
				{
					//if(child->type == NODE_NONTERMINAL)
					Queue_Append(&child_queue, (void *) child);
					child = child->next_sibling;
				}
				Queue_InsertQueueAtFront(&queue, child_queue);
			}
			else
				break;
		}
	} while(current_node);

	Queue_Destroy(&queue);

	return current_node;
}

/*void Tree_QueryNextNode_Initialize(QueryNextNodeType *query_next_node)
{
	memset((void *) query_next_node, '\0', sizeof(QueryNextNodeType));
}

void Tree_QueryNextNode_SetNode(QueryNextNodeType *query_next_node, ParseNode *node)
{
	query
}*/

ParseNode *Tree_QueryNextSiblingNodeDown(ParseNode *node, int nonterminal)
{
/*
Pre : First call was Tree_QueryFirstNodeDown. Subsequent calling of this function
will return the next node associated with the given nonterminal
Post : Returns the next node whose nonterminal value is given nonterminal
*/

	ParseNode *search_node = node->parent->next_sibling;

	return Tree_QueryFirstNodeDown(search_node, nonterminal);
}

Queue *Queue_Create()
{
/*
Pre : None
Post : Pseudo function to create a queue. Actual queue will be created when an
element will be enqueued.
*/


	/*Queue *queue;

	queue = (Queue *) calloc(1, sizeof(Queue));
	return queue;*/
	return NULL;
}

void Queue_Destroy(Queue **queue)
{
/*
Pre : Queue to be destroyed is supplied.
Post : Destroys the queue
*/

	while(Queue_RemoveFromFront(queue));
}

void Queue_InsertQueueAtFront(Queue **queue, Queue *new_queue)
{
	Queue *process_queue = new_queue;

	if(new_queue==NULL)
		return;

	while(process_queue->next && (process_queue = process_queue->next));
	process_queue->next = *queue;
	*queue = new_queue;
}

void Queue_Append(Queue **queue, void *elem)
{
/*
Pre : Queue and the element to be queued is supplied
Post : Element is queued at the end of the queue
*/

	Queue *new_queue, *process_queue;

	new_queue = (Queue *) calloc(1, sizeof(Queue));
	new_queue->elem = elem;
	if(*queue)
	{
		process_queue = *queue;
		while(process_queue->next && (process_queue = process_queue->next));
		process_queue->next = new_queue;
	}
	else
	{
		*queue = new_queue;
	}
	//printf("Queue_Append : %d, %x\n", ((ParseNode *) elem)->terminal_nonterminal, new_queue->next);
}

void Queue_InsertAtFront(Queue **queue, void *elem)
{
/*
Pre : Queue and the element to be queued is supplied
Post : Element is queued at the front of the queue
*/
	Queue *new_queue;

	/*{
		ParseNode *node = (ParseNode *) elem;
		printf("Queue_InsertAtFront : %d\n", node->terminal_nonterminal);
	}*/

	if(*queue==NULL)
	{
		new_queue = (Queue *) calloc(1, sizeof(Queue));
		new_queue->next = NULL;
	}
	/*else if((*queue)->elem==NULL)
	{
		new_queue = *queue;
	}*/
	else
	{
		new_queue = (Queue *) calloc(1, sizeof(Queue));
		new_queue->next = *queue;
	}
	new_queue->elem = elem;
	*queue = new_queue;
}

void *Queue_RemoveFromFront(Queue **queue)
{
/*
Pre : Queue to be dequeued is supplied
Post : Dequeues the front element of the queue and returns
*/
	Queue *remove_queue;
	void *elem;

	if(queue==NULL || *queue==NULL)
		return NULL;

	remove_queue = *queue;
	elem = remove_queue->elem;
	*queue = remove_queue->next;
	free(remove_queue);

	//printf("Queue_RemoveFromFront : %d\n", ((ParseNode *) elem)->terminal_nonterminal);

	return elem;
}

