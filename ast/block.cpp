
#include "block.hpp"
#include <iostream>
#include <string> 
using namespace std; 

/*
string toString(STTYPE type){
  switch (type)
  {
    case FUNC_DEC: return "function delcaration"; 
    case VAR_DEC: return "variable delcaration"; 
    case GVAR_DEC: return "global variable command"; 
    case IF : return "if block"; 
    case WHILE : return "while block"; 
    case CMD : return "input/output command"; 
    case ASS : return "assignment block"; 
    case SIMPLE : return "simple expression or function call"; 
    default: return "wrong type"; 
  }
}
*/

void Block::print() {
  // cout << "block type : " << toString(type) << endl; 
}

void printNodeList(vector<Node>& nodes){
  for(int i = 0; i < nodes.size(); i++){
    nodes[i].print(); 
  }
}

void printBlockList(vector<Block>& blocks){
  for(int i = 0; i < blocks.size(); i++){
    blocks[i].print(); 
  }
}

void FuncDecB::print(){
  Block::print(); 
  printNodeList(inTypes); 
  printNodeList(outTypes); 
}

void FuncBodyB::print(){
  Block::print(); 
  printNodeList(starts); 
  ends.print(); 
  printBlockList(stmts); 
}

void VarDecB::print(){
  Block::print(); 
  printNodeList(ids); 
  printNodeList(types); 
}

void GVarDecB::print(){
  Block::print(); 
  cmd.print(); 
  printNodeList(ids); 
  printNodeList(types); 
}

void IfB::print(){
  Block::print(); 
  condition.print(); 
  printBlockList(ifStmts); 
  printBlockList(elseStmts); 
}

void WhileB::print(){
  Block::print(); 
  condition.print(); 
  printBlockList(stmts); 
}

void CmdB::print(){
  cmd.print(); 
  exp.print(); 
}

void AssB::print(){
  id.print(); 
  exp.print();
}

void SimpleB::print(){
  exp.print(); 
}