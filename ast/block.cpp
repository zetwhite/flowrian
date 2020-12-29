
#include "block.hpp"

using namespace std; 

extern int codeSection; 
extern vector<Block*> program; 
const string TE = "[TYPE ERROR] "; 
const string SE = "[SYNTAX ERROR] "; 

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

bool Block::addSymbol(SymTab* table, SymTab* globaltable){
  return true; 
}

bool Block::checkType(SymTab* table){
  return true; 
}

list<string> Block::codeGen(SymTab* table){
  return list<string>(); 
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
  cout << s << "===== Delcare Function " << id << "=====" << endl; 
  cout << s_ << "input arg type  : "; 
  printNodeList(inTypes); 
  cout << endl; 
  cout << s_ << "output type  : "; 
  outType->print();  
  cout << endl; 
}

FuncDecB::FuncDecB(char* i, int fid, vector<Node*>* in, Node* out, FuncBodyB* fb){
  id = i; 
  functionNumber = fid; 
  inTypes.insert(inTypes.end(), in->begin(), in->end()); 
  outType = out; 
  body = fb; 
}

bool FuncDecB::addSymbol(SymTab* tab, SymTab* globaltab){
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
    return false; 
  }
  for(int i = 0; i < inTypes.size(); i++){
    TypeN* typeNode = dynamic_cast<TypeN*>(inTypes[i]); 
    ITERTYPE t = typeNode->type;
    int s = typeNode->size; 
    string vid = string(dynamic_cast<IdN*>(body->starts[i])->value);  
    bool res = tab->insert(vid, t, s);
    if(res == false){
      cout << SE <<  " in " + string(id) + " declaration, start variable has dup id" << endl; 
      return false; 
    } 
  }
  return body->addSymbol(tab, globaltab); 
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
    if(vtype == INVALID){
      cout << SE << " in " + string(id) << ", undefined variable is found" << endl; 
      return false; 
    }
    if(ttype != vtype){
      cout << TE << " in " + string(id) + ", end value and return argument type is differ" << endl; 
      return false; 
    }
  }
  return body->checkType(table); 
}

