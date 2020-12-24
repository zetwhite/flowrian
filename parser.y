%{
	#include <stdio.h> 
	#include "ast/block.hpp"
       #include "ast/node.hpp"
       #define DBUG

       using namespace std; 
	int yyerror(const char* msg), yylex(); 

       void dbg(const char* s){
              #ifdef DBUG 
              printf("%s", s); 
              fflush(stdout); 
              #endif
       }

       vector<Block*>* program; 
%}	
%code requires { #include "ast/node.hpp" }
%code requires { #include "ast/block.hpp" }

%union {
	Node* node; 
       Block* block; 
       vector<Block*>* blocks; 
       vector<Node*>* nodes; 
	int iVal; 
	char* sVal;  
}

%token <iVal> _NUMBER
%token <sVal> _VARID _FUNCID _LITERAL
%type <nodes> IdList TypeList ExpList FuncArg
%type <node> Id Type Factor Exp Term IFactor Number FuncRet Condition
%type <block> StDecFunc FuncBody Stmt StDecId StGlobal StIf StWhile StCommand StAssign StSimple 
%type <blocks> Funcs Stmts 


%token _IF _ELSE _WHILE _START _END _OPAREN _CPAREN _OCURLY _CCURLY _SEMI _COLONS _COMMA _ASS 
%token _GLOBAL _DELETE
%token _AT _TOLEFT _TORIGHT
%token _PLUS _MINUS _TIMES _MOD _DIV 
%token _GT _LT _GE _LE _EQ _NEQ 
%token _INT _FLOAT _STRING _VOID 

%right _ELSE 
%start Prog

%%
Prog   : Funcs              { dbg("total program\n"); program = $1; }
       ; 

Funcs  : StDecFunc Funcs    { dbg("declare function!\n"); $$->push_back($1); }
       |                    { $$ = new vector<Block*>(); }
       ; 

StDecFunc : _FUNCID _COLONS TypeList _TORIGHT Type FuncBody
              { dbg("function declaration part\n"); $$ = new FuncDecB($1, $3, $5, dynamic_cast<FuncBodyB*>($6));}
       ; 

FuncBody : _OPAREN _START FuncArg _SEMI Stmts _END FuncRet _SEMI _CPAREN
              { dbg("function body part" ); $$ = new FuncBodyB($3, $7, $5); }
       ; 

FuncArg : IdList            { $$ = $1; }
       |                    { dbg("create empty node"); $$ = new vector<Node*>(); }
       ; 

FuncRet : Exp               { $$ = $1; }
       |                    { dbg("create empty ret node"); $$ = new IteralN(INT, 0); }
       ; 

Stmts : Stmt Stmts          { dbg("add new statments\n");   $1->print(); $2->push_back($1); $$ = $2;}
       |                    { dbg("no statment!\n");        $$ = new vector<Block*>();}
       ; 

Stmt   : StDecId _SEMI      { dbg("declaration ID\n");      $$ = $1; }
       | StGlobal _SEMI     { dbg("global defintion ID\n"); $$ = $1; }
       | StIf               { dbg("if statement\n");        $$ = $1; }
       | StWhile            { dbg("while statment\n");      $$ = $1; }
       | StCommand  _SEMI   { dbg("command statment\n");    $$ = $1; }
	| StAssign  _SEMI    { dbg("assignment statement\n");   $$ = $1; }
       | StSimple _SEMI     { dbg("simple statments\n");    $$ = $1; }
       | _SEMI              { dbg("semi only line \n");     $$ = new SimpleB(); }
       ; 

StDecId : IdList _COLONS TypeList  { dbg("variable declartion list\n"); $$ = new VarDecB($1, $3); }
       | Id _COLONS Type           { dbg("variable declartion one\n");  $$ = new VarDecB($1, $3); }
       | Id _COLONS Type _ASS Exp  { dbg("variable declaration with init\n"); $$ = new VarDecB($1, $3, $5); }
       ; 

StGlobal : _GLOBAL StDecId  { dynamic_cast<VarDecB*>($2)->setGlobal(); $$ = $2; }       
       | _DELETE Id         { Node* n = new CmdN(DELETE); $$ = new CmdB(n, $2); }
       ;

StIf   : _IF _OPAREN Condition _CPAREN _OCURLY Stmts _CCURLY 
              { dbg("if part\n" ); $$ = new IfB($3, $6); }
       | _IF _OPAREN Condition _CPAREN _OCURLY Stmts _CCURLY _ELSE _OCURLY Stmts _CCURLY
              { dbg("if-else part\n"); $$ = new IfB($3, $6, $10); }
       ; 

StWhile : _WHILE _OPAREN Condition _CPAREN _OCURLY Stmts _CCURLY
              { dbg("while part\n"); $$ = new WhileB($3, $6); }
       ; 

StCommand : _AT _TOLEFT Exp  { dbg("print statments01\n");  Node* n = new CmdN(WRITE); $$ = new CmdB(n, $3); }
       | Id _TOLEFT _AT      { dbg("read statement\n");     Node* n = new CmdN(READ);  $$ = new CmdB(n, $1); }
       ; 

StAssign : Id _ASS Exp       { dbg("Assignment\n");          $$ = new AssB($1, $3); }
       ; 

StSimple :  Exp              { dbg("JustExp \n");           $$ = new SimpleB($1); }
       ;


Condition : Exp _LT Exp      { dbg("Less Than \n");         $$ = new OpN(LT); $$->addSon($3); }
       | Exp _GT Exp         { dbg("Greater Then\n");       $$ = new OpN(GT); $$->addSon($3); }
       | Exp _LE Exp         { dbg("Less Equal\n");         $$ = new OpN(LE); $$->addSon($3); }
       | Exp _GE Exp         { dbg("Greate Equal\n");       $$ = new OpN(GE); $$->addSon($3); }
       | Exp _EQ Exp         { dbg("Equal\n");              $$ = new OpN(EQ); $$->addSon($3); }
       | Exp _NEQ Exp        { dbg("Not Equal\n");          $$ = new OpN(NEQ); $$->addSon($3); }
       ; 

Exp    : Exp _PLUS Term     { dbg("plus binary op\n");      $$ = new OpN(ADD); $$->addSon($3); }
       | Exp _MINUS Term    { dbg("minus binary op\n");     $$ = new OpN(SUB); $$->addSon($3); }
       | Term               { $$ = $1; }
       ;

Term   : Term _TIMES Factor  { dbg("times binary op\n");    $$ = new OpN(MUL); $$->addSon($3); }
       | Term _DIV Factor    { dbg("div binary op\n");      $$ = new OpN(DIV); $$->addSon($3); }
       | Term _MOD Factor    { dbg("mod binary op\n");      $$ = new OpN(MOD); $$->addSon($3); }  
       | Factor              { $$ = $1; }
       ;

Factor  : _FUNCID ExpList   
              { dbg("call function\n");   $$ = new IdN(FUNCID, $1);  $$->addSons($2); $$->print(); }
       | IFactor            { $$ = $1; }
       ; 

IFactor : _MINUS Number            { dbg("unary minus\n");  $$ = new OpN(UMINUS); $$->addSon($2); }
       | _PLUS Number              { dbg("unary plus\n");   $$ = new OpN(UPLUS); $$->addSon($2); }
       | Number                    { $$ = $1; }
       ;

Number  : Id                       { dbg("find id\n");            $$ = $1; }
       | _LITERAL                  { dbg("this is stirng \n");    $$ = new IteralN(STRING, _LITERAL);  }
       | _NUMBER                   { dbg("find number\n");        $$ = new IteralN(INT, _NUMBER); } 
       | _OPAREN Exp _CPAREN       { dbg("into parentheses\n");   $$ = $2; }
       ;

TypeList : TypeList _COMMA Type    { $1->push_back($3); $$ = $1; }
       | Type                      { $$ = new vector<Node*>(); $$->push_back($1); }
       ; 

IdList : IdList _COMMA Id          { $1->push_back($3); $$ = $1; }
       | Id                        { $$ = new vector<Node*>(); $$->push_back($1); }
       ; 

ExpList : ExpList _COMMA Exp       { $1->push_back($3); $$ = $1; }
       | Exp                       { $$ = new vector<Node*>(); $$->push_back($1); }
       ; 

Id     : _VARID      { dbg($1); $$ = new IdN(VARID, $1); }
       ; 

Type   : _INT        { dbg("find var int \n");       $$ = new TypeN(INT); }
       | _FLOAT      { dbg("find var flaot \n");     $$ = new TypeN(FLOAT); }
       | _STRING     { dbg("find var string \n");    $$ = new TypeN(STRING); }
       | _VOID       { dbg("find var void \n");      $$ = new TypeN(VOID); } 
       ; 
%%

int yyerror(const char* msg) { 
       fputs(msg, stderr); 
       return 0; 
}

int main(){
       yyparse(); 
       return 0; 
}