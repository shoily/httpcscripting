void MathemeticalOp()
{
	int x, y;
	int result_add, result_sub, result_mul, result_div, result_mod;
	int result_shl, result_shr;
	int result_gt, result_lt, result_eq, result_ne;
	int result_bitand, result_bitor, result_bitxor;
	
	x = 4;
	y = 2;

	result_add = x + y;
	result_sub = x - y;
	result_mul = x * y;
	result_div = x / y;
	result_mod = x % y;
	result_shl = x << y;
	result_shr = x >> y;

	result_gt = x > y;
	result_lt = x < y;
	result_eq = x == y;
	result_ne = x != y;	
	
	result_bitand = x & y;
	result_bitor = x | y;
	result_bitxor = x ^ y;
	
	Response_Write("x = ", x, " y = " , y, "<BR>");
	Response_Write("Addition : ", result_add, "<BR>");
	Response_Write("Subtraction : ", result_sub, "<BR>");
	Response_Write("Multiplication : ", result_mul, "<BR>");
	Response_Write("Division : ", result_div, "<BR>");
	Response_Write("Modulus: ", result_mod, "<BR>");

	Response_Write("Shift-left : ", result_shl, "<BR>");
	Response_Write("Shift-right : ", result_shr, "<BR>");
	Response_Write("Grater than : ", result_gt, "<BR>");
	Response_Write("Less than : ", result_lt, "<BR>");
	Response_Write("Equal : ", result_eq, "<BR>");
	Response_Write("Not equal : ", result_ne, "<BR>");
	

	Response_Write("Bitwise AND : ", result_bitand, "<BR>");
	Response_Write("Bitwise OR : ", result_bitor, "<BR>");
	Response_Write("Bitwise XOR : ", result_bitxor, "<BR>");
}

<HTML>
<BODY>
<CALLFUNCTION>MathemeticalOp</CALLFUNCTION>
</BODY>
</HTML>
