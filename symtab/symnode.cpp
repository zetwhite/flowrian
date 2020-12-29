#include "symnode.hpp"

SymNode::SymNode(ITERTYPE t, int o, int s){
  type = t; 
  offset = o; 
  address = nullptr; 
  size = s; 
}

void SymNode::print(){
  const int idx = 15; 
  cout << left << setw(idx) << toString(type) << setw(idx) << offset << setw(idx) << size; 
}