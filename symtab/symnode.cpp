#include "symnode.hpp"

SymNode::SymNode(ITERTYPE t, int o){
  type = t; 
  offset = o; 
  address = nullptr; 
  if(t == INT || t == BOOL){
    size = 4; 
  }
  else if(t == VOID || t== STRING){
    size = 0; 
  }
}

void SymNode::print(){
  cout << toString(type) << "\t\t"; 
  cout << offset << "\t\t"; 
  cout << size << "\t\t"; 
}