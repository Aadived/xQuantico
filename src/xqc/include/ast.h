#ifndef XQC_AST_H
#include "x.h"
#define XQC_AST_H

typedef enum ast_eRootNode {mod=0, script=1} ast_eRootNode;
typedef enum ast_eNodeType {
  EXPR,
} ast_eNodeType;

typedef struct ast_stModAST ast_stModAST;
typedef struct ast_stScriptAST ast_stScriptAST;
typedef struct ast_stNode ast_stNode;

struct ast_stModAST {
  bool isActive;
  char* modName;
  char* modPath;
  ast_stNode* node;
};

struct ast_stScriptAST {
  bool isActive;
  ast_stNode* node;
};

struct ast_stNode {
  int idx;
  ast_eNodeType type;
  ast_stNode* left;
  ast_stNode* right;
  ast_stNode* prev;
  ast_stNode* next;
};

typedef struct {
  ast_eRootNode type;
  ast_stModAST mainMod;
  ast_stScriptAST mainScript;
  int rc;
} ast_stSrcTree;

ast_stSrcTree ast_fnNewSrcTree();

#endif