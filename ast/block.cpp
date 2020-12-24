
#include "block.hpp"

using namespace std; 

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

void Block::print() {
  // cout << "block type : " << toString(type) << endl; 
}

void printNodeList(vector<Node*>& nodes){
  for(int i = 0; i < nodes.size(); i++){
    nodes[i]->print(); 
  }
}

void printBlockList(vector<Block*>& blocks){
  cout << blocks.size() << endl; 
  for(int i = 0; i < blocks.size(); i++){
    blocks[i]->print(); 
  }
}

//------------------------------------------------------
void FuncDecB::print(){
  Block::print(); 
  cout << id << " "; 
  printNodeList(inTypes); 
  outType->print();  
}

FuncDecB::FuncDecB(char* i, vector<Node*>* in, Node* out, FuncBodyB* fb){
  id = i; 
  inTypes.insert(inTypes.end(), in->begin(), in->end()); 
  outType = out; 
  body = fb; 
}

//-----------------------------------------------

void FuncBodyB::print(){
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

void VarDecB::setGlobal(){
  global = true; 
}

void VarDecB::print(){
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

void IfB::print(){
  Block::print(); 
  condition->print(); 
  printBlockList(ifStmts); 
  printBlockList(elseStmts); 
}

//---------------------------------------------------

WhileB::WhileB(Node* n, vector<Block*>* s){
  condition = n; 
  stmts.insert(stmts.end(), s->begin(), s->end()); 
}

void WhileB::print(){
  condition->print(); 
  printBlockList(stmts); 
}

//-----------------------------------

CmdB::CmdB(Node* c, Node* o){
  cmd = c; 
  other = o; 
}

void CmdB::print(){
  cmd->print(); 
  other->print(); 
}

//----------------------------------

AssB::AssB(Node* i, Node* e){
  id = i; 
  exp = e; 
}

void AssB::print(){
  id->print(); 
  exp->print();
}

//----------------------------------

SimpleB::SimpleB(Node* n){
  exp = n; 
}

SimpleB::SimpleB(){
  exp = nullptr; 
}

void SimpleB::print(){
  if(exp != nullptr)
    exp->print(); 
  else 
    printf("empty node\n"); 
}