list<string> FuncDecB::codeGen(SymTab* table){
  list<string> code; 

  //stack allocation
  if(string(id) != "#main")
    code.push_back("F" + to_string(functionNumber) + ":"); 
  code.push_back("ssp " + to_string(table->offset)); 
  code.splice(code.end(), body->codeGen(table)); 

  if(string(id) == "#main")
    code.push_back("stp"); 
  else{
    ITERTYPE t = dynamic_cast<TypeN*>(outType)->type; 
    if(t == VOID)
      code.push_back("retp"); 
    else
      code.push_back("retf"); 
  }
  return code; 
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

bool FuncBodyB::addSymbol(SymTab* tab, SymTab* globaltab){
  bool result = true; 
  for(int i = 0; i < stmts.size(); i++){
    result = stmts[i]->addSymbol(tab, globaltab); 
    if(result == false)
      break; 
  }
  return result; 
}

bool FuncBodyB::checkType(SymTab* table){
  bool result = true; 
  for(int i = 0; i < stmts.size(); i++){
    bool result = stmts[i]->checkType(table); 
    if(result == false)
      break; 
  }
  return result; 
}

list<string> FuncBodyB::codeGen(SymTab* table){
  list<string> code; 
  for(int i = 0; i < stmts.size(); i++){
    list<string> addr = stmts[i]->codeGen(table); 
    code.insert(code.begin(), addr.begin(), addr.end()); 
  }
  code.splice(code.end(), end->calcCode(table));  
  code.push_back("str 0"); //return value saver 
  return code; 
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

  if(iSize == 1 && value != nullptr){
    TypeN* t = dynamic_cast<TypeN*>(types[0]); 
    if(value->calcType(table) != t->type)
      return false; 
  }
  return true; 
}

void VarDecB::setGlobal(){
  global = true; 
}

bool VarDecB::addSymbol(SymTab* table, SymTab* globaltab){
  int iSize = ids.size(); 
  int tSize = types.size(); 
  if(iSize != tSize){
    cout << SE  << "variable id and type isn't match => fail to create symboltable" << endl; 
    return false; 
  }
  for(int i = 0; i < ids.size(); i++){
    string vid = string(dynamic_cast<IdN*>(ids[i])->value); 
    TypeN* type = dynamic_cast<TypeN*>(types[i]); 
    ITERTYPE t = type->type; 
    int s = type->size; 

    bool res; 
    if(global == true)
      res = globaltab->insert(vid, t, s); 
    else 
      res = table->insert(vid, t, s); 

    if(res == false){
      cout << SE << vid << " is duplicate fail to delcaration" << endl; 
      return false; 
    }
  }
  return true; 
} 

void VarDecB::print(int space){
  printNodeList(ids); 
  printNodeList(types); 
  if(value != nullptr)
    value->print(); 
}

list<string> VarDecB::codeGen(SymTab* table){
  list<string> code; 
  if(value != nullptr && ids.size() == 1){
    code.splice(code.end(), value->calcCode(table)); 
    string vid = string(dynamic_cast<IdN*>(ids[0])->value); 
    int offset = table->lookupOffset(vid); 

    if(types[0]->calcType(table) == CHAR){
      int size = code.size(); 
      for(int i = 0; i < size; i++){
        code.push_back("str " + to_string(offset + size - i)); 
      } 
    }
    else if(types[0]->calcType(table) == INT){
      code.push_back("str " + to_string(offset)); 
    }
  }
  return code; 
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

bool IfB::addSymbol(SymTab* tab, SymTab* globaltab){
  bool result = true; 
  for(int i = 0; i < ifStmts.size(); i++){
    result = ifStmts[i]->addSymbol(tab, globaltab); 
    if(result == false)
      break; 
  }
  if(result == false) 
    return result; 

  for(int i = 0; i < elseStmts.size(); i++){
    result = elseStmts[i]->addSymbol(tab, globaltab); 
    if(result == false)
      break; 
  }
  return result; 
}

bool IfB::checkType(SymTab* table){
  if(condition->calcType(table) != BOOL) {
    cout << TE << "If statement condition isn't boolean type at LINE " << condition->lineno << endl; 
    return false; 
  }
 return true; 
}

list<string> IfB::codeGen(SymTab* table){
  list<string> code;

  int ifSection, continueSection; 
  list<string> conCode = condition->calcCode(table); 
  code.insert(code.begin(), conCode.begin(), conCode.end()); 

  code.push_back("fjp L" + to_string(codeSection)); 
  ifSection = codeSection; 
  codeSection++; 

  //if statement
  for(int i = ifStmts.size() - 1; i >= 0; i--){
    list<string> addr = ifStmts[i]->codeGen(table); 
    code.insert(code.end(), addr.begin(), addr.end()); 
  }
  code.push_back("ujp L" + to_string(codeSection)); 
  continueSection = codeSection; 
  codeSection++; 

  //else statement 
  code.push_back("L"+ to_string(ifSection) + ":"); 
  for(int i = elseStmts.size()-1; i >= 0; i--){
    list<string> addr = elseStmts[i]->codeGen(table); 
    code.insert(code.end(), addr.begin(), addr.end()); 
  }

  //continue statment 
  code.push_back("L"+ to_string(continueSection) + ":"); 
  return code; 
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

bool WhileB::addSymbol(SymTab* tab, SymTab* globaltab){
  bool result = true; 
  for(int i = 0; i < stmts.size(); i++){
    result = stmts[i]->addSymbol(tab, globaltab); 
    if(result == false)
      break; 
  }
  return result; 
}

bool WhileB::checkType(SymTab* table){
  if(condition->calcType(table) != BOOL) {
    cout << toString(condition->calcType(table)) << endl; 
    cout << TE << "WHILE statement condition isn't boolean type at LINE " << condition->lineno << endl; 
    return false; 
  }
  return true; 
}

list<string> WhileB::codeGen(SymTab* table){
  list<string> code;
  int conditionSection, continueSection; 
  conditionSection = codeSection++; 
  continueSection = codeSection++; 

  //condition Section
  code.push_back("L"+ to_string(conditionSection) + ":"); 
  list<string> conCode = condition->calcCode(table); 
  code.splice(code.end(), conCode); 
  code.push_back("fjp L" + to_string(continueSection)); 

  //inner while 
  for(int i = 0; i < stmts.size(); i++){
    list<string> addr = stmts[i]->codeGen(table); 
    code.splice(code.end(), addr); 
  }
  code.push_back("ujp L" + to_string(conditionSection)); 
  code.push_back("L"+ to_string(continueSection) + ":"); 
  return code; 
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

list<string> CmdB::codeGen(SymTab* table){
  list<string> code; 
  CMDTYPE ctype = dynamic_cast<CmdN*>(cmd)->type; 
  ITERTYPE t = other->calcType(table); 

  
  if(ctype == READ){
    if(t == INT){
      code.push_back("in"); 
    }
    else if(t == CHAR){
      /*TODO*/ 
    }
  }

  if(ctype == WRITE){
    list<string> getValue = other->calcCode(table);
    code.insert(code.begin(), getValue.begin(), getValue.end());  
    
    if(t == INT){
      code.push_back("out"); 
    }
    else if (t == CHAR){
      for(int i = 0; i < getValue.size(); i++){
        code.push_back("outc"); 
      }
    }
  }

  return code; 
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
  ITERTYPE itype = id->calcType(table); 
  ITERTYPE etype = exp->calcType(table); 
  if( itype != etype ) {
    cout << TE << "assignment type error at LINE " << id->lineno << endl; 
    if( itype == INVALID){
      cout << SE << "left variable no defined!!" << endl; 
    }
    else {
      cout << "left is " << toString(itype) << ", but right is " << toString(etype) << endl;  
    }
    return false; 
  }
  return true; 
}


list<string> AssB::codeGen(SymTab* table){
  list<string> code; 

  code.splice(code.end(), exp->calcCode(table));

  string vid = string(dynamic_cast<IdN*>(id)->value);
  int offset = table->lookupOffset(vid); 

  code.push_back("str " + to_string(offset)); 
  return code; 
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
