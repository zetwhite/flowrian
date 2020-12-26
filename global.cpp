#include "global.hpp"

string toString(ITERTYPE t){
  switch (t)
  {
  case INT : return "integer"; 
  case STRING : return "string"; 
  case VOID : return "void"; 
  case BOOL : return "bool"; 
  default:  return "Invlaid"; 
  }
}