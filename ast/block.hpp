#ifndef __AST_H__
#define __AST_H__

#include "node.hpp"
#include <vector> 
#include <iostream> 
using namespace std; 

//typedef enum {FUNC_DEC, VAR_DEC, GVAR_DEC, IF, WHILE, CMD, ASS, SIMPLE} STTYPE;

class Block{
public : 
  virtual void print(); 
}; 

class FuncBodyB : public Block{
public: 
  vector <Node*> starts; 
  Node* end; 
  vector<Block*> stmts; 

  FuncBodyB(vector<Node*>* s, Node* e, vector<Block*>* st); 
  void print(); 
}; 


class FuncDecB : public Block{
public:
  char* id; 
  vector<Node*> inTypes; 
  Node* outType; 
  FuncBodyB* body;

  FuncDecB(char* i, vector<Node*>* in, Node* out, FuncBodyB* fb); 
  void print(); 
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
  void print(); 
}; 

class IfB : public Block {
public: 
  Node* condition; 
  vector<Block*> ifStmts; 
  vector<Block*> elseStmts; 

  IfB(Node* c, vector<Block*>* i, vector<Block*>* e = nullptr); 
  void print(); 
}; 


class WhileB : public Block {
public: 
  Node* condition; 
  vector<Block*> stmts; 

  WhileB(Node* c, vector<Block*>* s); 
  void print(); 
}; 


class CmdB : public Block {
public: 
  Node* cmd; 
  Node* other;  

  CmdB(Node* c, Node* o); 
  void print(); 
}; 


class AssB : public Block {
public : 
  Node* id; 
  Node* exp; 

  AssB(Node* i, Node* e); 
  void print(); 
}; 


class SimpleB : public Block {
public : 
  Node* exp; 

  SimpleB(Node*); 
  SimpleB(); 
  void print();  
}; 

#endif
