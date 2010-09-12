/*
File Name : htmlprocessor.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Process CHTML files, extract C code, ask the compiler
module to compile this C code, gets html chunk, gets function name to be called,
call interpreter to interpret and execute the intermediate code associate with
this function, calls HTTPResponse function to write back response to web client.
*/

#include "htmlprocessor.h"
#include "common.h"
#include "tree.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


HTMLProcessor *HTMLProcessor_Create()
{
/*
Pre : None
Post : Creates HTMLProcessor object and returns it to the caller
*/
	HTMLProcessor *processor;

	processor = (HTMLProcessor *) calloc(1, sizeof(HTMLProcessor));

	return processor;
}

int HTMLProcessor_Destroy(HTMLProcessor *processor)
{
/*
Pre : HTMLProcessor object exists
Post : Destroys HTMLProcessor object
*/
	free(processor);

	return 0;
}

/*----------- Input/output stream for the lexical analyzer --------------------*/
extern FILE *yyin, *yyout;

int HTMLProcessor_Process(HTMLProcessor *processor, HTTPRequest *request, HTTPResponse *response)
{
/*
Pre : HTMLProcessor, HTTPRequest and HTTPResponse object is created first
Post : Process CHTML files, extract C code, ask the compiler
module to compile this C code, gets html chunk, gets function name to be called,
call interpreter to interpret and execute the intermediate code associate with
this function, calls HTTPResponse function to write back response to web client.
*/
	FILE *fp = NULL;
	char filename[100], *script_file_name = "test1.ch";
	int file_suffix;
	int ret;
	char *c_code, *html_chunk, *function_name;
	HTTPRequest_Field *query_field;
	int scrip_file_found = 0;

	//randomize();

	if(processor->filename[0]!='\0')
	{
		if(HTTPRequest_ReadFile(request, processor->filename)==0)
			scrip_file_found = 1;
	}
	else
	{
		script_file_name = getenv("SCRIPT_NAME");
		if(script_file_name &&
			*script_file_name!='\0' &&
			strlen(script_file_name) > 3 &&
			strcmpi(&script_file_name[strlen(script_file_name)-2], "ch")==0)
		{
			if(HTTPRequest_ReadFile(request, getenv("PATH_TRANSLATED"))==0)
				scrip_file_found = 1;
		}
		else
		{
			query_field = request->query_field;

			while(query_field)
			{
				if(query_field->name && strcmp(query_field->name, "SCRIPT_NAME")==0)
				{
					if(query_field->value && HTTPRequest_ReadFile(request, query_field->value)==0)
						scrip_file_found = 1;
					break;
				}
				query_field = query_field->next;
			}

			if(scrip_file_found==0)
			{
				HTTPResponse_HTMLText(response, "<HTML><BODY>");
				HTTPResponse_HTMLText(response, "<B>SCRIPT FILE NAME IS NOT PRESENT</B>");
				HTTPResponse_HTMLText(response, "</HTML></BODY>");
				HTTPResponse_Flush(response);

				return -1;
			}
		}
	}

	if(scrip_file_found==0)
	{
		HTTPResponse_HTMLText(response, "<HTML><BODY>");
		HTTPResponse_HTMLText(response, "<B>SCRIPT FILE COULD NOT BE FOUND</B>");
		HTTPResponse_HTMLText(response, "</HTML></BODY>");
		HTTPResponse_Flush(response);

		return -1;
	}

	processor->request = request;
	processor->next_chunk_ptr = processor->request->text;

	sprintf(filename, "TMP1.c");
	/*do
	{
		if(fp) fclose(fp);
		//file_suffix = random(99999);
		file_suffix = 1;
		sprintf(filename, "TMP%d.c", file_suffix);
		fp = fopen(filename, "r");
	} while(fp);*/

	fp = fopen(filename, "w+");

	ret = HTMLProcessor_FindCCode(processor, &c_code);
	if(ret==1)
	{
		fclose(fp);
		HTTPResponse_HTMLText(response, processor->request->text);
		HTTPResponse_Flush(response);
		return 0;
	}
	else if(ret==-1)
	{
		fclose(fp);
		HTTPResponse_HTMLText(response, "Error at the tag of code");
		HTTPResponse_Flush(response);
		return -1;
	}

	fwrite(c_code, 1, strlen(c_code), fp);
	fflush(fp);
	free(c_code);
	fseek(fp, 0L, SEEK_SET);

	yyin = fp;
	yyout = stdout;

	Initialize();
	yyparse();
	g_Tree_RootNode = ParseNodeStack_Pop(g_Tree_NodeStack);

	if(request->print_tree)
		Tree_Print(g_Tree_RootNode);

	TypeCheck_PopulateType(g_Tree_RootNode);
	IntrmdtCode_PopulateCode(g_Tree_RootNode);
	IntrmdtCode_GenerateLineNumber();
	IntrmdtCode_Backpatch();

	if(request->print_intermediatecode)
		IntrmdtCode_Print(g_Tree_RootNode);
	if(request->print_intermediatecodeverbose)
		IntrmdtCode_PrintVerbose(g_Tree_RootNode);
	if(request->print_symboltable)
		SymbolTable_Print(g_SymbolTable_RootTable);

	Interpreter_SetHTTPObject(request, response);

	do
	{
		HTMLProcessor_GetNextHTMLChunk(processor, &html_chunk);
		if(html_chunk)
		{
			HTTPResponse_HTMLText(response, html_chunk);
			free(html_chunk);
		}
		HTMLProcessor_GetNextFunctionToCall(processor, &function_name);
		if(function_name)
		{
			Interpreter_Start(function_name);
			free(function_name);
		}
	} while(html_chunk || function_name);

	HTTPResponse_Flush(response);

	Deinitialize();

	fclose(fp);  
	remove(filename);
}

