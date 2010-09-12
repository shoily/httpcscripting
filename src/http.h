/*
File Name : HTTP.h
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Description : Contains data structure and defines for HTTP reqeust and response
*/

#ifndef _HTTP_H
#define _HTTP_H

#include "common.h"

//Data structure for HTTP request field
typedef struct _HTTPRequest_Field HTTPRequest_Field;

struct _HTTPRequest_Field
{
	char *name;						// Name
	char *value;					// Value
	HTTPRequest_Field *next;	// Pointer to the next field
};

//Data structure for the HTTP request
struct _HTTPRequest
{
	char *query_string;					// Query string
	HTTPRequest_Field *query_field;	// Pointer to the query field
	char *text;								// Pointer to the whole CHTML data
	int print_tree;					// Print parse tree
	int print_symboltable;			// Print symbol table
	int print_intermediatecode;		// Print intermediate code
	int print_intermediatecodeverbose;		// Print intermediate code verbose
};

//Function declaration for HTTP request
HTTPRequest *HTTPRequest_Create();
int HTTPRequest_Destroy(HTTPRequest *request_header);

int HTTPRequest_ReadFile(HTTPRequest *request_header, char *filename);
int HTTPRequest_SetQueryString(HTTPRequest *request_header, char *query_string);
int HTTPRequest_AddQueryField(HTTPRequest *request_header, char *name, char *value);
int HTTPRequest_FillQueryField(HTTPRequest *request_header);

//Data structure for HTTP response
struct _HTTPResponse
{
	int content_length;	// Content-Length
	char *HTML_text;		// Pointer to the buffered output
};

//Function declaration for HTTP response
HTTPResponse *HTTPResponse_Create();
int HTTPResponse_Destroy(HTTPResponse *response_header);

int HTTPResponse_HTMLText(HTTPResponse *response_header, char *text);
int HTTPResponse_Flush(HTTPResponse *response_header);

#endif

