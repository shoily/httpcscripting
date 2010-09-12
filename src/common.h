/*
File Name : common.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains data structure and defines used more than one modules
*/

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define COMPILER_YES	1		// Yes (true)
#define COMPILER_NO	0		// No (false)

#define LONGPARAM		unsigned long int

//Defines for nonterminals
#define NONTERMINAL_NONE											0
#define NONTERMINAL_translation_unit							1
#define NONTERMINAL_external_declaration                 2
#define NONTERMINAL_function_definition                  3
#define NONTERMINAL_declaration                          4
#define NONTERMINAL_declaration_list                     5
#define NONTERMINAL_declaration_specifiers_opt           6
#define NONTERMINAL_declaration_specifiers               7
#define NONTERMINAL_type_specifier                       8
#define NONTERMINAL_struct_or_union_specifier            9
#define NONTERMINAL_struct_or_union                      10
#define NONTERMINAL_struct_declaration_list              11
#define NONTERMINAL_init_declarator_list                 12
#define NONTERMINAL_init_declarator_list_opt             13
#define NONTERMINAL_init_declarator                      14
#define NONTERMINAL_struct_declaration                   15
#define NONTERMINAL_specifier_qualifier_list             16
#define NONTERMINAL_specifier_qualifier_list_opt         17
#define NONTERMINAL_struct_declarator_list               18
#define NONTERMINAL_struct_declarator                    19
#define NONTERMINAL_declarator                           20
#define NONTERMINAL_direct_declarator                    21
#define NONTERMINAL_pointer                              22
#define NONTERMINAL_pointer_opt                          23
#define NONTERMINAL_parameter_type_list                  24
#define NONTERMINAL_parameter_type_list_opt              25
#define NONTERMINAL_parameter_list                       26
#define NONTERMINAL_parameter_declaration                27
#define NONTERMINAL_identifier_list                      28
#define NONTERMINAL_identifier_list_opt                  29
#define NONTERMINAL_initializer                          30
#define NONTERMINAL_initializer_list                     31
#define NONTERMINAL_type_name                            32
#define NONTERMINAL_abstract_declarator                  33
#define NONTERMINAL_abstract_declarator_opt              34
#define NONTERMINAL_direct_abstract_declarator           35
#define NONTERMINAL_direct_abstract_declarator_opt       36
#define NONTERMINAL_statement                            37
#define NONTERMINAL_labeled_statement                    38
#define NONTERMINAL_expression_statement                 39
#define NONTERMINAL_compound_statement                   40
#define NONTERMINAL_declaration_list_opt                 41
#define NONTERMINAL_statement_list_opt                   42
#define NONTERMINAL_statement_list                       43
#define NONTERMINAL_selection_statement                  44
#define NONTERMINAL_iteration_statement                  45
#define NONTERMINAL_jump_statement                       46
#define NONTERMINAL_web_statement                      	75
#define NONTERMINAL_expression                           47
#define NONTERMINAL_assignment_expression                48
#define NONTERMINAL_assignment_operator                  49
#define NONTERMINAL_constant_expression                  50
#define NONTERMINAL_constant_expression_opt              51
#define NONTERMINAL_conditional_expression               52
#define NONTERMINAL_logical_OR_expression                53
#define NONTERMINAL_logical_AND_expression               54
#define NONTERMINAL_inclusive_OR_expression              55
#define NONTERMINAL_exclusive_OR_expression              56
#define NONTERMINAL_AND_expression                       57
#define NONTERMINAL_equality_expression                  58
#define NONTERMINAL_relational_expression                59
#define NONTERMINAL_shift_expression                     60
#define NONTERMINAL_additive_expression                  61
#define NONTERMINAL_multiplicative_expression            62
#define NONTERMINAL_cast_expression                      63
#define NONTERMINAL_unary_expression                     64
#define NONTERMINAL_unary_operator                       65
#define NONTERMINAL_postfix_expression                   66
#define NONTERMINAL_primary_expression                   67
#define NONTERMINAL_argument_expression_list             68
#define NONTERMINAL_argument_expression_list_opt         69
#define NONTERMINAL_constant                             70
#define NONTERMINAL_string                               71
#define NONTERMINAL_identifier                           72
#define NONTERMINAL_identifier_opt                       73
#define NONTERMINAL_expression_opt                       74

//Typedefs
typedef int typevar_type;
typedef struct _Type Type;
typedef struct _TypeEntry TypeEntry;

typedef struct _VariableMemoryChain VariableMemoryChain;
typedef struct _VariableMemory VariableMemory;

typedef struct _SymbolTableEntry SymbolTableEntry;
typedef struct _SymbolTable SymbolTable;

typedef struct _ParseNode ParseNode;
typedef struct _TreeAttribute TreeAttribute;

typedef struct _IntrmdtCodeAccessType IntrmdtCodeAccessType;
typedef struct _TypeCheck_Function TypeCheck_Function;

typedef struct _ParamInfo ParamInfo;

typedef struct _HTTPRequest HTTPRequest;
typedef struct _HTTPResponse HTTPResponse;

#endif

