/*
File Name : chtml.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Contains initialization/deinitialization and main function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "symtab.h"
#include "intrmdtcode.h"
#include "interpreter.h"
#include "http.h"
#include "htmlprocessor.h"

int Initialize()
{
/*
Pre : None
Post : Initializes the compiler modules (Tree, Symbol table, TypeCheck, Intermediate code)
*/
	Tree_Init();
	SymbolTable_Init();
	TypeCheck_Init();
	IntrmdtCode_Init();
	return 0;
}

int Deinitialize()
{
/*
Pre :	All the compiler modules are initialized
Post : Deinitializes all the compiler modules
*/

	IntrmdtCode_Deinit();
	TypeCheck_Deinit();
	SymbolTable_Deinit();
	Tree_Deinit();
	return 0;
}

/*---------------------------------- MAIN FUNCTION ---------------------------*/


int main(int argc, char **argv)
{
	FILE *fp = NULL;
	HTTPRequest *request;
	HTTPResponse *response;
	HTMLProcessor *html_processor;

	request = HTTPRequest_Create();		// Creates the HTTPRequest object
	response = HTTPResponse_Create();	// Creates the HTTPResponse object
	html_processor = HTMLProcessor_Create();	// Creates the HTMLProcessor object

	if(argc > 1)
	{
		int i;

		for(i = 1; i < argc; i++)
			if(strcmp(argv[i], "-t") == 0) {
				request->print_tree = 1;
			}
			else if(strcmp(argv[i], "-s") == 0) {
				request->print_symboltable = 1;
			}
			else if(strcmp(argv[i], "-i") == 0) {
				request->print_intermediatecode = 1;
			}
			else if(strcmp(argv[i], "-v") == 0) {
				request->print_intermediatecodeverbose = 1;
			}
			else if(strcmp(argv[i], "-q") == 0) {
				if(argc > i) {
					HTTPRequest_SetQueryString(request, argv[i+1]);	//Sets the query string received from command line
					HTTPRequest_FillQueryField(request);			// Updates internal data structure
					i++;
				}
			}
			else if(strcmp(argv[i], "-f") == 0) {
				if(argc > i) {
					HTMLProcessor_SetFileName(html_processor, argv[i+1]);
					i++;
				}
			}
	}
	else
	{
		HTTPRequest_SetQueryString(request, getenv("QUERY_STRING"));	//Sets the query string received from web server
		HTTPRequest_FillQueryField(request);							// Updates internal data structure
	}

	HTMLProcessor_Process(html_processor, request, response);	// Process the CHTML file

	HTMLProcessor_Destroy(html_processor);		// Destroys the HTMLProcessor object
	HTTPResponse_Destroy(response);				// Destroys the HTTPResponse object
	HTTPRequest_Destroy(request);					// Destroys the HTTPRequest object

	return 0;
}

/*
Function yyerror is required for machine generated parser to be compiled
*/
int yyerror(char *s)
{
	return 0;
}

