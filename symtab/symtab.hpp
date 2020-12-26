#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#include <iostream> 
#include <map> 
#include "symnode.hpp"

using namespace std; 

class SymTab{
public : 
  int offset; 
  string functionId; 
  map<string, SymNode> table; 
  
  SymTab(string fid); 
  bool insert(string vid, ITERTYPE t);
  ITERTYPE lookupType(string vid); 
  void print();  
}; 


#endif 