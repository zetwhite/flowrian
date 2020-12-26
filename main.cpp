#include <iostream> 
#include <vector> 
#include "ast/block.hpp"
#include "ast/node.hpp"
#include "symtab/symtab.hpp"
#include "syntaxTreeParser.h"

using namespace std; 

//global symbol table
SymTab globalTable("global");
int codeSection = 1; 

int main(){

  extern vector<Block*> program; 

  // ========================= parsing! =================================================
  yyparse(); 
  int functionCnt = program.size(); 
  for(int i = 0; i < functionCnt; i++){
    program.at(i)->print(); 
    cout << endl; 
  }

  // ======================= create symbol table! ========================================= 
  //symbol table per function 
  vector<SymTab*> symbolTables;

  for(int i = 0; i < functionCnt; i++){
    FuncDecB* func = dynamic_cast<FuncDecB*>(program.at(i)); 
    SymTab* table = new SymTab(func->id); 
    func->addSymbol(table, &globalTable); 
    symbolTables.push_back(table); 
  }
  
  for(int i = 0; i < symbolTables.size(); i++){
    symbolTables[i]->print(); 
    cout << endl; 
  }
  globalTable.print(); 
  cout << endl; 

  //======================= type checker ====================================================
  
  bool typeCheck = true; 
  for(int i = 0; i < functionCnt; i++){
    FuncDecB* func = dynamic_cast<FuncDecB*>(program.at(i)); 
    typeCheck = func->checkType(symbolTables[i]); 
    if(typeCheck == false)
      break; 
  }

  if( typeCheck == false ) {
    cout << "can not continue because of type check error  " << endl; 
    return -1; 
  }

  //================== code generator ====================================================
  for(int i = 0; i < functionCnt; i++){
    FuncDecB* func = dynamic_cast<FuncDecB*>(program.at(i)); 
    cout << "=======[[ code of " << string(func->id ) << " ]] ============" << endl; 

    list<string> code = func->codeGen(symbolTables[i]); 
    for(auto v : code){
      cout << v << endl; 
    }
  }

  return 0; 
}