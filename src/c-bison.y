%{
#include "tree.h"	// Includes tree.h file to get prototype of two functions - MAKE_PUSH_NODE and MAKE_TREE
extern char *yytext;	// yytext is declared in the lex.yy.cc module. It holds the token.
float yyfval;		// Holds the floating point constant
%}


%token CONSTANT_INTEGER, CONSTANT_FLOATING, CONSTANT_CHAR, CONSTANT_STRING
%token IDENTIFIER
%token KW_BREAK, KW_BREAK, KW_CHAR, KW_CONTINUE, KW_DO, KW_DOUBLE, KW_ELSE, KW_ENUM
%token KW_FLOAT, KW_FOR, KW_GOTO, KW_IF, KW_INT, KW_LONG, KW_RETURN, KW_SHORT, KW_SIZEOF
%token KW_STRUCT, KW_TYPEDEF, KW_VOID, KW_WHILE
%token PLUSPLUS, MINUSMINUS, SHL, SHR, EQ, NE, GE, LE, STRUCTREF, LOGICALAND, LOGICALOR
%token ASSIGNMENT_MUL, ASSIGNMENT_DIV, ASSIGNMENT_PERCENT, ASSIGNMENT_PLUS, ASSIGNMENT_MINUS
%token ASSIGNMENT_SHL, ASSIGNMENT_SHR, ASSIGNMENT_AND, ASSIGNMENT_XOR, ASSIGNMENT_OR
%token KW_REQUEST_QUERYSTRING, KW_RESPONSE_WRITE

%%

translation_unit	:	translation_unit external_declaration	{MAKE_TREE(NONTERMINAL_translation_unit, 2, 1);}
						|	external_declaration			            {MAKE_TREE(NONTERMINAL_translation_unit, 1, 2);}
						;

external_declaration	:	function_definition			{MAKE_TREE(NONTERMINAL_external_declaration, 1, 1);}
							|	declaration						{MAKE_TREE(NONTERMINAL_external_declaration, 1, 2);}
							;

function_definition	:	declaration_specifiers declarator compound_statement	{MAKE_TREE(NONTERMINAL_function_definition, 3, 1);}
							;


declaration				:	declaration_specifiers init_declarator_list ';'	{MAKE_TREE(NONTERMINAL_declaration, 2, 1);}
							;

declaration_list		:	declaration_list declaration		{MAKE_TREE(NONTERMINAL_declaration_list, 2, 1);}
							|	declaration                      {MAKE_TREE(NONTERMINAL_declaration_list, 1, 2);}
							;
/*
declaration_specifiers_opt	:	declaration_specifiers declaration_specifiers_opt		{MAKE_TREE(NONTERMINAL_, 1);}
									|                                                        {MAKE_TREE(NONTERMINAL_);}
									;
*/
declaration_specifiers	:	type_specifier		{MAKE_TREE(NONTERMINAL_declaration_specifiers, 1, 1);}
								;

type_specifier					:	KW_VOID		{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_VOID, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 1);}
									|	KW_CHAR		{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_CHAR, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 2);}
//									|	KW_SHORT		{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_SHORT, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 3);}
									|	KW_INT		{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_INT, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 4);}
//									|	KW_LONG		{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_LONG, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 5);}
									|	KW_FLOAT		{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_FLOAT, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 6);}
									|	KW_DOUBLE	{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_DOUBLE, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 7);}
									|	struct_or_union_specifier	{MAKE_TREE(NONTERMINAL_type_specifier, 1, 8);}
//									|	typedef_name
									;

struct_or_union_specifier	:	struct_or_union identifier_opt '{' struct_declaration_list '}'		{MAKE_TREE(NONTERMINAL_struct_or_union_specifier, 3, 1);}
									|	struct_or_union identifier                                        {MAKE_TREE(NONTERMINAL_struct_or_union_specifier, 2, 2);}
									;

struct_or_union				:	KW_STRUCT		{MAKE_PUSH_NODE(NONTERMINAL_struct_or_union, KW_STRUCT, NULL, 0); MAKE_TREE(NONTERMINAL_struct_or_union, 1, 1);}
									;

