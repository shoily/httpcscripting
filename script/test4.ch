void IfThenExample()
{
	int x, y;

	x = 1;
	y = 2;
	
	Response_Write("if-then example", "<BR> ");
	
	if(x > y)
		Response_Write("x is grater than y", "<BR>");	
}

void IfThenElseExample()
{
	int x, y;

	x = 3;
	y = 2;
	
	Response_Write("if-then-else example", "<BR> ");

	if(x > y)
		Response_Write("x is grater than y", "<BR>");
	else if(x == y)
		Response_Write("x is equal to y", "<BR>");
	else
		Response_Write("x is less than y", "<BR>");

	
}

<HTML>
<BODY>
Now showing if-then example <BR>
<CALLFUNCTION>IfThenExample</CALLFUNCTION>
<BR>
Now showing if-then-else example <BR>
<CALLFUNCTION>IfThenElseExample</CALLFUNCTION>
</BODY>
</HTML>
