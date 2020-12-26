#include "node.hpp"
#include "block.hpp"

extern SymTab globalTable;  
extern vector<Block*> program; 

const string TE = "[TYPE ERROR] "; 
const string SE = "[SYNTAX ERROR] "; 

string toString(NTYPE type){
  switch(type){
    case CMD : return "command node"; 
    case OP : return "op node"; 
    case TYPE : return "type node"; 
    case ITERAL : return "iteral node"; 
    default : 
      return "wrong nodeType"; 
  }
}

void Node::print(){
  if(son.size() > 0){
    cout << " => "; 
    for(int i = 0; i < son.size(); i++){
      son[i]->print(); 
      cout << ", "; 
    } 
    cout << endl; 
  }
}

void Node::addSon(Node* n){
  son.push_back(n); 
}

void Node::addSons(vector<Node*>* n){
  son.insert(son.end(), n->begin(), n->end()); 
}

ITERTYPE Node:: calcType(SymTab* table){
  return INVALID; 
}

list<string> Node::calcCode(SymTab* table){
  return list<string>(); 
}


//==============================================

CmdN::CmdN(CMDTYPE t, int l):Node(l){
  type = t; 
}

void CmdN::print(){
  cout << "command node\n"; 
}

//==============================================

OpN::OpN(OPTYPE t, int l):Node(l){
  type = t; 
}

void OpN::print(){
  cout << "operation node\n"; 
}

ITERTYPE OpN::calcType(SymTab* table){
  //check unary operation
  if(type == UPLUS || type == UMINUS){
    if( son.size() <= 0){
      cout << SE << "unary operatoin operand error at LINE " << lineno << endl; 
      return INVALID; 
    }
    if( son[0]->calcType(table) == INT){
      return INT; 
    }  
  }
  
  if(son.size() != 2){
    cout << "son size : " << son.size() << endl; 
    cout << SE << "unary operatoin operand error at LINE " << lineno << endl; 
    return INVALID; 
  }
  ITERTYPE t1 = son[0]->calcType(table); 
  ITERTYPE t2 = son[1]->calcType(table); 
  if( t1 != t2 ){
    cout << TE <<"operand type is not same at LINE " << lineno << endl; 
    return INVALID; 
  }
  if( t1 == INT ){
    if(type == LT || type == GT || type == GE || type == LE || type == EQ || type == NEQ)
      return BOOL; 
    else
      return INT;  
  }
  if( t1 == BOOL ){
    if(!(type == EQ || type == NEQ))
      cout << TE <<"operand type must be bool or number at LINE " << lineno << endl; 
    else
      return BOOL; 
  }
  cout << TE << "operand type must be bool or number at LINE " << lineno << endl; 
  return INVALID; 
}

list<string> OpN::calcCode(SymTab* table){
  list<string> code; 
  for(int i = son.size()-1; i >= 0; i--){
    list<string> addr = son[i]->calcCode(table); 
    code.insert(code.begin(), addr.begin(), addr.end());
    //code.splice(code.end(), son[i]->calcCode(table)); 
  }
  if(type == ADD) 
    code.push_back("add"); 
  else if(type == SUB)
    code.push_back("sub"); 
  else if(type == MUL)
    code.push_back("mul"); 
  else if(type == DIV)
    code.push_back("div"); 
  else if(type == UMINUS)
    code.push_back("neg"); 
  
  else if(type == EQ)
    code.push_back("equ"); 
  else if(type == NEQ){
    code.push_back("equ"); 
    code.push_back("not"); 
  }
  else if(type == GT)
    code.push_back("grt"); 
  else if(type == LT)
    code.push_back("les"); 
  else if(type == GE)
    code.push_back("geq"); 
  else if(type == LE)
    code.push_back("leq"); 
  return code; 
}  


//============================================

IdN::IdN(IDTYPE t, char* s, int l):Node(l){
  type = t; 
  value = s; 
}

void IdN::print(){
  cout << "id(" << value << ")"; 
  Node::print();
}

ITERTYPE IdN::calcType(SymTab* table){
  if(type == VARID){
    ITERTYPE t = table->lookupType(string(value));
    if(t == INVALID){
      t = globalTable.lookupType(string(value)); 
    }
    return t; 
  } 
  if(type == FUNCID){
    //search function in list 
    FuncDecB* funcP = nullptr; 
    for(int i = 0; i < program.size(); i++){
      FuncDecB* tmpP = dynamic_cast<FuncDecB*>(program[i]); 
      if(strcmp(tmpP->id, value) == 0 ){
        funcP = tmpP; 
        break; 
      }
    }

    //check argument type 
    bool success = true; 
    int argSize = funcP->inTypes.size(); 
    int pasSize = son.size(); 
    if(argSize != pasSize){
      cout << SE << "calling function(" << string(value) << ") argument count is differ, at LINE " << lineno << endl; 
      return INVALID; 
    }
    for(int i = 0; i < argSize; i++){
      if(funcP->inTypes[i]->calcType(table) != son[i]->calcType(table)){
        cout << TE << "calling function(" << string(value) << ") argument type is differ, at LINE" << lineno << endl;  
        return INVALID; 
      }
    }
    return funcP->outType->calcType(table);  
  }
  return VOID; 
}

list<string> IdN::calcCode(SymTab* table){
  list<string> code; 

  if(type == VARID){
    string vid = string(value); 
    int offset = table->lookupOffset(vid);
    int size = table->lookupSize(vid); 
    for(int i = 0; i < size; i++){
      code.push_back("lod " + to_string(offset+i)); 
    }
  }

  return code; 
}  

//==============================================

TypeN::TypeN(ITERTYPE t, int l):Node(l){
  type = t; 
}

void TypeN::print(){
  string strType = toString(type); 
  cout << "type(" << strType  << ")"; 
}

ITERTYPE TypeN::calcType(SymTab* table){
  return type; 
}


//==============================================

IteralN::IteralN(ITERTYPE t, int value, int l):Node(l){
  type = t; 
  ival = value; 
}

IteralN::IteralN(ITERTYPE t, char* value, int l):Node(l){
  type = t; 
  sval = value; 
}

IteralN::IteralN(ITERTYPE t, bool value, int l):Node(l){
  type = t; 
  bval = value; 
}


void IteralN::print(){
  cout << "interal node\n"; 
}

ITERTYPE IteralN::calcType(SymTab* table){
  return type; 
}

list<string> IteralN::calcCode(SymTab* table){
  list<string> code;
  if(type == INT){
    code.push_back("ldc " + to_string(ival)); 
  }
  else if(type == STRING){
    int slen = strlen(sval);
    for(int i = slen - 2; i >= 1; i--){
      code.push_back("ldc '" + string(1, sval[i]) + "'" ); 
    }
  }
  else if(type == BOOL){
    if(bval == false)
      code.push_back("ldc 0"); 
    else 
      code.push_back("ldc 1"); 
  }
  return code; 
}  
