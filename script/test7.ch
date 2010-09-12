void GetBits()
{
	int x, p, n, d;
	int number;
	
	x = Request_QueryString("x");
	p = Request_QueryString("p");
	n = Request_QueryString("n");
	
	Response_Write("x:", x, "p:", p, "n:", n, "<BR>");

	d = 0;
	
	number = (x >> (p+1-n)) & ~(~d << n);
	
	Response_Write("Calculated number :", number);
}

<HTML>
<BODY>
<B>Get <U>n</U> bits from postion <U>p</U> for <U>x</U></B><BR>
<CALLFUNCTION>GetBits</CALLFUNCTION>
</BODY>
</HTML>