int HTMLProcessor_FindCCode(HTMLProcessor *processor, char **c_code)
{
/*
Pre : C code in CHTML file may be present
Post : Returns the extracted C code from the file
*/
	char *code_start, *code_end;
	int code_length;

	code_start = processor->request->text;
	if(code_start==NULL)
	{
		*c_code = NULL;
		return 1;
	}

	code_end = strstr(code_start, "<HTML>");
	if(code_end == NULL)
	{
		code_end = strstr(code_start, "<html>");
		{
			if(code_end == NULL)
			{
				*c_code = NULL;
				return -1;
			}
		}
	}

	code_length = (int) (code_end - code_start);
	*c_code = (char *) malloc(code_length + 1);
	strncpy(*c_code, code_start, code_length);
	(*c_code)[code_length] = '\0';
	processor->next_chunk_ptr = code_end;

	return 0;
}

int HTMLProcessor_GetNextHTMLChunk(HTMLProcessor *processor, char **chunk)
{
/*
Pre : HTML chunk should be present
Post : Returns HTML chunk upto the next <CALLFUNCTION> tag
*/
	char *p;
	int ret, chunk_len;

	*chunk = NULL;

	if(processor->next_chunk_ptr==NULL)
		return 0;

	p = strstr(processor->next_chunk_ptr, "<CALLFUNCTION>");
	if(p)
		chunk_len = (int) (p - processor->next_chunk_ptr);
	else
		chunk_len = strlen(processor->next_chunk_ptr);

	if(chunk_len==0)
		return 0;

	*chunk = (char *) malloc(chunk_len + 1);
	strncpy(*chunk, processor->next_chunk_ptr, chunk_len);
	(*chunk)[chunk_len] = '\0';

	if(p)
		processor->next_chunk_ptr = p;
	else
		processor->next_chunk_ptr = NULL;

	return 0;
}

int HTMLProcessor_GetNextFunctionToCall(HTMLProcessor *processor, char **function_name)
{
/*
Pre : <CALLFUNCTION> tag may be present
Post : Returns the function name from the next <CALLFUNCTION> tag if there is any
*/
	char *p;
	int ret, chunk_len;

	*function_name = NULL;

	if(processor->next_chunk_ptr==NULL)
		return 0;

	p = strstr(processor->next_chunk_ptr, "<CALLFUNCTION>");
	if(p==NULL)
		return 0;

	processor->next_chunk_ptr = p + strlen("<CALLFUNCTION>");
	p = strstr(processor->next_chunk_ptr, "</CALLFUNCTION>");
	if(p==NULL)
		return -1;

	chunk_len = (int) (p - processor->next_chunk_ptr);
	*function_name = (char *) malloc(chunk_len + 1);
	strncpy(*function_name, processor->next_chunk_ptr, chunk_len);
	(*function_name)[chunk_len] = '\0';

	processor->next_chunk_ptr = p + strlen("</CALLFUNCTION>");

	return 0;
}

int HTMLProcessor_SetFileName(HTMLProcessor *processor, char *filename)
{
/*
Pre : Debugging function
Post : Debugging function
*/
	if(filename==NULL)
		return -1;
	strcpy(processor->filename, filename);

	return 0;
}

