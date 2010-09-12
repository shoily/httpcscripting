
/*  A Bison parser, made from c-bison.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	CONSTANT_INTEGER	258
#define	CONSTANT_FLOATING	259
#define	CONSTANT_CHAR	260
#define	CONSTANT_STRING	261
#define	IDENTIFIER	262
#define	KW_BREAK	263
#define	KW_CHAR	264
#define	KW_CONTINUE	265
#define	KW_DO	266
#define	KW_DOUBLE	267
#define	KW_ELSE	268
#define	KW_ENUM	269
#define	KW_FLOAT	270
#define	KW_FOR	271
#define	KW_GOTO	272
#define	KW_IF	273
#define	KW_INT	274
#define	KW_LONG	275
#define	KW_RETURN	276
#define	KW_SHORT	277
#define	KW_SIZEOF	278
#define	KW_STRUCT	279
#define	KW_TYPEDEF	280
#define	KW_VOID	281
#define	KW_WHILE	282
#define	PLUSPLUS	283
#define	MINUSMINUS	284
#define	SHL	285
#define	SHR	286
#define	EQ	287
#define	NE	288
#define	GE	289
#define	LE	290
#define	STRUCTREF	291
#define	LOGICALAND	292
#define	LOGICALOR	293
#define	ASSIGNMENT_MUL	294
#define	ASSIGNMENT_DIV	295
#define	ASSIGNMENT_PERCENT	296
#define	ASSIGNMENT_PLUS	297
#define	ASSIGNMENT_MINUS	298
#define	ASSIGNMENT_SHL	299
#define	ASSIGNMENT_SHR	300
#define	ASSIGNMENT_AND	301
#define	ASSIGNMENT_XOR	302
#define	ASSIGNMENT_OR	303
#define	KW_REQUEST_QUERYSTRING	304
#define	KW_RESPONSE_WRITE	305

#line 1 "c-bison.y"

#include "tree.h"	// Includes tree.h file to get prototype of two functions - MAKE_PUSH_NODE and MAKE_TREE
extern char *yytext;	// yytext is declared in the lex.yy.cc module. It holds the token.
float yyfval;		// Holds the floating point constant

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		290
#define	YYFLAG		-32768
#define	YYNTBASE	74

#define YYTRANSLATE(x) ((unsigned)(x) <= 305 ? yytranslate[x] : 176)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    72,     2,     2,     2,    70,    64,     2,    55,
    56,    59,    67,    54,    68,    73,    69,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    60,    51,    65,
    61,    66,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    57,     2,    58,    63,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    52,    62,    53,    71,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     5,     7,     9,    13,    17,    20,    22,    24,
    26,    28,    30,    32,    34,    36,    42,    45,    47,    49,
    52,    54,    58,    60,    64,    66,    68,    69,    71,    75,
    77,    80,    81,    86,    87,    93,    94,   100,   102,   103,
   107,   109,   110,   112,   114,   115,   117,   121,   124,   126,
   128,   132,   134,   136,   138,   140,   142,   144,   146,   148,
   149,   154,   157,   162,   164,   165,   167,   168,   171,   173,
   179,   180,   189,   190,   197,   198,   199,   209,   210,   221,
   222,   227,   230,   233,   234,   239,   245,   247,   251,   255,
   257,   259,   261,   263,   265,   267,   269,   271,   273,   275,
   277,   279,   281,   283,   284,   286,   288,   289,   294,   296,
   297,   302,   304,   305,   310,   312,   313,   318,   320,   321,
   326,   328,   329,   334,   335,   340,   342,   343,   348,   349,
   354,   355,   360,   361,   366,   368,   369,   374,   375,   380,
   382,   383,   388,   389,   394,   396,   397,   402,   403,   408,
   409,   414,   416,   421,   423,   424,   428,   429,   433,   436,
   437,   441,   442,   448,   450,   452,   454,   456,   458,   460,
   462,   463,   469,   470,   476,   477,   482,   483,   488,   491,
   494,   495,   501,   503,   505,   507,   511,   513,   517,   519,
   520,   522,   524,   526,   528,   530,   532,   533,   535
};

static const short yyrhs[] = {    74,
    75,     0,    75,     0,    76,     0,    77,     0,    79,    90,
   107,     0,    79,    84,    51,     0,    78,    77,     0,    77,
     0,    80,     0,    26,     0,     9,     0,    19,     0,    15,
     0,    12,     0,    81,     0,    82,   174,    52,    83,    53,
     0,    82,   173,     0,    24,     0,    86,     0,    83,    86,
     0,    85,     0,    84,    54,    85,     0,    90,     0,    87,
    88,    51,     0,    80,     0,    87,     0,     0,    89,     0,
    88,    54,    89,     0,    90,     0,    97,    91,     0,     0,
    55,    92,    90,    56,     0,     0,    91,    57,    93,   125,
    58,     0,     0,    91,    55,    94,    99,    56,     0,   173,
     0,     0,    59,    96,    97,     0,    95,     0,     0,   100,
     0,    98,     0,     0,   101,     0,   100,    54,   101,     0,
    79,    90,     0,   123,     0,     0,     0,     0,    54,     0,
     0,    87,     0,   106,     0,   104,     0,   107,     0,   111,
     0,   113,     0,   118,     0,   121,     0,     0,   173,    60,
   105,   103,     0,   175,    51,     0,    52,   108,   109,    53,
     0,    78,     0,     0,   110,     0,     0,   110,   103,     0,
   103,     0,    18,    55,   122,    56,   103,     0,     0,    18,
    55,   122,    56,   103,    13,   112,   103,     0,     0,    27,
   114,    55,   122,    56,   103,     0,     0,     0,    11,   115,
   103,    27,   116,    55,   122,    56,    51,     0,     0,    16,
   117,    55,   175,    51,   175,    51,   175,    56,   103,     0,
     0,    17,   119,   173,    51,     0,    10,    51,     0,     8,
    51,     0,     0,    21,   120,   175,    51,     0,    50,    55,
   170,    56,    51,     0,   123,     0,   122,    54,   123,     0,
   156,   124,   123,     0,   126,     0,    61,     0,    39,     0,
    40,     0,    41,     0,    42,     0,    43,     0,    44,     0,
    45,     0,    46,     0,    47,     0,    48,     0,   126,     0,
   125,     0,     0,   127,     0,   129,     0,     0,   127,    38,
   128,   129,     0,   131,     0,     0,   129,    37,   130,   131,
     0,   133,     0,     0,   131,    62,   132,   133,     0,   135,
     0,     0,   133,    63,   134,   135,     0,   137,     0,     0,
   135,    64,   136,   137,     0,   140,     0,     0,   137,    32,
   138,   140,     0,     0,   137,    33,   139,   140,     0,   145,
     0,     0,   140,    65,   141,   145,     0,     0,   140,    66,
   142,   145,     0,     0,   140,    35,   143,   145,     0,     0,
   140,    34,   144,   145,     0,   148,     0,     0,   145,    30,
   146,   148,     0,     0,   145,    31,   147,   148,     0,   151,
     0,     0,   148,    67,   149,   151,     0,     0,   148,    68,
   150,   151,     0,   155,     0,     0,   151,    59,   152,   155,
     0,     0,   151,    69,   153,   155,     0,     0,   151,    70,
   154,   155,     0,   156,     0,    55,   102,    56,   155,     0,
   162,     0,     0,    28,   157,   156,     0,     0,    29,   158,
   156,     0,   161,   155,     0,     0,    23,   159,   168,     0,
     0,    23,    55,   160,   102,    56,     0,    64,     0,    59,
     0,    67,     0,    68,     0,    71,     0,    72,     0,   168,
     0,     0,   162,    57,   163,   122,    58,     0,     0,   162,
    55,   164,   170,    56,     0,     0,   162,    73,   165,   173,
     0,     0,   162,    36,   166,   173,     0,   162,    28,     0,
   162,    29,     0,     0,    49,   167,    55,   172,    56,     0,
   173,     0,   171,     0,   172,     0,    55,   122,    56,     0,
   123,     0,   169,    54,   123,     0,   169,     0,     0,     3,
     0,     5,     0,     4,     0,     6,     0,     7,     0,   173,
     0,     0,   122,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    20,    21,    24,    25,    28,    32,    35,    36,    43,    46,
    47,    49,    51,    52,    53,    57,    58,    61,    64,    65,
    68,    69,    76,    80,    83,    86,    87,    90,    91,    94,
   109,   112,   112,   113,   113,   114,   114,   115,   119,   119,
   122,   123,   126,   130,   131,   134,   135,   138,   150,   155,
   156,   160,   186,   187,   188,   189,   190,   191,   192,   195,
   195,   198,   202,   205,   206,   209,   210,   213,   214,   218,
   219,   219,   222,   222,   223,   223,   223,   224,   224,   227,
   227,   228,   229,   230,   230,   233,   236,   237,   240,   241,
   244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
   254,   257,   260,   261,   264,   268,   269,   269,   272,   273,
   273,   276,   277,   277,   280,   281,   281,   284,   285,   285,
   288,   289,   289,   290,   290,   293,   294,   294,   295,   295,
   296,   296,   297,   297,   300,   301,   301,   302,   302,   305,
   306,   306,   307,   307,   310,   311,   311,   312,   312,   313,
   313,   316,   317,   322,   323,   323,   324,   324,   325,   326,
   326,   327,   327,   331,   332,   333,   334,   335,   336,   340,
   341,   341,   342,   342,   343,   343,   344,   344,   345,   346,
   347,   347,   350,   351,   352,   353,   356,   357,   360,   361,
   364,   365,   366,   369,   372,   376,   377,   380,   381
};

static const char * const yytname[] = {   "$","error","$undefined.","CONSTANT_INTEGER",
"CONSTANT_FLOATING","CONSTANT_CHAR","CONSTANT_STRING","IDENTIFIER","KW_BREAK",
"KW_CHAR","KW_CONTINUE","KW_DO","KW_DOUBLE","KW_ELSE","KW_ENUM","KW_FLOAT","KW_FOR",
"KW_GOTO","KW_IF","KW_INT","KW_LONG","KW_RETURN","KW_SHORT","KW_SIZEOF","KW_STRUCT",
"KW_TYPEDEF","KW_VOID","KW_WHILE","PLUSPLUS","MINUSMINUS","SHL","SHR","EQ","NE",
"GE","LE","STRUCTREF","LOGICALAND","LOGICALOR","ASSIGNMENT_MUL","ASSIGNMENT_DIV",
"ASSIGNMENT_PERCENT","ASSIGNMENT_PLUS","ASSIGNMENT_MINUS","ASSIGNMENT_SHL","ASSIGNMENT_SHR",
"ASSIGNMENT_AND","ASSIGNMENT_XOR","ASSIGNMENT_OR","KW_REQUEST_QUERYSTRING","KW_RESPONSE_WRITE",
"';'","'{'","'}'","','","'('","')'","'['","']'","'*'","':'","'='","'|'","'^'",
"'&'","'<'","'>'","'+'","'-'","'/'","'%'","'~'","'!'","'.'","translation_unit",
"external_declaration","function_definition","declaration","declaration_list",
"declaration_specifiers","type_specifier","struct_or_union_specifier","struct_or_union",
"struct_declaration_list","init_declarator_list","init_declarator","struct_declaration",
"specifier_qualifier_list","struct_declarator_list","struct_declarator","declarator",
"direct_declarator","@1","@2","@3","pointer","@4","pointer_opt","parameter_type_list",
"parameter_type_list_opt","parameter_list","parameter_declaration","type_name",
"statement","labeled_statement","@5","expression_statement","compound_statement",
"declaration_list_opt","statement_list_opt","statement_list","selection_statement",
"@6","iteration_statement","@7","@8","@9","@10","jump_statement","@11","@12",
"web_statement","expression","assignment_expression","assignment_operator","constant_expression",
"conditional_expression","logical_OR_expression","@13","logical_AND_expression",
"@14","inclusive_OR_expression","@15","exclusive_OR_expression","@16","AND_expression",
"@17","equality_expression","@18","@19","relational_expression","@20","@21",
"@22","@23","shift_expression","@24","@25","additive_expression","@26","@27",
"multiplicative_expression","@28","@29","@30","cast_expression","unary_expression",
"@31","@32","@33","@34","unary_operator","postfix_expression","@35","@36","@37",
"@38","@39","primary_expression","argument_expression_list","argument_expression_list_opt",
"constant","string","identifier","identifier_opt","expression_opt","string"
};
#endif

static const short yyr1[] = {     0,
    74,    74,    75,    75,    76,    77,    78,    78,    79,    80,
    80,    80,    80,    80,    80,    81,    81,    82,    83,    83,
    84,    84,    85,    86,    87,    -1,    -1,    88,    88,    89,
    90,    92,    91,    93,    91,    94,    91,    91,    96,    95,
    97,    97,    98,    99,    99,   100,   100,   101,    -1,    -1,
    -1,   102,   103,   103,   103,   103,   103,   103,   103,   105,
   104,   106,   107,   108,   108,   109,   109,   110,   110,   111,
   112,   111,   114,   113,   115,   116,   113,   117,   113,   119,
   118,   118,   118,   120,   118,   121,   122,   122,   123,   123,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   125,    -1,    -1,   126,   127,   128,   127,   129,   130,
   129,   131,   132,   131,   133,   134,   133,   135,   136,   135,
   137,   138,   137,   139,   137,   140,   141,   140,   142,   140,
   143,   140,   144,   140,   145,   146,   145,   147,   145,   148,
   149,   148,   150,   148,   151,   152,   151,   153,   151,   154,
   151,   155,   155,   156,   157,   156,   158,   156,   156,   159,
   156,   160,   156,   161,   161,   161,   161,   161,   161,   162,
   163,   162,   164,   162,   165,   162,   166,   162,   162,   162,
   167,   162,   168,   168,   168,   168,   169,   169,   170,   170,
   171,   171,   171,   172,   173,   174,   174,   175,   175
};

static const short yyr2[] = {     0,
     2,     1,     1,     1,     3,     3,     2,     1,     1,     1,
     1,     1,     1,     1,     1,     5,     2,     1,     1,     2,
     1,     3,     1,     3,     1,     1,     0,     1,     3,     1,
     2,     0,     4,     0,     5,     0,     5,     1,     0,     3,
     1,     0,     1,     1,     0,     1,     3,     2,     1,     1,
     3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
     4,     2,     4,     1,     0,     1,     0,     2,     1,     5,
     0,     8,     0,     6,     0,     0,     9,     0,    10,     0,
     4,     2,     2,     0,     4,     5,     1,     3,     3,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     0,     1,     1,     0,     4,     1,     0,
     4,     1,     0,     4,     1,     0,     4,     1,     0,     4,
     1,     0,     4,     0,     4,     1,     0,     4,     0,     4,
     0,     4,     0,     4,     1,     0,     4,     0,     4,     1,
     0,     4,     0,     4,     1,     0,     4,     0,     4,     0,
     4,     1,     4,     1,     0,     3,     0,     3,     2,     0,
     3,     0,     5,     1,     1,     1,     1,     1,     1,     1,
     0,     5,     0,     5,     0,     4,     0,     4,     2,     2,
     0,     5,     1,     1,     1,     3,     1,     3,     1,     0,
     1,     1,     1,     1,     1,     1,     0,     1,     0
};

static const short yydefact[] = {     0,
    11,    14,    13,    12,    18,    10,     0,     2,     3,     4,
    42,     9,    15,   197,     1,    39,     0,    21,    23,    41,
     0,   195,    17,     0,    42,     6,    42,    65,     5,    32,
    31,    38,     0,    40,    22,    23,     8,    64,    42,    67,
    42,    36,    34,    25,     0,    19,    42,     7,   191,   193,
   192,   194,     0,     0,    75,    78,    80,     0,    84,   160,
    73,   155,   157,   181,     0,     0,   165,   164,   166,   167,
   168,   169,    69,    54,    53,    55,     0,    66,    56,    57,
    58,    59,   198,    87,    90,   105,   106,   109,   112,   115,
   118,   121,   126,   135,   140,   145,   152,     0,   154,   170,
   184,   185,   183,     0,     0,    45,     0,    16,    20,     0,
    28,    30,    83,    82,   199,     0,     0,     0,   199,   162,
     0,     0,     0,     0,     0,   190,    52,     0,     0,   183,
    63,    68,     0,   107,   110,   113,   116,   119,   122,   124,
   133,   131,   127,   129,   136,   138,   141,   143,   146,   148,
   150,    92,    93,    94,    95,    96,    97,    98,    99,   100,
   101,    91,     0,   159,   152,   179,   180,   177,   173,   171,
   175,    60,    62,    33,    42,    44,     0,    43,    46,     0,
   102,    24,    42,     0,   199,     0,     0,     0,     0,     0,
   161,     0,   156,   158,     0,   187,   189,     0,     0,   186,
    88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
     0,   190,     0,     0,   199,    48,    37,     0,    35,    29,
    76,     0,    81,   199,    85,     0,     0,     0,     0,     0,
   153,   108,   111,   114,   117,   120,   123,   125,   134,   132,
   128,   130,   137,   139,   142,   144,   147,   149,   151,   178,
     0,     0,   176,    61,    47,     0,   199,    70,   163,   199,
   182,   188,    86,   174,   172,     0,     0,    71,    74,     0,
   199,   199,     0,     0,    72,    77,   199,    79,     0,     0
};

static const short yydefgoto[] = {     7,
     8,     9,    10,    38,    11,    12,    13,    14,    45,    17,
    18,    46,    47,   110,   111,    36,    31,    41,   107,   106,
    20,    25,    21,   176,   177,   178,   179,   128,    73,    74,
   225,    75,    76,    40,    77,    78,    79,   282,    80,   122,
   115,   266,   116,    81,   117,   119,    82,    83,    84,   163,
   180,    85,    86,   202,    87,   203,    88,   204,    89,   205,
    90,   206,    91,   207,   208,    92,   211,   212,   210,   209,
    93,   213,   214,    94,   215,   216,    95,   217,   218,   219,
    96,    97,   123,   124,   121,   189,    98,    99,   223,   222,
   224,   221,   125,   100,   197,   198,   101,   102,   130,    24,
   104
};

static const short yypact[] = {   313,
-32768,-32768,-32768,-32768,-32768,-32768,   233,-32768,-32768,-32768,
   -45,-32768,-32768,    38,-32768,-32768,   -39,-32768,    -4,-32768,
     3,-32768,    10,    14,   -45,-32768,   -45,   313,-32768,-32768,
    -2,-32768,   313,-32768,-32768,-32768,-32768,   313,   -45,   211,
   -45,-32768,-32768,-32768,    25,-32768,   -45,-32768,-32768,-32768,
-32768,-32768,    18,    20,-32768,-32768,-32768,    39,-32768,    42,
-32768,-32768,-32768,-32768,    45,   351,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    37,   211,-32768,-32768,
-32768,-32768,    26,-32768,-32768,    64,    71,    51,    54,    55,
    24,    -6,    62,    28,   -34,-32768,   273,    81,    -5,-32768,
-32768,-32768,    58,    69,    65,   313,    81,-32768,-32768,   -24,
-32768,-32768,-32768,-32768,   281,    68,    38,    81,    81,-32768,
    15,    70,   379,   379,    72,    81,-32768,    73,     7,-32768,
-32768,-32768,    81,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    81,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   -45,-32768,    79,    83,-32768,    66,
-32768,-32768,   -45,   111,    81,    88,    11,    90,   313,    81,
-32768,    81,-32768,-32768,   136,-32768,    89,    91,    81,-32768,
-32768,    81,    81,    81,    81,    81,    81,    81,    81,    81,
    81,    81,    81,    81,    81,    81,    81,    81,    81,-32768,
    38,    81,    81,    38,   281,-32768,-32768,   313,-32768,-32768,
-32768,    93,-32768,   281,-32768,    94,    27,    99,    81,    95,
-32768,    71,    51,    54,    55,    24,    -6,    -6,    62,    62,
    62,    62,    28,    28,   -34,   -34,-32768,-32768,-32768,-32768,
   100,   -11,-32768,-32768,-32768,   102,    81,   145,-32768,   281,
-32768,-32768,-32768,-32768,-32768,    81,   112,-32768,-32768,    35,
    81,   281,   113,   106,-32768,-32768,   281,-32768,   165,-32768
};

static const short yypgoto[] = {-32768,
   159,-32768,     4,-32768,   -27,   -28,-32768,-32768,-32768,-32768,
   142,   125,   -58,-32768,   -12,    -8,-32768,-32768,-32768,-32768,
-32768,-32768,   147,-32768,-32768,-32768,   -55,   -13,   -74,-32768,
-32768,-32768,   176,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -64,  -117,-32768,
-32768,    92,-32768,-32768,     0,-32768,    -3,-32768,    -7,-32768,
    -1,-32768,    17,-32768,-32768,  -101,-32768,-32768,-32768,-32768,
  -135,-32768,-32768,  -102,-32768,-32768,  -100,-32768,-32768,-32768,
   -85,   -25,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    77,-32768,   -19,-32768,    29,   -14,-32768,
  -113
};


#define	YYLAST		451


static const short yytable[] = {    23,
    39,   129,    19,   132,    44,   188,    32,   127,   196,    22,
    39,    26,   164,    16,    27,   201,    44,    49,    50,    51,
    52,    22,   166,   167,   149,   103,   182,   141,   142,   183,
   168,    37,   105,     1,   150,   151,     2,    44,   112,     3,
   184,    48,   133,     4,    22,   220,   275,    28,     5,   169,
     6,   170,    42,   187,    43,   139,   140,    30,   143,   144,
   133,  -196,   200,   103,   133,    33,   234,   171,   113,   190,
   114,   232,   165,   249,   250,   251,   252,   108,   175,   133,
   133,   165,   270,    49,    50,    51,    52,    22,   133,   131,
   283,   145,   146,   118,   147,   148,   120,   193,   194,   126,
   103,   134,   186,    60,   196,   247,   248,   135,    62,    63,
   253,   254,   136,   241,   255,   256,   137,   172,   138,   173,
   174,   272,   185,   229,   192,   129,   195,   237,   199,    64,
   127,   257,   258,   259,   227,    66,   228,   231,   233,    67,
   235,    52,   239,   267,    68,   273,   240,    69,    70,   269,
   264,    71,    72,   277,   271,   274,   276,   278,   262,   268,
    44,   287,   281,   286,   290,    15,   226,   284,    35,   109,
   230,    34,   265,   165,   112,   236,   165,   165,   165,   165,
   165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
   165,   165,   165,   165,    29,   279,   244,   191,   181,   243,
   175,   242,   261,   245,     0,     0,   260,   285,     0,   263,
   103,   280,   288,    49,    50,    51,    52,    22,    53,   103,
    54,    55,   246,   238,     0,     0,    56,    57,    58,     0,
     0,    59,   289,    60,     0,     0,     0,    61,    62,    63,
     0,     1,     0,     0,     2,     0,     0,     3,     0,     0,
     0,     4,     0,     0,     0,   103,     5,     0,     6,    64,
    65,  -199,    28,     0,     0,    66,     0,   103,     0,    67,
     0,     0,   103,     0,    68,     0,     0,    69,    70,     0,
     0,    71,    72,    49,    50,    51,    52,    22,    53,     0,
    54,    55,     0,     0,     0,     0,    56,    57,    58,     0,
     0,    59,     0,    60,     0,     0,     0,    61,    62,    63,
     0,   152,   153,   154,   155,   156,   157,   158,   159,   160,
   161,     1,     0,     0,     2,     0,     0,     3,     0,    64,
    65,     4,    28,   162,     0,    66,     5,     0,     6,    67,
     0,     0,     0,     0,    68,     0,     0,    69,    70,     0,
     0,    71,    72,    49,    50,    51,    52,    22,     0,     1,
     0,     0,     2,     0,     0,     3,     0,     0,     0,     4,
     0,     0,     0,    60,     5,     0,     6,     0,    62,    63,
     0,    49,    50,    51,    52,    22,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
     0,    60,     0,     0,     0,    66,    62,    63,     0,    67,
     0,     0,     0,     0,    68,     0,     0,    69,    70,     0,
     0,    71,    72,     0,     0,     0,     0,    64,     0,     0,
     0,     0,     0,   190,     0,     0,     0,    67,     0,     0,
     0,     0,    68,     0,     0,    69,    70,     0,     0,    71,
    72
};

static const short yycheck[] = {    14,
    28,    66,    11,    78,    33,   119,    21,    66,   126,     7,
    38,    51,    98,    59,    54,   133,    45,     3,     4,     5,
     6,     7,    28,    29,    59,    40,    51,    34,    35,    54,
    36,    28,    41,     9,    69,    70,    12,    66,    47,    15,
   115,    38,    54,    19,     7,   163,    58,    52,    24,    55,
    26,    57,    55,   118,    57,    32,    33,    55,    65,    66,
    54,    52,    56,    78,    54,    52,    56,    73,    51,    55,
    51,   185,    98,   209,   210,   211,   212,    53,   106,    54,
    54,   107,    56,     3,     4,     5,     6,     7,    54,    53,
    56,    30,    31,    55,    67,    68,    55,   123,   124,    55,
   115,    38,   117,    23,   222,   207,   208,    37,    28,    29,
   213,   214,    62,   199,   215,   216,    63,    60,    64,    51,
    56,   239,    55,    58,    55,   190,    55,   192,    56,    49,
   189,   217,   218,   219,    56,    55,    54,    27,    51,    59,
    51,     6,    54,    51,    64,    51,    56,    67,    68,    56,
   225,    71,    72,   267,    56,    56,    55,    13,   223,   234,
   189,    56,    51,    51,     0,     7,   175,   281,    27,    45,
   183,    25,   228,   199,   183,   189,   202,   203,   204,   205,
   206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
   216,   217,   218,   219,    19,   270,   204,   121,   107,   203,
   228,   202,   222,   205,    -1,    -1,   221,   282,    -1,   224,
   225,   276,   287,     3,     4,     5,     6,     7,     8,   234,
    10,    11,   206,   195,    -1,    -1,    16,    17,    18,    -1,
    -1,    21,     0,    23,    -1,    -1,    -1,    27,    28,    29,
    -1,     9,    -1,    -1,    12,    -1,    -1,    15,    -1,    -1,
    -1,    19,    -1,    -1,    -1,   270,    24,    -1,    26,    49,
    50,    51,    52,    -1,    -1,    55,    -1,   282,    -1,    59,
    -1,    -1,   287,    -1,    64,    -1,    -1,    67,    68,    -1,
    -1,    71,    72,     3,     4,     5,     6,     7,     8,    -1,
    10,    11,    -1,    -1,    -1,    -1,    16,    17,    18,    -1,
    -1,    21,    -1,    23,    -1,    -1,    -1,    27,    28,    29,
    -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
    48,     9,    -1,    -1,    12,    -1,    -1,    15,    -1,    49,
    50,    19,    52,    61,    -1,    55,    24,    -1,    26,    59,
    -1,    -1,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
    -1,    71,    72,     3,     4,     5,     6,     7,    -1,     9,
    -1,    -1,    12,    -1,    -1,    15,    -1,    -1,    -1,    19,
    -1,    -1,    -1,    23,    24,    -1,    26,    -1,    28,    29,
    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
    -1,    23,    -1,    -1,    -1,    55,    28,    29,    -1,    59,
    -1,    -1,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
    -1,    71,    72,    -1,    -1,    -1,    -1,    49,    -1,    -1,
    -1,    -1,    -1,    55,    -1,    -1,    -1,    59,    -1,    -1,
    -1,    -1,    64,    -1,    -1,    67,    68,    -1,    -1,    71,
    72
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 20 "c-bison.y"
{MAKE_TREE(NONTERMINAL_translation_unit, 2, 1);;
    break;}
case 2:
#line 21 "c-bison.y"
{MAKE_TREE(NONTERMINAL_translation_unit, 1, 2);;
    break;}
case 3:
#line 24 "c-bison.y"
{MAKE_TREE(NONTERMINAL_external_declaration, 1, 1);;
    break;}
case 4:
#line 25 "c-bison.y"
{MAKE_TREE(NONTERMINAL_external_declaration, 1, 2);;
    break;}
case 5:
#line 28 "c-bison.y"
{MAKE_TREE(NONTERMINAL_function_definition, 3, 1);;
    break;}
case 6:
#line 32 "c-bison.y"
{MAKE_TREE(NONTERMINAL_declaration, 2, 1);;
    break;}
case 7:
#line 35 "c-bison.y"
{MAKE_TREE(NONTERMINAL_declaration_list, 2, 1);;
    break;}
case 8:
#line 36 "c-bison.y"
{MAKE_TREE(NONTERMINAL_declaration_list, 1, 2);;
    break;}
case 9:
#line 43 "c-bison.y"
{MAKE_TREE(NONTERMINAL_declaration_specifiers, 1, 1);;
    break;}
case 10:
#line 46 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_VOID, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 1);;
    break;}
case 11:
#line 47 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_CHAR, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 2);;
    break;}
case 12:
#line 49 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_INT, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 4);;
    break;}
case 13:
#line 51 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_FLOAT, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 6);;
    break;}
case 14:
#line 52 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_type_specifier, KW_DOUBLE, NULL, 0); MAKE_TREE(NONTERMINAL_type_specifier, 1, 7);;
    break;}
case 15:
#line 53 "c-bison.y"
{MAKE_TREE(NONTERMINAL_type_specifier, 1, 8);;
    break;}
case 16:
#line 57 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_or_union_specifier, 3, 1);;
    break;}
case 17:
#line 58 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_or_union_specifier, 2, 2);;
    break;}
case 18:
#line 61 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_struct_or_union, KW_STRUCT, NULL, 0); MAKE_TREE(NONTERMINAL_struct_or_union, 1, 1);;
    break;}
case 19:
#line 64 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_declaration_list, 1, 1);;
    break;}
case 20:
#line 65 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_declaration_list, 2, 2);;
    break;}
case 21:
#line 68 "c-bison.y"
{MAKE_TREE(NONTERMINAL_init_declarator_list, 1, 1);;
    break;}
case 22:
#line 69 "c-bison.y"
{MAKE_TREE(NONTERMINAL_init_declarator_list, 2, 2);;
    break;}
case 23:
#line 76 "c-bison.y"
{MAKE_TREE(NONTERMINAL_init_declarator, 1, 1);;
    break;}
case 24:
#line 80 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_declaration, 2, 1);;
    break;}
case 25:
#line 83 "c-bison.y"
{MAKE_TREE(NONTERMINAL_specifier_qualifier_list, 1, 2);;
    break;}
case 26:
#line 86 "c-bison.y"
{MAKE_TREE(NONTERMINAL_specifier_qualifier_list_opt, 1, 1);;
    break;}
case 27:
#line 87 "c-bison.y"
{MAKE_TREE(NONTERMINAL_specifier_qualifier_list_opt, 1, 2);;
    break;}
case 28:
#line 90 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_declarator_list, 1, 1);;
    break;}
case 29:
#line 91 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_declarator_list, 2, 2);;
    break;}
case 30:
#line 94 "c-bison.y"
{MAKE_TREE(NONTERMINAL_struct_declarator, 1, 1);;
    break;}
case 31:
#line 109 "c-bison.y"
{MAKE_TREE(NONTERMINAL_declarator, 2, 1);;
    break;}
case 32:
#line 112 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) '(', NULL, 0);;
    break;}
case 33:
#line 112 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) ')', NULL, 0); MAKE_TREE(NONTERMINAL_direct_declarator, 3, 1);;
    break;}
case 34:
#line 113 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) '[', NULL, 0);;
    break;}
case 35:
#line 113 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) ']', NULL, 0); MAKE_TREE(NONTERMINAL_direct_declarator, 4, 2);;
    break;}
case 36:
#line 114 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) '(', NULL, 0);;
    break;}
case 37:
#line 114 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_direct_declarator, (LONGPARAM) ')', NULL, 0); MAKE_TREE(NONTERMINAL_direct_declarator, 4, 3);;
    break;}
case 38:
#line 115 "c-bison.y"
{MAKE_TREE(NONTERMINAL_direct_declarator, 1, 4);;
    break;}
case 39:
#line 119 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_pointer, (LONGPARAM) '*', NULL, 0);;
    break;}
case 40:
#line 119 "c-bison.y"
{MAKE_TREE(NONTERMINAL_pointer, 2, 1);;
    break;}
case 41:
#line 122 "c-bison.y"
{MAKE_TREE(NONTERMINAL_pointer_opt, 1, 1);;
    break;}
case 42:
#line 123 "c-bison.y"
{MAKE_TREE(NONTERMINAL_pointer_opt, 0, 2);;
    break;}
case 43:
#line 126 "c-bison.y"
{MAKE_TREE(NONTERMINAL_parameter_type_list, 1, 1);;
    break;}
case 44:
#line 130 "c-bison.y"
{MAKE_TREE(NONTERMINAL_parameter_type_list_opt, 1, 1);;
    break;}
case 45:
#line 131 "c-bison.y"
{MAKE_TREE(NONTERMINAL_parameter_type_list_opt, 0, 2);;
    break;}
case 46:
#line 134 "c-bison.y"
{MAKE_TREE(NONTERMINAL_parameter_list, 1, 1);;
    break;}
case 47:
#line 135 "c-bison.y"
{MAKE_TREE(NONTERMINAL_parameter_list, 2, 2);;
    break;}
case 48:
#line 138 "c-bison.y"
{MAKE_TREE(NONTERMINAL_parameter_declaration, 2, 1);;
    break;}
case 49:
#line 150 "c-bison.y"
{MAKE_TREE(NONTERMINAL_initializer, 1, 1);;
    break;}
case 50:
#line 155 "c-bison.y"
{MAKE_TREE(NONTERMINAL_initializer_list, 1, 1);;
    break;}
case 51:
#line 156 "c-bison.y"
{MAKE_TREE(NONTERMINAL_initializer_list, 2, 2);;
    break;}
case 52:
#line 160 "c-bison.y"
{MAKE_TREE(NONTERMINAL_type_name, 1, 1);;
    break;}
case 53:
#line 186 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement, 1, 1);;
    break;}
case 54:
#line 187 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement, 1, 2);;
    break;}
case 55:
#line 188 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement, 1, 3);;
    break;}
case 56:
#line 189 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement, 1, 4);;
    break;}
case 57:
#line 190 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement, 1, 5);;
    break;}
case 58:
#line 191 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement, 1, 6);;
    break;}
case 59:
#line 192 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement, 1, 7);;
    break;}
case 60:
#line 195 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_labeled_statement, (LONGPARAM) ':', NULL, 0);;
    break;}
case 61:
#line 195 "c-bison.y"
{MAKE_TREE(NONTERMINAL_labeled_statement, 3, 1);;
    break;}
case 62:
#line 198 "c-bison.y"
{MAKE_TREE(NONTERMINAL_expression_statement, 1, 1);;
    break;}
case 63:
#line 202 "c-bison.y"
{MAKE_TREE(NONTERMINAL_compound_statement, 2, 1);;
    break;}
case 64:
#line 205 "c-bison.y"
{MAKE_TREE(NONTERMINAL_declaration_list_opt, 1, 1);;
    break;}
case 65:
#line 206 "c-bison.y"
{MAKE_TREE(NONTERMINAL_declaration_list_opt, 0, 2);;
    break;}
case 66:
#line 209 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement_list_opt, 1, 1);;
    break;}
case 67:
#line 210 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement_list_opt, 0, 2);;
    break;}
case 68:
#line 213 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement_list, 2, 1);;
    break;}
case 69:
#line 214 "c-bison.y"
{MAKE_TREE(NONTERMINAL_statement_list, 1, 2);;
    break;}
case 70:
#line 218 "c-bison.y"
{MAKE_TREE(NONTERMINAL_selection_statement, 2, 1);;
    break;}
case 71:
#line 219 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_selection_statement, KW_ELSE, NULL, 0);;
    break;}
case 72:
#line 219 "c-bison.y"
{MAKE_TREE(NONTERMINAL_selection_statement, 4, 2);;
    break;}
case 73:
#line 222 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_WHILE, NULL, 0);;
    break;}
case 74:
#line 222 "c-bison.y"
{MAKE_TREE(NONTERMINAL_iteration_statement, 3, 1);;
    break;}
case 75:
#line 223 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_DO, NULL, 0);;
    break;}
case 76:
#line 223 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_WHILE, NULL, 0);;
    break;}
case 77:
#line 223 "c-bison.y"
{MAKE_TREE(NONTERMINAL_iteration_statement, 4, 2);;
    break;}
case 78:
#line 224 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_iteration_statement, KW_FOR, NULL, 0);;
    break;}
case 79:
#line 224 "c-bison.y"
{MAKE_TREE(NONTERMINAL_iteration_statement, 5, 3);;
    break;}
case 80:
#line 227 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_GOTO, NULL, 0);;
    break;}
case 81:
#line 227 "c-bison.y"
{MAKE_TREE(NONTERMINAL_jump_statement, 2, 1);;
    break;}
case 82:
#line 228 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_CONTINUE, NULL, 0); MAKE_TREE(NONTERMINAL_jump_statement, 1, 2);;
    break;}
case 83:
#line 229 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_BREAK, NULL, 0); MAKE_TREE(NONTERMINAL_jump_statement, 1, 3);;
    break;}
case 84:
#line 230 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_jump_statement, KW_RETURN, NULL, 0);;
    break;}
case 85:
#line 230 "c-bison.y"
{MAKE_TREE(NONTERMINAL_jump_statement, 2, 4);;
    break;}
case 86:
#line 233 "c-bison.y"
{MAKE_TREE(NONTERMINAL_web_statement, 1, 1);;
    break;}
case 87:
#line 236 "c-bison.y"
{MAKE_TREE(NONTERMINAL_expression, 1, 1);;
    break;}
case 88:
#line 237 "c-bison.y"
{MAKE_TREE(NONTERMINAL_expression, 2, 2);;
    break;}
case 89:
#line 240 "c-bison.y"
{MAKE_TREE(NONTERMINAL_assignment_expression, 3, 1);;
    break;}
case 90:
#line 241 "c-bison.y"
{MAKE_TREE(NONTERMINAL_assignment_expression, 1, 2);;
    break;}
case 91:
#line 244 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) '=', NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 1);;
    break;}
case 92:
#line 245 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_MUL, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 2);;
    break;}
case 93:
#line 246 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_DIV, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 3);;
    break;}
case 94:
#line 247 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_PERCENT, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 4);;
    break;}
case 95:
#line 248 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_PLUS, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 5);;
    break;}
case 96:
#line 249 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_MINUS, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 6);;
    break;}
case 97:
#line 250 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_SHL, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 7);;
    break;}
case 98:
#line 251 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_SHR, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 8);;
    break;}
case 99:
#line 252 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_AND, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 9);;
    break;}
case 100:
#line 253 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_XOR, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 10);;
    break;}
case 101:
#line 254 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_assignment_operator, (LONGPARAM) ASSIGNMENT_OR, NULL, 0); MAKE_TREE(NONTERMINAL_assignment_operator, 1, 11);;
    break;}
case 102:
#line 257 "c-bison.y"
{MAKE_TREE(NONTERMINAL_constant_expression, 1, 1);;
    break;}
case 103:
#line 260 "c-bison.y"
{MAKE_TREE(NONTERMINAL_constant_expression_opt, 1, 1);;
    break;}
case 104:
#line 261 "c-bison.y"
{MAKE_TREE(NONTERMINAL_constant_expression_opt, 0, 2);;
    break;}
case 105:
#line 264 "c-bison.y"
{MAKE_TREE(NONTERMINAL_conditional_expression, 1, 1);;
    break;}
case 106:
#line 268 "c-bison.y"
{MAKE_TREE(NONTERMINAL_logical_OR_expression, 1, 1);;
    break;}
case 107:
#line 269 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_logical_OR_expression, (LONGPARAM) LOGICALOR, NULL, 0);;
    break;}
case 108:
#line 269 "c-bison.y"
{MAKE_TREE(NONTERMINAL_logical_OR_expression, 3, 2);;
    break;}
case 109:
#line 272 "c-bison.y"
{MAKE_TREE(NONTERMINAL_logical_AND_expression, 1, 1);;
    break;}
case 110:
#line 273 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_logical_AND_expression, (LONGPARAM) LOGICALAND, NULL, 0); ;
    break;}
case 111:
#line 273 "c-bison.y"
{MAKE_TREE(NONTERMINAL_logical_AND_expression, 3, 2);;
    break;}
case 112:
#line 276 "c-bison.y"
{MAKE_TREE(NONTERMINAL_inclusive_OR_expression, 1, 1);;
    break;}
case 113:
#line 277 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_inclusive_OR_expression, (LONGPARAM) '|', NULL, 0);;
    break;}
case 114:
#line 277 "c-bison.y"
{MAKE_TREE(NONTERMINAL_inclusive_OR_expression, 3, 2);;
    break;}
case 115:
#line 280 "c-bison.y"
{MAKE_TREE(NONTERMINAL_exclusive_OR_expression, 1, 1);;
    break;}
case 116:
#line 281 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_exclusive_OR_expression, (LONGPARAM) '^', NULL, 0);;
    break;}
case 117:
#line 281 "c-bison.y"
{MAKE_TREE(NONTERMINAL_exclusive_OR_expression, 3, 2);;
    break;}
case 118:
#line 284 "c-bison.y"
{MAKE_TREE(NONTERMINAL_AND_expression, 1, 1);;
    break;}
case 119:
#line 285 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_AND_expression, (LONGPARAM) '&', NULL, 0);;
    break;}
case 120:
#line 285 "c-bison.y"
{ MAKE_TREE(NONTERMINAL_AND_expression, 3, 2);;
    break;}
case 121:
#line 288 "c-bison.y"
{MAKE_TREE(NONTERMINAL_equality_expression, 1, 1);;
    break;}
case 122:
#line 289 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_equality_expression, (LONGPARAM) EQ, NULL, 0);;
    break;}
case 123:
#line 289 "c-bison.y"
{MAKE_TREE(NONTERMINAL_equality_expression, 3, 2);;
    break;}
case 124:
#line 290 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_equality_expression, (LONGPARAM) NE, NULL, 0);;
    break;}
case 125:
#line 290 "c-bison.y"
{MAKE_TREE(NONTERMINAL_equality_expression, 3, 3);;
    break;}
case 126:
#line 293 "c-bison.y"
{MAKE_TREE(NONTERMINAL_relational_expression, 1, 1);;
    break;}
case 127:
#line 294 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) '<', NULL, 0);;
    break;}
case 128:
#line 294 "c-bison.y"
{MAKE_TREE(NONTERMINAL_relational_expression, 3, 2);;
    break;}
case 129:
#line 295 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) '>', NULL, 0);;
    break;}
case 130:
#line 295 "c-bison.y"
{MAKE_TREE(NONTERMINAL_relational_expression, 3, 3);;
    break;}
case 131:
#line 296 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) LE, NULL, 0);;
    break;}
case 132:
#line 296 "c-bison.y"
{MAKE_TREE(NONTERMINAL_relational_expression, 3, 4);;
    break;}
case 133:
#line 297 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_relational_expression, (LONGPARAM) GE, NULL, 0);;
    break;}
case 134:
#line 297 "c-bison.y"
{MAKE_TREE(NONTERMINAL_relational_expression, 3, 5);;
    break;}
case 135:
#line 300 "c-bison.y"
{MAKE_TREE(NONTERMINAL_shift_expression, 1, 1);;
    break;}
case 136:
#line 301 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_shift_expression, (LONGPARAM) SHL, NULL, 0);;
    break;}
case 137:
#line 301 "c-bison.y"
{MAKE_TREE(NONTERMINAL_shift_expression, 3, 2);;
    break;}
case 138:
#line 302 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_shift_expression, (LONGPARAM) SHR, NULL, 0);;
    break;}
case 139:
#line 302 "c-bison.y"
{MAKE_TREE(NONTERMINAL_shift_expression, 3, 3);;
    break;}
case 140:
#line 305 "c-bison.y"
{MAKE_TREE(NONTERMINAL_additive_expression, 1, 1);;
    break;}
case 141:
#line 306 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_additive_expression, (LONGPARAM) '+', NULL, 0);;
    break;}
case 142:
#line 306 "c-bison.y"
{MAKE_TREE(NONTERMINAL_additive_expression, 3, 2);;
    break;}
case 143:
#line 307 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_additive_expression, (LONGPARAM) '-', NULL, 0);;
    break;}
case 144:
#line 307 "c-bison.y"
{MAKE_TREE(NONTERMINAL_additive_expression, 3, 3);;
    break;}
case 145:
#line 310 "c-bison.y"
{MAKE_TREE(NONTERMINAL_multiplicative_expression, 1, 1);;
    break;}
case 146:
#line 311 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_multiplicative_expression, (LONGPARAM) '*', NULL, 0);;
    break;}
case 147:
#line 311 "c-bison.y"
{MAKE_TREE(NONTERMINAL_multiplicative_expression, 3, 2);;
    break;}
case 148:
#line 312 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_multiplicative_expression, (LONGPARAM) '/', NULL, 0);;
    break;}
case 149:
#line 312 "c-bison.y"
{MAKE_TREE(NONTERMINAL_multiplicative_expression, 3, 3);;
    break;}
case 150:
#line 313 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_multiplicative_expression, (LONGPARAM) '%', NULL, 0);;
    break;}
case 151:
#line 313 "c-bison.y"
{MAKE_TREE(NONTERMINAL_multiplicative_expression, 3, 4);;
    break;}
case 152:
#line 316 "c-bison.y"
{MAKE_TREE(NONTERMINAL_cast_expression, 1, 1);;
    break;}
case 153:
#line 317 "c-bison.y"
{MAKE_TREE(NONTERMINAL_cast_expression, 2, 2);;
    break;}
case 154:
#line 322 "c-bison.y"
{MAKE_TREE(NONTERMINAL_unary_expression, 1, 1);;
    break;}
case 155:
#line 323 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_expression, (LONGPARAM) PLUSPLUS, NULL, 0);;
    break;}
case 156:
#line 323 "c-bison.y"
{MAKE_TREE(NONTERMINAL_unary_expression, 2, 2);;
    break;}
case 157:
#line 324 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_expression, (LONGPARAM)MINUSMINUS, NULL, 0);;
    break;}
case 158:
#line 324 "c-bison.y"
{MAKE_TREE(NONTERMINAL_unary_expression, 2, 3);;
    break;}
case 159:
#line 325 "c-bison.y"
{MAKE_TREE(NONTERMINAL_unary_expression, 2, 4);;
    break;}
case 160:
#line 326 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_expression, KW_SIZEOF, NULL, 0);;
    break;}
case 161:
#line 326 "c-bison.y"
{MAKE_TREE(NONTERMINAL_unary_expression, 2, 5);;
    break;}
case 162:
#line 327 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_expression, KW_SIZEOF, NULL, 0);;
    break;}
case 163:
#line 327 "c-bison.y"
{MAKE_TREE(NONTERMINAL_unary_expression, 2, 6);;
    break;}
case 164:
#line 331 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '&', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 1);;
    break;}
case 165:
#line 332 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '*', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 2);;
    break;}
case 166:
#line 333 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '+', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 3);;
    break;}
case 167:
#line 334 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '-', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 4);;
    break;}
case 168:
#line 335 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '~', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 5);;
    break;}
case 169:
#line 336 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_unary_operator, (LONGPARAM) '!', NULL, 0); MAKE_TREE(NONTERMINAL_unary_operator, 1, 6);;
    break;}
case 170:
#line 340 "c-bison.y"
{MAKE_TREE(NONTERMINAL_postfix_expression, 1, 1);;
    break;}
case 171:
#line 341 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) '[', NULL, 0);;
    break;}
case 172:
#line 341 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) ']', NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 4, 2);;
    break;}
case 173:
#line 342 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) '(', NULL, 0);;
    break;}
case 174:
#line 342 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) ')', NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 4, 3);;
    break;}
case 175:
#line 343 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) '.', NULL, 0);;
    break;}
case 176:
#line 343 "c-bison.y"
{MAKE_TREE(NONTERMINAL_postfix_expression, 3, 4);;
    break;}
case 177:
#line 344 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) STRUCTREF, NULL, 0);;
    break;}
case 178:
#line 344 "c-bison.y"
{MAKE_TREE(NONTERMINAL_postfix_expression, 3, 5);;
    break;}
case 179:
#line 345 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) PLUSPLUS, NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 2, 6);;
    break;}
case 180:
#line 346 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, (LONGPARAM) MINUSMINUS, NULL, 0); MAKE_TREE(NONTERMINAL_postfix_expression, 2, 7);;
    break;}
case 181:
#line 347 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_postfix_expression, KW_REQUEST_QUERYSTRING, (LONGPARAM) yytext, -1);;
    break;}
case 182:
#line 347 "c-bison.y"
{MAKE_TREE(NONTERMINAL_postfix_expression, 2, 8);;
    break;}
case 183:
#line 350 "c-bison.y"
{MAKE_TREE(NONTERMINAL_primary_expression, 1, 1);;
    break;}
case 184:
#line 351 "c-bison.y"
{MAKE_TREE(NONTERMINAL_primary_expression, 1, 2);;
    break;}
case 185:
#line 352 "c-bison.y"
{MAKE_TREE(NONTERMINAL_primary_expression, 1, 3);;
    break;}
case 186:
#line 353 "c-bison.y"
{MAKE_TREE(NONTERMINAL_primary_expression, 1, 4);;
    break;}
case 187:
#line 356 "c-bison.y"
{MAKE_TREE(NONTERMINAL_argument_expression_list, 1, 1);;
    break;}
case 188:
#line 357 "c-bison.y"
{MAKE_TREE(NONTERMINAL_argument_expression_list, 2, 2);;
    break;}
case 189:
#line 360 "c-bison.y"
{MAKE_TREE(NONTERMINAL_argument_expression_list_opt, 1, 1);;
    break;}
case 190:
#line 361 "c-bison.y"
{MAKE_TREE(NONTERMINAL_argument_expression_list_opt, 0, 2);;
    break;}
case 191:
#line 364 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_constant, CONSTANT_INTEGER, (LONGPARAM) yylval, sizeof(int)); MAKE_TREE(NONTERMINAL_constant, 1, 1);;
    break;}
case 192:
#line 365 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_constant, CONSTANT_CHAR, (LONGPARAM) yylval, sizeof(char)); MAKE_TREE(NONTERMINAL_constant, 1, 2);;
    break;}
case 193:
#line 366 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_constant, CONSTANT_FLOATING, (LONGPARAM) yyfval, sizeof(float)); MAKE_TREE(NONTERMINAL_constant, 1, 3);;
    break;}
case 194:
#line 369 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_string, CONSTANT_STRING, (LONGPARAM) yytext, -1); MAKE_TREE(NONTERMINAL_string, 1, 1);;
    break;}
case 195:
#line 372 "c-bison.y"
{MAKE_PUSH_NODE(NONTERMINAL_identifier, IDENTIFIER, (LONGPARAM) yytext, -1); MAKE_TREE(NONTERMINAL_identifier, 1, 1);;
    break;}
case 196:
#line 376 "c-bison.y"
{MAKE_TREE(NONTERMINAL_identifier_opt, 1, 1);;
    break;}
case 197:
#line 377 "c-bison.y"
{MAKE_TREE(NONTERMINAL_identifier_opt, 0, 2);;
    break;}
case 198:
#line 380 "c-bison.y"
{MAKE_TREE(NONTERMINAL_expression_opt, 1, 1);;
    break;}
case 199:
#line 381 "c-bison.y"
{MAKE_TREE(NONTERMINAL_expression_opt, 0, 2);;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 386 "c-bison.y"

