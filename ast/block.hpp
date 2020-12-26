#ifndef __AST_H__
#define __AST_H__

#include "node.hpp"
#include "../symtab/symnode.hpp"
#include "../symtab/symtab.hpp"
#include <vector> 
#include <iostream> 
using namespace std; 

class Block{
public : 
  virtual void print(int space = 0); 
  virtual void addSymbol(SymTab* table, SymTab* globaltable); 
  virtual bool checkType(SymTab* table);
}; 

class FuncBodyB : public Block{
public: 
  vector <Node*> starts; 
  Node* end; 
  vector<Block*> stmts; 

  FuncBodyB(vector<Node*>* s, Node* e, vector<Block*>* st);
  bool checkType(SymTab* table);  
  void addSymbol(SymTab* table, SymTab* globaltable);  
  void print(int space = 0); 
}; 


class FuncDecB : public Block{
public:
  char* id; 
  vector<Node*> inTypes; 
  Node* outType; 
  FuncBodyB* body;

  FuncDecB(char* i, vector<Node*>* in, Node* out, FuncBodyB* fb); 
  bool checkType(SymTab* table); 
  void addSymbol(SymTab* table, SymTab* globaltable); 
  void print(int space = 0); 

}; 


class VarDecB : public Block {
public: 
  bool global; 
  vector<Node*> ids; 
  vector<Node*> types; 
  Node* value; 

  VarDecB(vector<Node*>* i, vector<Node*>* t, bool g = false); 
  VarDecB(Node* i, Node* t, bool g = false); 
  VarDecB(Node* i, Node* t, Node* e, bool g = false); 
  void setGlobal(); 
  bool checkType(SymTab* table); 
  void addSymbol(SymTab* table, SymTab* globaltable); 
  void print(int space = 0); 
}; 

class IfB : public Block {
public: 
  Node* condition; 
  vector<Block*> ifStmts; 
  vector<Block*> elseStmts; 

  IfB(Node* c, vector<Block*>* i, vector<Block*>* e = nullptr); 
  bool checkType(SymTab* table); 
  void addSymbol(SymTab* table, SymTab* globaltable); 
  void print(int space = 0); 
}; 


class WhileB : public Block {
public: 
  Node* condition; 
  vector<Block*> stmts; 

  WhileB(Node* c, vector<Block*>* s); 
  bool checkType(SymTab* table); 
  void addSymbol(SymTab* table, SymTab* globaltable); 
  void print(int space = 0); 
}; 


class CmdB : public Block {
public: 
  Node* cmd; 
  Node* other;  

  CmdB(Node* c, Node* o); 
  void print(int space = 0); 
}; 


class AssB : public Block {
public : 
  Node* id; 
  Node* exp; 

  AssB(Node* i, Node* e); 
  bool checkType(SymTab* table); 
  void print(int space = 0); 
}; 


class SimpleB : public Block {
public : 
  Node* exp; 

  SimpleB(Node*); 
  SimpleB(); 
  bool checkType(SymTab* table); 
  void print(int space = 0);  
}; 

#endif
