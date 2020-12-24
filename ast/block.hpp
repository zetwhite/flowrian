#ifndef __AST_H__
#define __AST_H__

#include "node.hpp"
#include <vector> 
using namespace std; 

//typedef enum {FUNC_DEC, VAR_DEC, GVAR_DEC, IF, WHILE, CMD, ASS, SIMPLE} STTYPE;

class Block{
public : 
  virtual void print(); 
}; 

class FuncBodyB : public Block{
public: 
  vector <Node> starts; 
  Node ends; 
  vector<Block> stmts; 

  void print(); 
}; 

class FuncDecB : public Block{
public:
  vector<Node> inTypes; 
  vector<Node> outTypes; 
  FuncBodyB body;

  void print(); 
}; 

class VarDecB : public Block {
public: 
  vector<Node> ids; 
  vector<Node> types; 

  void print(); 
}; 

class GVarDecB : public Block {
public: 
  Node cmd; 
  vector<Node> ids; 
  vector<Node> types; 

  void print(); 
}; 

class IfB : public Block {
public: 
  Node condition; 
  vector<Block> ifStmts; 
  vector<Block> elseStmts; 

  void print(); 
}; 

class WhileB : public Block {
public: 
  Node condition; 
  vector<Block> stmts; 

  void print(); 
}; 

class CmdB : public Block {
public: 
  Node cmd; 
  Node exp;  

  void print(); 
}; 

class AssB : public Block {
public : 
  Node id; 
  Node exp; 

  void print(); 
}; 

class SimpleB : public Block {
public : 
  Node exp; 

  void print();  
}; 

#endif
