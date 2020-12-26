
#include "block.hpp"

using namespace std; 

extern vector<Block*> program; 
const string TE = "[TYPE ERROR] "; 
const string SE = "[SYNTAX ERROR] "; 

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

string makespace(int s){
  string str; 
  for(int i = 0; i < s; i++){
    str.append(" "); 
  }
  return str; 
}

void Block::print(int space) {
  // cout << "block type : " << toString(type) << endl; 
}

void Block::addSymbol(SymTab* table, SymTab* globaltable){
  return; 
}

bool Block::checkType(SymTab* table){
  return true; 
}

void printNodeList(vector<Node*>& nodes){
  for(int i = 0; i < nodes.size(); i++){
    nodes[i]->print(); 
    cout << ", " ; 
  }
}

void printBlockList(vector<Block*>& blocks){
  cout << blocks.size() << endl; 
  for(int i = 0; i < blocks.size(); i++){
    blocks[i]->print(); 
  }
}

//------------------------------------------------------

void FuncDecB::print(int space){
  Block::print(); 
  string s = makespace(space);
  string s_ =  makespace(space + 1);  
  cout << s << "===============================" << endl; 
  cout << s << "Delcare Function " << id << endl; 
  cout << s_ << "input arg type  : "; 
  printNodeList(inTypes); 
  cout << endl; 
  cout << s_ << "output type  : "; 
  outType->print();  
  cout << endl; 
}

FuncDecB::FuncDecB(char* i, vector<Node*>* in, Node* out, FuncBodyB* fb){
  id = i; 
  inTypes.insert(inTypes.end(), in->begin(), in->end()); 
  outType = out; 
  body = fb; 
}

void FuncDecB::addSymbol(SymTab* tab, SymTab* globaltab){
  auto iter = inTypes.begin();
  //erase void type 
  while(iter != inTypes.end()){
    if(dynamic_cast<TypeN*>(*iter)->type == VOID) 
      iter = inTypes.erase(iter); 
    else 
      iter++; 
  } 

  int tSize = inTypes.size(); 
  int iSize = body->starts.size(); 
  if(tSize != iSize){
    cout << SE << " in " + string(id) + " declaration, function argument and start arugment count is differ"; 
    cout << " => fail to create symbol table" << endl; 
    return; 
  }
  for(int i = 0; i < inTypes.size(); i++){
    ITERTYPE t = dynamic_cast<TypeN*>(inTypes[i])->type;
    if(t != VOID){
      string vid = string(dynamic_cast<IdN*>(body->starts[i])->value);  
      bool res = tab->insert(vid, t);
      if(res == false){
        cout << SE <<  " in " + string(id) + " declaration, start variable has dup id" << endl; 
      } 
    }
  }
  body->addSymbol(tab, globaltab); 
}

bool FuncDecB::checkType(SymTab* table){
  auto iter = inTypes.begin();
  //erase void type 
  while(iter != inTypes.end()){
    if(dynamic_cast<TypeN*>(*iter)->type == VOID) 
      iter = inTypes.erase(iter); 
    else 
      iter++; 
  } 

  //start argument count check 
  int tSize = inTypes.size(); 
  int iSize = body->starts.size(); 
  if(tSize != iSize){
    cout << SE << " in " + string(id) + " declaration, function argument and start arugment count is differ" << endl; 
    return false; 
  }

  //end value type check
  ITERTYPE ttype = outType -> calcType(table); 
  if(ttype != VOID){
    ITERTYPE vtype = body->end->calcType(table); 
    if(ttype != vtype){
      cout << TE << " in " + string(id) + ", end value and return argument type is differ" << endl; 
    }
  }
  return body->checkType(table); 
}

//-----------------------------------------------

void FuncBodyB::print(int space){
  Block::print(); 
  printNodeList(starts); 
  end->print(); 
  printBlockList(stmts); 
}

FuncBodyB::FuncBodyB(vector<Node*>* s, Node* e, vector<Block*>* st){
  starts.insert(starts.begin(), s->begin(), s->end()); 
  end = e; 
  stmts.insert(stmts.end(), st->begin(), st->end()); 
}

void FuncBodyB::addSymbol(SymTab* tab, SymTab* globaltab){
  for(int i = 0; i < stmts.size(); i++){
    stmts[i]->addSymbol(tab, globaltab); 
  }
}

bool FuncBodyB::checkType(SymTab* table){
  bool result = true; 
  for(int i = 0; i < stmts.size(); i++){
    if(stmts[i]->checkType(table) == false)
      result = false; 
  }
  return result; 
}

//--------------------------------------------------

VarDecB::VarDecB(vector<Node*>* i, vector<Node*>* t, bool g){
  ids.insert(ids.end(), i->begin(), i->end()); 
  types.insert(types.end(), t->begin(), t->end()); 
  value = nullptr; 
  global = g; 
} 

