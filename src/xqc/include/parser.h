#ifndef XQC_PARSER_H
#include "x.h"

#include "ast.h"
#include "logging.h"
#include "prefs.h"
#include "tokens.h"
#define XQC_PARSER_H

typedef struct {
  char* path;
  bool isEOF;
  int x;
  int y;
} parser_stParser;

void parser_fnParse(char* name, logging_eLevel lvl, ast_stSrcTree* tree, x_List* tkList);

#endif