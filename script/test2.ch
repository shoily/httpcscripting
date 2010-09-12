void AddAndPrint()
{
	int x, y;
	int result;

	x = Request_QueryString("x");
	y = Request_QueryString("y");
	result = x + y;
	Response_Write(x, "+", y, "=", result);
}

void PrintHelloWorld()
{
	Response_Write("Hello world!");
}

<HTML>
<BODY>
Simple addition program <BR>
<CALLFUNCTION>AddAndPrint</CALLFUNCTION>
Hello world by the C code will be printed just after this line <BR>
<CALLFUNCTION>PrintHelloWorld</CALLFUNCTION>
</BODY>
</HTML>
