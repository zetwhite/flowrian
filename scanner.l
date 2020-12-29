%{
	#include "syntaxTreeParser.h"
	#include "ast/block.hpp"
	#include "ast/node.hpp"
	#include <string.h>

	extern int lineno; 
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
{space}	{ }

","			{ return _COMMA; }
"::"		{ return _COLONS; }
"="			{ return _ASS; }
";"			{ return _SEMI; } 
"("			{ return _OPAREN; }
")" 		{ return _CPAREN; }
"{"			{ return _OCURLY; }
"}" 		{ return _CCURLY; }
"["			{ return _OBRACK; }
"]"			{ return _CBRACK; }
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

"--".*"\n" { lineno++; }
"\n"			 { lineno++; }

"integer" { return _INT; }
"bool"		{ return _BOOL; }
"char"		{ return _CHAR; }
"void"		{ return _VOID; }
"true"		{ return _TRUE; }
"false"		{ return _FALSE; }

"if"		{ return _IF; }
"else"	{ return _ELSE; }
"while"	{ return _WHILE; }
"start"	{ return _START; }
"end"		{ return _END; }

"global"	{ return _GLOBAL; }
"delete" 	{ return _DELETE; }

%%

int yywrap(){ 
	return 1; 
} 