VarDecB::VarDecB(Node* i, Node* t, bool g){
  ids.push_back(i); 
  types.push_back(t); 
  value = nullptr; 
  global = g; 
}

VarDecB::VarDecB(Node* i, Node* t, Node* e, bool g){
  ids.push_back(i); 
  types.push_back(t); 
  value = e; 
  global = g; 
}

bool VarDecB::checkType(SymTab* table){
  int iSize = ids.size(); 
  int tSize = types.size(); 
  if(iSize != tSize){
    cout << SE  << "variable id and type isn't match" << endl; 
    return false; 
  }
  return true; 
}

void VarDecB::setGlobal(){
  global = true; 
}

void VarDecB::addSymbol(SymTab* table, SymTab* globaltab){
  int iSize = ids.size(); 
  int tSize = types.size(); 
  if(iSize != tSize){
    cout << SE  << "variable id and type isn't match => fail to create symboltable" << endl; 
    return; 
  }
  for(int i = 0; i < ids.size(); i++){
    string vid = string(dynamic_cast<IdN*>(ids[i])->value);
    ITERTYPE t = dynamic_cast<TypeN*>(types[i])->type; 
    bool res; 
    if(global == true)
      res = globaltab->insert(vid, t); 
    else 
      res = table->insert(vid, t); 
    if(res == false){
      cout << SE << vid << " is duplicate fail to delcaration" << endl; 
    }
  }
} 

void VarDecB::print(int space){
  printNodeList(ids); 
  printNodeList(types); 
  if(value != nullptr)
    value->print(); 
}

//-------------------------------------------------

IfB::IfB(Node* c, vector<Block*>* i, vector<Block*>* e ){
  condition = c; 
  ifStmts.insert(ifStmts.end(), i->begin(), i-> end()); 
  if(e != nullptr){
    elseStmts.insert(elseStmts.end(), e->begin(), e-> end()); 
  }
}

void IfB::print(int space){
  Block::print(); 
  condition->print(); 
  printBlockList(ifStmts); 
  printBlockList(elseStmts); 
}

void IfB::addSymbol(SymTab* tab, SymTab* globaltab){
  for(int i = 0; i < ifStmts.size(); i++){
    ifStmts[i]->addSymbol(tab, globaltab); 
  }
  for(int i = 0; i < elseStmts.size(); i++){
    elseStmts[i]->addSymbol(tab, globaltab); 
  }
}


bool IfB::checkType(SymTab* table){
  if(condition->calcType(table) != BOOL) {
    cout << TE << "If statement condition isn't boolean type at LINE " << condition->lineno << endl; 
    return false; 
  }
 return true; 
}

//---------------------------------------------------

WhileB::WhileB(Node* n, vector<Block*>* s){
  condition = n; 
  stmts.insert(stmts.end(), s->begin(), s->end()); 
}

void WhileB::print(int space){
  condition->print(); 
  printBlockList(stmts); 
}

void WhileB::addSymbol(SymTab* tab, SymTab* globaltab){
  for(int i = 0; i < stmts.size(); i++){
    stmts[i]->addSymbol(tab, globaltab); 
  }
}

bool WhileB::checkType(SymTab* table){
  if(condition->calcType(table) != BOOL) {
    cout << toString(condition->calcType(table)) << endl; 
    cout << TE << "WHILE statement condition isn't boolean type at LINE " << condition->lineno << endl; 
    return false; 
  }
  return true; 
}

//-----------------------------------

CmdB::CmdB(Node* c, Node* o){
  cmd = c; 
  other = o; 
}

void CmdB::print(int space){
  cmd->print(); 
  other->print(); 
}


//----------------------------------

AssB::AssB(Node* i, Node* e){
  id = i; 
  exp = e; 
}

void AssB::print(int space){
  id->print(); 
  exp->print();
}

bool AssB::checkType(SymTab* table){
  if(id->calcType(table) != exp->calcType(table)) {
    cout << TE << "assignment type error at LINE " << id->lineno << endl; 
    cout << "left is " << toString(id->calcType(table)) << ", but right is " << toString(exp->calcType(table)) << endl;  
    return false; 
  }
  return true; 
}


//----------------------------------

SimpleB::SimpleB(Node* n){
  exp = n; 
}

SimpleB::SimpleB(){
  exp = nullptr; 
}

void SimpleB::print(int space){
  if(exp != nullptr)
    exp->print(); 
  else 
    printf("empty node\n"); 
}

bool SimpleB::checkType(SymTab* table){
  if(exp == nullptr)
    return true; 
  
  if(exp->calcType(table) == INVALID){
    cout << TE << "error at LINE " << exp->lineno << endl;
    return false;  
  } 
  return true; 
}
