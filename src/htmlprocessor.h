/*
File Name : htmlprocessor.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Contains method to process .ch file.
*/

#ifndef _HTML_PROCESSOR_H
#define _HTML_PROCESSOR_H

#include "http.h"

typedef struct _HTMLProcessor HTMLProcessor;

struct _HTMLProcessor
{
	HTTPRequest *request;
	char *next_chunk_ptr;
	char filename[100];
};

HTMLProcessor *HTMLProcessor_Create();
int HTMLProcessor_Destroy(HTMLProcessor *processor);

int HTMLProcessor_Process(HTMLProcessor *processor, HTTPRequest *request, HTTPResponse *response);
int HTMLProcessor_GetNextHTMLChunk(HTMLProcessor *processor, char **chunk);
int HTMLProcessor_GetNextFunctionToCall(HTMLProcessor *processor, char **function_name);
int HTMLProcessor_SetFileName(HTMLProcessor *processor, char *filename);

#endif

