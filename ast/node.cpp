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

void CmdN::print(){
  cout << "command node\n"; 
}

void OpN::print(){
  cout << "operation node\n"; 
}

void IdN::print(){
  cout << "id node\n"; 
}

void TypeN::print(){
  cout << "type node\n"; 
}

void IteralN::print(){
  cout << "interal node\n"; 
}