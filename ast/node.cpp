#include "node.hpp"

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

//==============================================

CmdN::CmdN(CMDTYPE t){
  type = t; 
}

void CmdN::print(){
  cout << "command node\n"; 
}

//==============================================

OpN::OpN(OPTYPE t){
  type = t; 
}


void OpN::print(){
  cout << "operation node\n"; 
}

//============================================

IdN::IdN(IDTYPE t, char* s){
  type = t; 
  value = s; 
}

void IdN::print(){
  cout << "id(" << value << ")"; 
  Node::print();
}

//==============================================

TypeN::TypeN(ITERTYPE t){
  type = t; 
}

void TypeN::print(){
  cout << "type node\n"; 
}

//==============================================

IteralN::IteralN(ITERTYPE t, int value){
  type = t; 
  ival = value; 
}

IteralN::IteralN(ITERTYPE t, char* value){
  type = t; 
  sval = value; 
}

void IteralN::print(){
  cout << "interal node\n"; 
}