struct_declaration_list		:	struct_declaration									{MAKE_TREE(NONTERMINAL_struct_declaration_list, 1, 1);}
									|	struct_declaration_list struct_declaration   {MAKE_TREE(NONTERMINAL_struct_declaration_list, 2, 2);}
									;

init_declarator_list			:	init_declarator										{MAKE_TREE(NONTERMINAL_init_declarator_list, 1, 1);}
									|	init_declarator_list ',' init_declarator     {MAKE_TREE(NONTERMINAL_init_declarator_list, 2, 2);}
									;
/*
init_declarator_list_opt	:	init_declarator_list				{MAKE_TREE(NONTERMINAL_);}
									|                                {MAKE_TREE(NONTERMINAL_);}
									;
*/
init_declarator				:	declarator							{MAKE_TREE(NONTERMINAL_init_declarator, 1, 1);}
//									|	declarator '=' {MAKE_PUSH_NODE(NONTERMINAL_init_declarator, (LONGPARAM) '=', NULL, 0);} initializer		{MAKE_TREE(NONTERMINAL_init_declarator, 3, 2);}
									;

struct_declaration			:	specifier_qualifier_list struct_declarator_list ';'	{MAKE_TREE(NONTERMINAL_struct_declaration, 2, 1);}
									;

specifier_qualifier_list	:	type_specifier		{MAKE_TREE(NONTERMINAL_specifier_qualifier_list, 1, 2);}
									;

specifier_qualifier_list_opt	:	specifier_qualifier_list								{MAKE_TREE(NONTERMINAL_specifier_qualifier_list_opt, 1, 1);}
										|                                                  {MAKE_TREE(NONTERMINAL_specifier_qualifier_list_opt, 1, 2);}
										;

struct_declarator_list			:	struct_declarator											{MAKE_TREE(NONTERMINAL_struct_declarator_list, 1, 1);}
										|	struct_declarator_list ',' struct_declarator    {MAKE_TREE(NONTERMINAL_struct_declarator_list, 2, 2);}
										;

struct_declarator					:	declarator	{MAKE_TREE(NONTERMINAL_struct_declarator, 1, 1);}
										;

/*
enum_specifier						:	KW_ENUM identifier_opt '{' enumerator_list '}'
										|	KW_ENUM identifier
										;

enumerator_list					:	enumerator
										|	enumerator_list ',' enumerator

enumerator							:	identifier
//										|	identifier '=' constant_expression
										;
*/
declarator							:	pointer_opt direct_declarator		{MAKE_TREE(NONTERMINAL_declarator, 2, 1);}
										;

direct_declarator					:	'(' {MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) '(', NULL, 0);} declarator ')'		{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) ')', NULL, 0); MAKE_TREE(NONTERMINAL_direct_declarator, 3, 1);}
										|	direct_declarator '[' {MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) '[', NULL, 0);} constant_expression ']'		{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) ']', NULL, 0); MAKE_TREE(NONTERMINAL_direct_declarator, 4, 2);}
										|	direct_declarator '(' {MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) '(', NULL, 0);} parameter_type_list_opt ')'  {MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) ')', NULL, 0); MAKE_TREE(NONTERMINAL_direct_declarator, 4, 3);}
										|	identifier					{MAKE_TREE(NONTERMINAL_direct_declarator, 1, 4);}
//										|	direct_declarator '(' identifier_list_opt ')' {MAKE_TREE(NONTERMINAL_);}
										;

pointer								:	'*' {MAKE_PUSH_NODE(NONTERMINAL_pointer, (LONGPARAM) '*', NULL, 0);} pointer_opt	{MAKE_TREE(NONTERMINAL_pointer, 2, 1);}
										;

pointer_opt							:	pointer				{MAKE_TREE(NONTERMINAL_pointer_opt, 1, 1);}
										|                    {MAKE_TREE(NONTERMINAL_pointer_opt, 0, 2);}
										;

