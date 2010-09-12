void PointerOperation()
{
	char c;	
	char *p;
	char **pp;
	char ***ppp;

	c = 65;
	p = &c;
	++*p;
	
	Response_Write("Value of c :", c, "<BR>");
	
	pp = &p;
	ppp = &pp;
	
	***ppp = 70;
	
	Response_Write("New value of c :", c, "<BR>");

}

<HTML>
<BODY>
<B><U>Pointer operation example</U></B><BR>
<CALLFUNCTION>PointerOperation</CALLFUNCTION>
</BODY>
</HTML>
