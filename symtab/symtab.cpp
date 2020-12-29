#include "symtab.hpp"


SymTab::SymTab(string fid){
  functionId = fid; 
  offset = 3; 
  roffset = -1; 
}

bool SymTab::insert(string vid, ITERTYPE t, int size){
  SymNode record(t, offset, size); 
  auto ret = table.insert({vid, record}); 
    
  if( ret.second ) { //insert success 
    offset += record.size; 
  }
  return ret.second; 
}

bool SymTab::insertReverse(string vid, ITERTYPE t, int size){
  SymNode record(t, roffset, size);
  auto ret = table.insert({vid, record});  
  if( ret.second) {
    roffset -= record.size; 
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
  const int idx = 15; 
  cout << "===== [[ symbol table of (" << functionId << ") ]] =====" << endl; 
  cout << left << setw(idx) << "id" << setw(idx) << "type" << setw(idx) << "offset" << setw(idx) << "size" << endl; 
  auto iter = table.begin(); 
  for(iter=table.begin(); iter != table.end(); iter++){
    cout << left << setw(idx) <<  iter->first; 
    iter->second.print(); 
    cout << endl; 
  }
}