parameter_type_list				:	parameter_list		{MAKE_TREE(NONTERMINAL_parameter_type_list, 1, 1);}
//										|	parameter_list ',' '.' '.' '.'
										;

parameter_type_list_opt			:	parameter_type_list		{MAKE_TREE(NONTERMINAL_parameter_type_list_opt, 1, 1);}
										|                          {MAKE_TREE(NONTERMINAL_parameter_type_list_opt, 0, 2);}
										;

parameter_list						:	parameter_declaration		{MAKE_TREE(NONTERMINAL_parameter_list, 1, 1);}
										|	parameter_list ',' parameter_declaration	{MAKE_TREE(NONTERMINAL_parameter_list, 2, 2);}
										;

parameter_declaration			:	declaration_specifiers declarator		{MAKE_TREE(NONTERMINAL_parameter_declaration, 2, 1);}
//										|	declaration_specifiers abstract_declarator_opt
										;
/*
identifier_list					:	identifier
										|	identifier_list ',' identifier
										;

identifier_list_opt				:	identifier_list
										|
										;
*/
initializer							:	assignment_expression					{MAKE_TREE(NONTERMINAL_initializer, 1, 1);}
/*										|	'{' initializer_list '}'
										|	'{' initializer_list ',' '}'	*/
										;

initializer_list					:	initializer									{MAKE_TREE(NONTERMINAL_initializer_list, 1, 1);}
										|	initializer_list ',' initializer		{MAKE_TREE(NONTERMINAL_initializer_list, 2, 2);}
										;


type_name							:	specifier_qualifier_list /*abstract_declarator_opt*/		{MAKE_TREE(NONTERMINAL_type_name, 1, 1);}
										;

/*
abstract_declarator				:	pointer_opt direct_abstract_declarator
										;

abstract_declarator_opt			:	abstract_declarator
										|
										;

direct_abstract_declarator		:	'(' abstract_declarator ')'
										|	direct_abstract_declarator_opt '[' constant_expression ']'
										|	direct_abstract_declarator_opt '(' parameter_type_list_opt ')'
										;

direct_abstract_declarator_opt	:	direct_abstract_declarator
											|
											;
*/
/*
typedef_name						:	identifier
										;

*/

statement				:	expression_statement		{MAKE_TREE(NONTERMINAL_statement, 1, 1);}
							|	labeled_statement       {MAKE_TREE(NONTERMINAL_statement, 1, 2);}
							|	compound_statement      {MAKE_TREE(NONTERMINAL_statement, 1, 3);}
							|	selection_statement     {MAKE_TREE(NONTERMINAL_statement, 1, 4);}
							|	iteration_statement     {MAKE_TREE(NONTERMINAL_statement, 1, 5);}
							|	jump_statement          {MAKE_TREE(NONTERMINAL_statement, 1, 6);}
							|	web_statement         	{MAKE_TREE(NONTERMINAL_statement, 1, 7);}
							;

labeled_statement		:	identifier ':' {MAKE_PUSH_NODE(NONTERMINAL_labeled_statement, (LONGPARAM) ':', NULL, 0);} statement	{MAKE_TREE(NONTERMINAL_labeled_statement, 3, 1);}
							;

expression_statement	:	expression_opt ';'            							{MAKE_TREE(NONTERMINAL_expression_statement, 1, 1);}
							;


compound_statement	:	'{' declaration_list_opt statement_list_opt '}'		{MAKE_TREE(NONTERMINAL_compound_statement, 2, 1);}
							;

declaration_list_opt	:	declaration_list				{MAKE_TREE(NONTERMINAL_declaration_list_opt, 1, 1);}
							|                             {MAKE_TREE(NONTERMINAL_declaration_list_opt, 0, 2);}
							;

statement_list_opt	:	statement_list					{MAKE_TREE(NONTERMINAL_statement_list_opt, 1, 1);}
							|                             {MAKE_TREE(NONTERMINAL_statement_list_opt, 0, 2);}
							;

