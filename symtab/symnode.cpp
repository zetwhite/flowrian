#include "symnode.hpp"

SymNode::SymNode(ITERTYPE t, int o){
  type = t; 
  offset = o; 
  address = nullptr; 

  if(t == INT || t == BOOL){
    size = 1; 
  }
  if(t == VOID){
    size = 0; 
  }
  if(t == STRING){
    size = 10; //can handle only up to 10 character...;; 
  }
}

void SymNode::print(){
  cout << toString(type) << "\t\t"; 
  cout << offset << "\t\t"; 
  cout << size << "\t\t"; 
}