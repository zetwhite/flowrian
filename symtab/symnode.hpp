#ifndef __SYMNODE_H__
#define __SYMNODE_H__
#include "../global.hpp"
#include <string> 
#include <iostream> 
#include <iomanip>
using namespace std; 

class SymNode{
public : 
  ITERTYPE type; 
  int offset; 
  char* address; 
  int size; 

  SymNode(ITERTYPE t, int o, int s = 1); 
  void print(); 
}; 

#endif