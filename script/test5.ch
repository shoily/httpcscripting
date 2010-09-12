void WhileExample()
{
	int x, y;

	x = 1;
	y = 5;

	while(x < y)
	{
		int result;

		result = x + y;

		Response_Write("x = ", x, " y = ", y, " x + y = ", result);
		Response_Write("<BR>");

		x = x + 1;
	}
	
	Response_Write("while example <BR>");
}

<HTML>
<BODY>
<CALLFUNCTION>WhileExample</CALLFUNCTION>
</BODY>
</HTML>
