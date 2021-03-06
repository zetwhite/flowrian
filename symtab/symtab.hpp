#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#include <iostream> 
#include <map> 
#include <iomanip> 
#include "symnode.hpp"

#define ERR_OFFSET -200 
#define ERR_SIZE -100
using namespace std; 

class SymTab{
public : 
  int roffset; 
  int offset; 
  string functionId; 
  map<string, SymNode> table; 
  
  SymTab(string fid); 
  bool insert(string vid, ITERTYPE t, int size = 1);
  bool insertReverse(string vid, ITERTYPE t, int size = 1); 
  ITERTYPE lookupType(string vid); 
  int lookupOffset(string vid); 
  int lookupSize(string vid); 
  void print();  
}; 


#endif 