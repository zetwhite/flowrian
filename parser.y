%{
	#include <stdio.h> 
	#include "ast/node.hpp"
	int yyerror(const char* msg), yylex(); 

       Node* AST; 
%}	

%union {
	struct node* pNode; 
	int iVal; 
	char* sVal;  
}
%token <iVal> _NUMBER
%token <sVal> _VARID _FUNCID _LITERAL
%type <pNode> Id Type

%token _IF _ELSE _WHILE _START _END _OPAREN _CPAREN _OCURLY _CCURLY _SEMI _COLONS _COMMA _ASS 

%token _CREATE _DELETE
%token _AT _TOLEFT _TORIGHT
%token _PLUS _MINUS _TIMES _MOD _DIV 
%token _GT _LT _GE _LE _EQ _NEQ 
%token _INT _FLOAT _STRING _VOID 


%right _ELSE 

%start Prog

%%
Prog   : Funcs       { printf("total program\n"); }
       ; 

Funcs  : StDecFunc Funcs  { printf("declare function!\n"); }
       |
       ; 

StDecFunc : _FUNCID _COLONS TypeList _TORIGHT Type FuncBody
              { printf("function declaration part\n");}
       ; 

FuncBody : _OPAREN _START FuncArg _SEMI Stmts _END FuncRet _SEMI _CPAREN
              { printf("function body part" );}
       ; 

FuncArg : IdList 
       | 
       ; 

FuncRet : Exp 
       | 
       ; 

Stmts : Stmt Stmts
       | 
       ; 

Stmt   : StDecId _SEMI      { printf("declaration ID\n"); }
       | StGlobal _SEMI     { printf("global defintion ID\n"); }
       | StIf               { printf("if statement\n"); }
       | StWhile            { printf("while statment\n"); }
       | StCommand  _SEMI   { printf("command statment\n"); }
	| StAssign  _SEMI    { printf("find one sentence\n"); }
       | StSimple _SEMI     { printf("simple statments\n"); }
       | _SEMI              { printf("semi only line \n"); }
       ; 

StDecId : IdList _COLONS TypeList { printf("variable declartion list\n"); }
       | Id _COLONS Type { printf("variable declartion one\n");}
       | Id _COLONS Type _ASS Exp { printf("variable declaration with init\n"); }
       ; 

StGlobal : _CREATE StDecId
       | _DELETE Id 
       ;

StIf   : _IF _OPAREN Condition _CPAREN _OCURLY Stmts _CCURLY 
              { printf("if part\n" ); }
       | _IF _OPAREN Condition _CPAREN _OCURLY Stmts _CCURLY _ELSE _OCURLY Stmts _CCURLY
              { printf("if-else part\n"); }
       ; 

StWhile : _WHILE _OPAREN Condition _CPAREN _OCURLY Stmts _CCURLY
              { printf("while part\n"); }
       ; 

StCommand : _AT _TOLEFT Exp  
              { printf("print statments01\n"); }
       | Id _TOLEFT _AT
              { printf("read statement\n"); }
       ; 

StAssign : Id _ASS Exp      { printf("Assignment\n"); }
       ; 

StSimple :  Exp               { printf("JustExp \n"); }
       ;


Condition : Exp _LT Exp       { printf("Less Than \n"); }
       | Exp _GT Exp         { printf("Greater Then\n"); }
       | Exp _LE Exp         { printf("Less Equal\n"); }
       | Exp _GE Exp         { printf("Greate Equal\n"); }
       | Exp _EQ Exp         { printf("Equal\n"); }
       | Exp _NEQ Exp        { printf("Not Equal\n"); }
       ; 


Exp    : Exp _PLUS Term     { printf("plus binary op\n"); }
       | Exp _MINUS Term    { printf("minus binary op\n"); }
       | Term               { }
       ;

Term   : Term _TIMES Factor  { printf("times binary op\n"); }
       | Term _DIV Factor    { printf("div binary op\n"); }
       | Term _MOD Factor    { printf("mod binary op\n"); }  
       | Factor             { }
       ;

Factor  : _FUNCID ExpList { printf("call function\n"); }
       | IFactor 
       ; 

IFactor : _MINUS Number     { printf("unary minus\n");}
       | _PLUS Number       { printf("unary plus\n"); }
       | Number
       ;

Number  : Id                { printf("find id\n");  }
       | _LITERAL           { printf("this is stirng \n"); }
       | _NUMBER            { printf("find number\n");  } 
       | _OPAREN Exp _CPAREN { printf("into parentheses\n");  }
       ;

TypeList : TypeList _COMMA Type  
       | Type   
       ; 

IdList  : IdList _COMMA Id  
       | Id
       ; 

ExpList : ExpList _COMMA Exp  
       | Exp
       ; 

Id     : _VARID      
       { 
       printf("find var id \n"); 
       }
       ; 

Type   : _INT        { printf("find var int \n"); }
       | _FLOAT      { printf("find var flaot \n"); }
       | _STRING     { printf("find var string \n");}
       | _VOID       { printf("find var void \n");} 
       ; 
%%

int main() { yyparse(); return 0; }
int yyerror(const char* msg) { fputs(msg, stderr); return 0; }