statement_list			:	statement_list statement	{MAKE_TREE(NONTERMINAL_statement_list, 2, 1);}
							|	statement                  {MAKE_TREE(NONTERMINAL_statement_list, 1, 2);}
							;


selection_statement	:	KW_IF '(' expression ')' statement							{MAKE_TREE(NONTERMINAL_selection_statement, 2, 1);}
							|	KW_IF '(' expression ')' statement KW_ELSE {MAKE_PUSH_NODE(NONTERMINAL_selection_statement, KW_ELSE, NULL, 0);} statement  {MAKE_TREE(NONTERMINAL_selection_statement, 4, 2);}
							;

iteration_statement	:	KW_WHILE {MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_WHILE, NULL, 0);} '(' expression ')' statement               {MAKE_TREE(NONTERMINAL_iteration_statement, 3, 1);}
							|	KW_DO {MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_DO, NULL, 0);} statement KW_WHILE {MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_WHILE, NULL, 0);} '(' expression ')' ';'     {MAKE_TREE(NONTERMINAL_iteration_statement, 4, 2);}
							|	KW_FOR {MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_FOR, NULL, 0);} '(' expression_opt ';' expression_opt ';' expression_opt ')' statement {MAKE_TREE(NONTERMINAL_iteration_statement, 5, 3);}
							;

jump_statement			:	KW_GOTO {MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_GOTO, NULL, 0);} identifier ';'				{MAKE_TREE(NONTERMINAL_jump_statement, 2, 1);}
							|	KW_CONTINUE ';'                  {MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_CONTINUE, NULL, 0); MAKE_TREE(NONTERMINAL_jump_statement, 1, 2);}
							|	KW_BREAK ';'                     {MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_BREAK, NULL, 0); MAKE_TREE(NONTERMINAL_jump_statement, 1, 3);}
							|	KW_RETURN {MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_RETURN, NULL, 0);} expression_opt ';'	   {MAKE_TREE(NONTERMINAL_jump_statement, 2, 4);}
							;

web_statement			:	KW_RESPONSE_WRITE '(' argument_expression_list_opt ')' ';'			{MAKE_TREE(NONTERMINAL_web_statement, 1, 1);}
							;

expression				:	assignment_expression						{MAKE_TREE(NONTERMINAL_expression, 1, 1);}
							|	expression ',' assignment_expression	{MAKE_TREE(NONTERMINAL_expression, 2, 2);}
							;

assignment_expression	: unary_expression assignment_operator assignment_expression	{MAKE_TREE(NONTERMINAL_assignment_expression, 3, 1);}
								|	conditional_expression		                                 {MAKE_TREE(NONTERMINAL_assignment_expression, 1, 2);}
								;

assignment_operator	:	'='						{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) '=', NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 1);}
							|	ASSIGNMENT_MUL			{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_MUL, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 2);}
							|	ASSIGNMENT_DIV			{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_DIV, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 3);}
							|	ASSIGNMENT_PERCENT	{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_PERCENT, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 4);}
							|	ASSIGNMENT_PLUS		{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_PLUS, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 5);}
							|	ASSIGNMENT_MINUS		{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_MINUS, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 6);}
							|	ASSIGNMENT_SHL			{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_SHL, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 7);}
							|	ASSIGNMENT_SHR			{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_SHR, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 8);}
							|	ASSIGNMENT_AND       {MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_AND, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 9);}
							|	ASSIGNMENT_XOR       {MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_XOR, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 10);}
							|	ASSIGNMENT_OR        {MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_OR, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 11);}
							;

constant_expression		:	conditional_expression			{MAKE_TREE(NONTERMINAL_constant_expression, 1, 1);}
								;

constant_expression_opt	:	constant_expression				{MAKE_TREE(NONTERMINAL_constant_expression_opt, 1, 1);}
								|                                {MAKE_TREE(NONTERMINAL_constant_expression_opt, 0, 2);}
								;

