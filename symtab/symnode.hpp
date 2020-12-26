#ifndef __SYMNODE_H__
#define __SYMNODE_H__
#include "../global.hpp"
#include <string> 
#include <iostream> 
using namespace std; 

class SymNode{
public : 
  ITERTYPE type; 
  int offset; 
  char* address; 
  int size; 

  SymNode(ITERTYPE t, int o); 
  void print(); 
}; 

#endif