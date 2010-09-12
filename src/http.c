/*
File Name : HTTP.c
Author : Shoily Obaidur Rahman
Student Number : 980296684
OS : MS-Windows
Language : Microsoft Visual C++ 6.0
Program Description : Handles HTTP query string and formats output for HTTP response.
*/

#include "HTTP.h"
#include <stdio.h>
#include <stdlib.h>

HTTPRequest *HTTPRequest_Create()
{
/*
Pre : None
Post : Creates HTTP request object and returns it to caller
*/

	HTTPRequest *request_header;

	request_header = (HTTPRequest *) calloc(1, sizeof(HTTPRequest));

	return request_header;
}

int HTTPRequest_Destroy(HTTPRequest *request_header)
{
/*
Pre : HTTP request object is supplied
Post : HTTP request object destroyed
*/

	HTTPRequest_Field *current_query_field, *remove_query_field;

	current_query_field = request_header->query_field;

	while(current_query_field)
	{
		remove_query_field = current_query_field;
		current_query_field = current_query_field->next;
		if(remove_query_field->name) free(remove_query_field->name);
		if(remove_query_field->value) free(remove_query_field->value);
		free(remove_query_field);
	}

	if(request_header->text)
		free(request_header->text);

	if(request_header->query_string)
		free(request_header->query_string);

	free(request_header);

	return 0;
}

int HTTPRequest_SetQueryString(HTTPRequest *request_header, char *query_string)
{
/*
Pre : Request object and query string
Post : Copy the request object in the internal buffer
*/

	if(query_string == NULL)
		return -1;

	request_header->query_string = malloc(strlen(query_string)+1);
	strcpy(request_header->query_string, query_string);

	return 0;
}

int HTTPRequest_FillQueryField(HTTPRequest *request_header)
{
/*
Pre : Call to the HTTPRequest_SetQueryString must be prior to this call of function
Post : Fills the query name and value pair in a list form.
*/

	char *name, *value;
	int name_len, value_len;
	char *p;
	HTTPRequest_Field *query_field;

	if(request_header->query_string == NULL)
		return 0;

	name = request_header->query_string;
	if(name && *name=='\"')
		name++;

	while(name && *name!='\0')
	{
		p = strchr(name, '=');
		if(p)
		{
			name_len = (int) (p - name);

			query_field = (HTTPRequest_Field *) malloc(sizeof(HTTPRequest_Field));
			query_field->name = (char *) malloc(name_len+1);
			strncpy(query_field->name, name, name_len);
			query_field->name[name_len] = '\0';

			p++;
			value = p;
			p = strchr(value, '&');

			if(p==NULL)
				p = strchr(value, '\0');

			if(p!=NULL)
			{
				value_len = (int) (p - value);
				if(*p=='&')
					name = p + 1;
				else
					name = p;
				query_field->value = (char *) malloc(value_len+1);
				strncpy(query_field->value, value, value_len);
				query_field->value[value_len] = '\0';
			}
			else
				name = p;

			query_field->next = request_header->query_field;
			request_header->query_field = query_field;
		}
	}

	return 0;
}

int HTTPRequest_AddQueryField(HTTPRequest *request_header, char *name, char *value)
{
/*
Pre : Helper function to add query field
Post : Query field is added in the internal list
*/

	HTTPRequest_Field *query_field;

	if(request_header->query_string==NULL)
		return -1;

	query_field = (HTTPRequest_Field *) calloc(1, sizeof(HTTPRequest_Field));

	query_field->name = (char *) calloc(1, strlen(name)+1);
	query_field->value = (char *) calloc(1, strlen(value)+1);

	strcpy(query_field->name, name);
	strcpy(query_field->value, value);

	query_field->next = request_header->query_field;
	request_header->query_field = query_field;

	return 0;
}

int HTTPRequest_ReadFile(HTTPRequest *request_header, char *filename)
{
/*
Pre : File name to be read is supplied
Post : Reads the chtml file and stores it in the internal buffer of request object
*/

	FILE *fp;
	int file_length, bread;
	char *p, c;

	fp = fopen(filename, "r");
	if(fp==NULL)
	{
		printf("Error opening file : %s\n", filename);
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	file_length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	request_header->text = (char *) malloc(file_length + 1);

	p = request_header->text;
	while((c = fgetc(fp))!=EOF)
		*p++ = c;
	*p = '\0';

	fclose(fp);

	return 0;
}

HTTPResponse *HTTPResponse_Create()
{
/*
Pre : None
Post : Creates HTTP response object and returns
*/

	HTTPResponse *response_header;

	response_header = (HTTPResponse *) calloc(1, sizeof(HTTPResponse));

	return response_header;
}

int HTTPResponse_Destroy(HTTPResponse *response_header)
{
/*
Pre : HTTP response to be deleted is supplied
Post : Deletes HTTP response object
*/

	if(response_header->HTML_text)
		free(response_header->HTML_text);

	free(response_header);
}

int HTTPResponse_HTMLText(HTTPResponse *response_header, char *text)
{
/*
Pre : Buffers the output
Post : Output is saved in internal buffer
*/

	char *p;

	response_header->HTML_text = realloc(response_header->HTML_text, response_header->content_length + strlen(text) + 1);
	p = response_header->HTML_text + response_header->content_length;
	strcpy(p, text);
	response_header->content_length += strlen(text);

	return 0;
}

int HTTPResponse_Flush(HTTPResponse *response_header)
{
/*
Pre : Flushes the buffered data to the stdout
Post : Writes the HTTP response to the stdout
*/

	printf("Content-Type: text/html\n");
	printf("Content-Length: %d\n", response_header->content_length);
	printf("\n");
	printf("%s", response_header->HTML_text);
	fflush(stdout);
}