conditional_expression	:	logical_OR_expression															{MAKE_TREE(NONTERMINAL_conditional_expression, 1, 1);}
//								|	logical_OR_expression '?' {MAKE_PUSH_NODE(NONTERMINAL_conditional_expression, (LONGPARAM) '?', NULL, 0);} expression ':' {MAKE_PUSH_NODE(NONTERMINAL_conditional_expression, (LONGPARAM) ':', NULL, 0);} conditional_expression	{MAKE_TREE(NONTERMINAL_conditional_expression, 5, 2);}
								;

logical_OR_expression	:	logical_AND_expression												{MAKE_TREE(NONTERMINAL_logical_OR_expression, 1, 1);}
								|	logical_OR_expression LOGICALOR {MAKE_PUSH_NODE(NONTERMINAL_logical_OR_expression, (LONGPARAM) LOGICALOR, NULL, 0);} logical_AND_expression	{MAKE_TREE(NONTERMINAL_logical_OR_expression, 3, 2);}
								;

logical_AND_expression	:	inclusive_OR_expression													{MAKE_TREE(NONTERMINAL_logical_AND_expression, 1, 1);}
								|	logical_AND_expression LOGICALAND {MAKE_PUSH_NODE(NONTERMINAL_logical_AND_expression, (LONGPARAM) LOGICALAND, NULL, 0); } inclusive_OR_expression   {MAKE_TREE(NONTERMINAL_logical_AND_expression, 3, 2);}
								;

inclusive_OR_expression	:	exclusive_OR_expression										   {MAKE_TREE(NONTERMINAL_inclusive_OR_expression, 1, 1);}
								|	inclusive_OR_expression '|' {MAKE_PUSH_NODE(NONTERMINAL_inclusive_OR_expression, (LONGPARAM) '|', NULL, 0);} exclusive_OR_expression	{MAKE_TREE(NONTERMINAL_inclusive_OR_expression, 3, 2);}
								;

exclusive_OR_expression	:	AND_expression													{MAKE_TREE(NONTERMINAL_exclusive_OR_expression, 1, 1);}
								|	exclusive_OR_expression '^' {MAKE_PUSH_NODE(NONTERMINAL_exclusive_OR_expression, (LONGPARAM) '^', NULL, 0);} AND_expression			{MAKE_TREE(NONTERMINAL_exclusive_OR_expression, 3, 2);}
								;

AND_expression				:	equality_expression											{MAKE_TREE(NONTERMINAL_AND_expression, 1, 1);}
								|	AND_expression '&' {MAKE_PUSH_NODE(NONTERMINAL_AND_expression, (LONGPARAM) '&', NULL, 0);} equality_expression             { MAKE_TREE(NONTERMINAL_AND_expression, 3, 2);}
								;

equality_expression		:	relational_expression										{MAKE_TREE(NONTERMINAL_equality_expression, 1, 1);}
								|	equality_expression EQ {MAKE_PUSH_NODE(NONTERMINAL_equality_expression, (LONGPARAM) EQ, NULL, 0);} relational_expression       {MAKE_TREE(NONTERMINAL_equality_expression, 3, 2);}
								|	equality_expression NE {MAKE_PUSH_NODE(NONTERMINAL_equality_expression, (LONGPARAM) NE, NULL, 0);} relational_expression       {MAKE_TREE(NONTERMINAL_equality_expression, 3, 3);}
								;

relational_expression	:	shift_expression												{MAKE_TREE(NONTERMINAL_relational_expression, 1, 1);}
								|	relational_expression '<' {MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) '<', NULL, 0);} shift_expression         {MAKE_TREE(NONTERMINAL_relational_expression, 3, 2);}
								|	relational_expression '>' {MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) '>', NULL, 0);} shift_expression         {MAKE_TREE(NONTERMINAL_relational_expression, 3, 3);}
								|	relational_expression LE {MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) LE, NULL, 0);} shift_expression				{MAKE_TREE(NONTERMINAL_relational_expression, 3, 4);}
								|	relational_expression GE {MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) GE, NULL, 0);} shift_expression				{MAKE_TREE(NONTERMINAL_relational_expression, 3, 5);}
								;

