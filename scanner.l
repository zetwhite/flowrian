%{
	#include "syntaxTreeParser.h"
	#include "node.h"
	#include <string.h>

	int line = 1; 
%}

digit		[0-9] 
alpha		[a-zA-Z]
space 		[ \t]
varid 		$([a-zA-Z0-9]|[_])+
funcid 		#([a-zA-Z0-9]|[_])+
literal 	\"([^\\\"]|\\.)*\"

%%
{digit}+	{ yylval.iVal = atoi(yytext); return _NUMBER;}
{varid} 	{ yylval.sVal = strdup(yytext); return _VARID; }
{literal}	{ yylval.sVal = (char*)malloc(yyleng); 
						sprintf(yylval.sVal, "%s", yytext);
						return _LITERAL; 
					}
{funcid}	{ yylval.sVal = strdup(yytext); return _FUNCID; }

","			{ return _COMMA; }
"::"		{ return _COLONS; }
"="			{ return _ASS; }
";"			{ return _SEMI; } 
"("			{ return _OPAREN; }
")" 		{ return _CPAREN; }
"{"			{ return _OCURLY; }
"}" 		{ return _CCURLY; }
"@"			{ return _AT; }
"->"		{ return _TORIGHT; }
"<-"		{ return _TOLEFT; }

"+" 		{ return _PLUS; }
"-"			{ return _MINUS; }
"*" 		{ return _TIMES; }
"%" 		{ return _MOD; }
"/" 		{ return _DIV;}
">"			{ return _GT; }
"<"			{ return _LT; }
">=" 		{ return _GE; }
"<="		{ return _LE; }
"=="		{ return _EQ; }
"!="		{ return _NEQ; }

"--".*"\n"	{ }

"integer" { return _INT; }
"float"		{ return _FLOAT; }
"string"	{ return _STRING; }
"void"		{ return _VOID; }

"if"		{ return _IF; }
"else"	{ return _ELSE; }
"while"	{ return _WHILE; }
"start"	{ return _START; }
"end"		{ return _END; }


%%

int yywrap(){ 
	return 1; 
} 
