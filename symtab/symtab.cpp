#include "symtab.hpp"


SymTab::SymTab(string fid){
  functionId = fid; 
  offset = 0; 
}

bool SymTab::insert(string vid, ITERTYPE t){
  SymNode record(t, offset); 
  auto ret = table.insert({vid, record}); 
    
  if( ret.second ) { //insert success 
    offset += record.size; 
  }
  return ret.second; 
}

ITERTYPE SymTab::lookupType(string vid){
  auto iter = table.find(vid); 
  if(iter == table.end())
    return INVALID; 
  else
    return iter->second.type; 
  
}

int SymTab::lookupOffset(string vid){
  auto iter = table.find(vid); 
  if(iter == table.end())
    return ERR_OFFSET; 
  else
    return iter->second.offset; 
} 

int SymTab::lookupSize(string vid){
  auto iter = table.find(vid); 
  if(iter == table.end())
    return ERR_SIZE; 
  else
    return iter->second.size; 
}


void SymTab::print(){
  cout << "=== [[ symbol table of (" << functionId << ") ]] ===" << endl; 
  cout << "id \t\t type \t\toffset \t\tsize" << endl; 
  auto iter = table.begin(); 
  for(iter=table.begin(); iter != table.end(); iter++){
    cout << iter->first << "\t\t"; 
    iter->second.print(); 
    cout << endl; 
  }
}