shift_expression			:	additive_expression											{MAKE_TREE(NONTERMINAL_shift_expression, 1, 1);}
								|	shift_expression SHL {MAKE_PUSH_NODE(NONTERMINAL_shift_expression, (LONGPARAM) SHL, NULL, 0);} additive_expression		     {MAKE_TREE(NONTERMINAL_shift_expression, 3, 2);}
								|	shift_expression SHR {MAKE_PUSH_NODE(NONTERMINAL_shift_expression, (LONGPARAM) SHR, NULL, 0);} additive_expression           {MAKE_TREE(NONTERMINAL_shift_expression, 3, 3);}
								;

additive_expression		:	multiplicative_expression                         {MAKE_TREE(NONTERMINAL_additive_expression, 1, 1);}
								|	additive_expression '+' {MAKE_PUSH_NODE(NONTERMINAL_additive_expression, (LONGPARAM) '+', NULL, 0);} multiplicative_expression {MAKE_TREE(NONTERMINAL_additive_expression, 3, 2);}
								|	additive_expression '-' {MAKE_PUSH_NODE(NONTERMINAL_additive_expression, (LONGPARAM) '-', NULL, 0);} multiplicative_expression {MAKE_TREE(NONTERMINAL_additive_expression, 3, 3);}
								;

multiplicative_expression	:  cast_expression											{MAKE_TREE(NONTERMINAL_multiplicative_expression, 1, 1);}
									| multiplicative_expression '*' {MAKE_PUSH_NODE(NONTERMINAL_multiplicative_expression, (LONGPARAM) '*', NULL, 0);} cast_expression	  {MAKE_TREE(NONTERMINAL_multiplicative_expression, 3, 2);}
									| multiplicative_expression '/' {MAKE_PUSH_NODE(NONTERMINAL_multiplicative_expression, (LONGPARAM) '/', NULL, 0);} cast_expression    {MAKE_TREE(NONTERMINAL_multiplicative_expression, 3, 3);}
									| multiplicative_expression '%' {MAKE_PUSH_NODE(NONTERMINAL_multiplicative_expression, (LONGPARAM) '%', NULL, 0);} cast_expression    {MAKE_TREE(NONTERMINAL_multiplicative_expression, 3, 4);}
									;

cast_expression				:	unary_expression		{MAKE_TREE(NONTERMINAL_cast_expression, 1, 1);}
									|	'(' type_name ')' cast_expression 	{MAKE_TREE(NONTERMINAL_cast_expression, 2, 2);}
									;



unary_expression				:	postfix_expression	{MAKE_TREE(NONTERMINAL_unary_expression, 1, 1);}
									|	PLUSPLUS {MAKE_PUSH_NODE(NONTERMINAL_unary_expression, (LONGPARAM) PLUSPLUS, NULL, 0);} unary_expression	{MAKE_TREE(NONTERMINAL_unary_expression, 2, 2);}
									|	MINUSMINUS {MAKE_PUSH_NODE(NONTERMINAL_unary_expression, (LONGPARAM)MINUSMINUS, NULL, 0);} unary_expression	{MAKE_TREE(NONTERMINAL_unary_expression, 2, 3);}
									|	unary_operator cast_expression {MAKE_TREE(NONTERMINAL_unary_expression, 2, 4);}
									|	KW_SIZEOF {MAKE_PUSH_NODE(NONTERMINAL_unary_expression, KW_SIZEOF, NULL, 0);} primary_expression	{MAKE_TREE(NONTERMINAL_unary_expression, 2, 5);}
									|	KW_SIZEOF '(' {MAKE_PUSH_NODE(NONTERMINAL_unary_expression, KW_SIZEOF, NULL, 0);} type_name ')'	{MAKE_TREE(NONTERMINAL_unary_expression, 2, 6);}
									;


unary_operator					:	'&'	{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '&', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 1);}
									|	'*'	{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '*', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 2);}
									|	'+'	{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '+', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 3);}
									|	'-'	{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '-', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 4);}
									|	'~'	{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '~', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 5);}
									|	'!'	{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '!', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 6);}
									;


