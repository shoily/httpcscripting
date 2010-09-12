/*
File Name : interpreter.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains function declaration for interpreter module
*/

#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "symtab.h"
#include "intrmdtcode.h"
#include "runtime.h"

//Function declarations for interpreter
int Interpreter_Start(char *func_name);
void Interpreter_GetSymbolTableEntryValue(SymbolTableEntry *entry, void *buffer, int size);
void Interpreter_Assignment(SymbolTableEntry *lvalue_entry, SymbolTableEntry *rvalue_entry);
ThreeAddressCode *Interpreter_Fetch(IntrmdtCodeAccessType *code_access, IntrmdtCodeHolderType **code_holder, int line_num);
int Interpreter_Execute(RuntimeStorage *storage, ThreeAddressCode *code, int *line_num);
int Interpreter_SetHTTPObject(HTTPRequest *request, HTTPResponse *response);

#endif
