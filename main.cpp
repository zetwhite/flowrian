#include <iostream> 
#include <vector> 
#include <fstream> 
#include "ast/block.hpp"
#include "ast/node.hpp"
#include "symtab/symtab.hpp"
#include "option.hpp"
#include "syntaxTreeParser.h"

using namespace std; 

//global symbol table
SymTab globalTable("global");
int codeSection = 1; 


int main(int argc, char* argv[]){

  extern vector<Block*> program; 
  string inFile = ""; 
  string outFile = "a.t"; 
  bool showSymbol = false; 
  bool showFunction = false; 

  parseInput(argc, argv, outFile, inFile, showSymbol, showFunction); 

  // ========================= parsing! =================================================
  yyparse(); 
  int functionCnt = program.size(); 

  if(showFunction){
      for(int i = 0; i < functionCnt; i++){
        program.at(i)->print(); 
        cout << endl; 
      }
      cout << "\n\n" << endl; 
  }

  // ======================= create symbol table! ========================================= 

  vector<SymTab*> symbolTables;
  for(int i = 0; i < functionCnt; i++){
    FuncDecB* func = dynamic_cast<FuncDecB*>(program.at(i)); 
    SymTab* table = new SymTab(func->id); 
    func->addSymbol(table, &globalTable); 
    symbolTables.push_back(table); 
  }
  
  if(showSymbol){
      for(int i = 0; i < symbolTables.size(); i++){
        symbolTables[i]->print(); 
        cout << endl; 
      }
      globalTable.print(); 
      cout << "\n\n" << endl; 
  }


  //======================= type checker ====================================================
  
  bool typeCheck = true; 
  for(int i = 0; i < functionCnt; i++){
    FuncDecB* func = dynamic_cast<FuncDecB*>(program.at(i)); 
    typeCheck = func->checkType(symbolTables[i]); 
    if(typeCheck == false)
      break; 
  }

  cout << endl; 
  if( typeCheck == false ) {
    cout << "can not continue because of type check error  " << endl; 
    return -1; 
  }

  //================== code generator ====================================================

  ofstream out(outFile, ios::out|ios::trunc); 

  int mainIndex = -1; 
  FuncDecB* main = nullptr; 
  for(int i = 0; i < functionCnt; i++){
    FuncDecB* func = dynamic_cast<FuncDecB*>(program.at(i)); 
    if(string(func->id) == "#main"){
      main = func; 
      mainIndex = i; 
      break; 
    }
  }
  if(main == nullptr){
    cout << "can not find #main function. you need to declare main function as entry point" << endl; 
    return -1; 
  }

  //create main function first!
  list<string> code = main->codeGen(symbolTables[mainIndex]); 
  for(auto v : code) {
    if('A' <= v[0] && v[0] <= 'Z') //if label print in one line
      out << v << " "; 
    else 
      out << v << endl; 
  }

  //create other function! 
  for(int i = 0; i < functionCnt; i++){
    FuncDecB* func = dynamic_cast<FuncDecB*>(program.at(i)); 
    if(string(func->id) == "#main") 
      continue; 

    list<string> code = func->codeGen(symbolTables[i]); 
    for(auto v : code) {
      if('A' <= v[0] && v[0] <= 'Z') //if label print in one line 
        out << v << " "; 
      else 
        out << v << endl; 
    }
  }

  return 0; 
}