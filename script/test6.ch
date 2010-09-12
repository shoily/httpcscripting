void OneBitCount()
{
	int x;
	int b;
	
	x = Request_QueryString("x");
	
	Response_Write("x:", x, "<BR>");
	
	b = 0;
	while(x != 0)
	{
		if(x & 1)
			b++;
		x >>= 1;
	}
	
	Response_Write("One bit count :", b);
}
<HTML>
<BODY>
<B>Bit counting example. Number of one bit will be counted for <U>x</U></B><BR>
<CALLFUNCTION>OneBitCount</CALLFUNCTION>
</BODY>
</HTML>
