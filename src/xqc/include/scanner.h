#ifndef XQC_SCANNER_H
#include "x.h"

#include "ast.h"
#include "logging.h"
#include "prefs.h"
#include "parser.h"
#include "tokens.h"
#define XQC_SCANNER_H

typedef struct {
  char* cPath;
  char* cFile;
  char* cBasePath;
  char* cText;
  size_t cSize;
  
  x_List *tkList;
  prefs_stPrefs* prefs;
  struct TkNode* tkTST;
  
  bool isEOF;
  
  int x;
  int y;
  int indent;
  
} scanner_stScanner;

scanner_stScanner scanner_fnNewScanner(prefs_stPrefs* prefs);
ast_stSrcTree scanner_fnScanAndParseFiles(prefs_stPrefs* prefs);

#endif