postfix_expression			:	primary_expression	{MAKE_TREE(NONTERMINAL_postfix_expression, 1, 1);}
									|	postfix_expression  '[' {MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) '[', NULL, 0);} expression ']' {MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) ']', NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 4, 2);}
									|	postfix_expression '(' {MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) '(', NULL, 0);} argument_expression_list_opt ')'	{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) ')', NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 4, 3);}
									|	postfix_expression '.' {MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) '.', NULL, 0);} identifier	{MAKE_TREE(NONTERMINAL_postfix_expression, 3, 4);}
									|	postfix_expression STRUCTREF {MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) STRUCTREF, NULL, 0);} identifier	{MAKE_TREE(NONTERMINAL_postfix_expression, 3, 5);}
									|	postfix_expression PLUSPLUS	{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) PLUSPLUS, NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 2, 6);}
									|	postfix_expression MINUSMINUS	{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) MINUSMINUS, NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 2, 7);}
									|	KW_REQUEST_QUERYSTRING {MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, KW_REQUEST_QUERYSTRING, (LONGPARAM) yytext, -1);} '(' string ')' {MAKE_TREE(NONTERMINAL_postfix_expression, 2, 8);}
									;

primary_expression			:	identifier		{MAKE_TREE(NONTERMINAL_primary_expression, 1, 1);}
									|	constant			{MAKE_TREE(NONTERMINAL_primary_expression, 1, 2);}
									|	string			{MAKE_TREE(NONTERMINAL_primary_expression, 1, 3);}
									|	'(' expression ')'	{MAKE_TREE(NONTERMINAL_primary_expression, 1, 4);}
									;

argument_expression_list	:	assignment_expression            {MAKE_TREE(NONTERMINAL_argument_expression_list, 1, 1);}
									|	argument_expression_list ',' assignment_expression	{MAKE_TREE(NONTERMINAL_argument_expression_list, 2, 2);}
									;

argument_expression_list_opt	:	argument_expression_list		{MAKE_TREE(NONTERMINAL_argument_expression_list_opt, 1, 1);}
										|		                           {MAKE_TREE(NONTERMINAL_argument_expression_list_opt, 0, 2);}
										;

constant								:	CONSTANT_INTEGER		{MAKE_PUSH_NODE(NONTERMINAL_constant, CONSTANT_INTEGER, (LONGPARAM) yylval, sizeof(int)); MAKE_TREE(NONTERMINAL_constant, 1, 1);}
										|	CONSTANT_CHAR			{MAKE_PUSH_NODE(NONTERMINAL_constant, CONSTANT_CHAR, (LONGPARAM) yylval, sizeof(char)); MAKE_TREE(NONTERMINAL_constant, 1, 2);}
										|	CONSTANT_FLOATING		{MAKE_PUSH_NODE(NONTERMINAL_constant, CONSTANT_FLOATING, (LONGPARAM) yyfval, sizeof(float)); MAKE_TREE(NONTERMINAL_constant, 1, 3);}
										;

string								:	CONSTANT_STRING		{MAKE_PUSH_NODE(NONTERMINAL_string, CONSTANT_STRING, (LONGPARAM) yytext, -1); MAKE_TREE(NONTERMINAL_string, 1, 1);}
										;

identifier						:	IDENTIFIER			{MAKE_PUSH_NODE(NONTERMINAL_identifier, IDENTIFIER, (LONGPARAM) yytext, -1); MAKE_TREE(NONTERMINAL_identifier, 1, 1);}
									;


identifier_opt					:	identifier		{MAKE_TREE(NONTERMINAL_identifier_opt, 1, 1);}
									|						{MAKE_TREE(NONTERMINAL_identifier_opt, 0, 2);}
									;

expression_opt					:	expression	{MAKE_TREE(NONTERMINAL_expression_opt, 1, 1);}
									|					{MAKE_TREE(NONTERMINAL_expression_opt, 0, 2);}
									;



%%
