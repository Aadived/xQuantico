#include "../../include/ast.h"

ast_stSrcTree ast_fnNewSrcTree(){
  return (ast_stSrcTree){
    .type = script,
    .rc = 0,
  };
}