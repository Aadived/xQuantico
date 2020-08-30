#include "../../include/scanner.h"

const int szCH = sizeof(tokens_stCHMap);
const int szTK = sizeof(tokens_stToken);

scanner_stScanner scanner_fnNewScanner(prefs_stPrefs* prefs){
  size_t size = 0;
  char* text = (char*)x_LoadFile(prefs->srcPath, &size);
  
  return (scanner_stScanner){
    .cPath = prefs->srcPath,
    .cFile = prefs->srcName,
    .cBasePath = prefs->srcBasePath,
    .cText = text,
    .cSize = size,
    .tkList = x_ListInit(szTK),
    .prefs = prefs,
    .tkTST = initTk(),
    .isEOF = false,
    .x = 0,
    .y = 0,
    .indent = 0,
  };
}

ast_stSrcTree scanner_fnScanAndParseFiles(prefs_stPrefs* prefs){
  logging_stLog log = {.program = "xQScanner"};
  
  scanner_stScanner s = scanner_fnNewScanner(prefs);
  
  log.level = debug;
  log.msg = "init success\n";
  logging_fnLog(log, prefs->logLevel);
  
  /*
  { // Unsafe
    log.level = info;
    char* msg = malloc(sizeof(char*)*1024);
    sprintf(msg, "scanning and parsing file `%s` from directory `%s`\n", s.cFile, s.cBasePath);
    log.msg = msg;
    logging_fnLog(log, prefs->logLevel);
    free(msg);
  }
  */
    
  ast_stSrcTree tree = ast_fnNewSrcTree();
  
  puts(s.cText);
  
  tokens_stToken tok = tokens_fnNewToken(s.x, s.y, s.indent);
  
  x_List* cTkList = x_ListInit(szTK);
  
  while(!s.isEOF){
    char ch = *(s.cText+s.x+s.y);
    tokens_stCHMap chmap = {.val=ch};
    
    if(ch>=33 && ch<=126){
      if(ch>=48 && ch<=57){
        chmap.type = digit;
        tok.chMap->add(tok.chMap, &chmap);
      } else if(ch>=65 && ch<=90){
        chmap.type = ucLetter;
        tok.chMap->add(tok.chMap, &chmap);
      } else if(ch>=97 && ch<=122){
        chmap.type = lcLetter;
        tok.chMap->add(tok.chMap, &chmap);
      } else if(ch=='_'){
        chmap.type = letter;
        tok.chMap->add(tok.chMap, &chmap);
      } else {
        if(ch=='\"' || ch=='\'' || ch=='(' || ch==')' || ch==',' || ch==';' || ch=='[' || ch==']' || ch=='{' || ch=='}'){
          chmap.type = delimiter;
        } else {
          chmap.type = symbol;
        }
        
        tok.indent = s.indent;
        tokens_fnProcessToken(&tok, s.tkTST);
        
        if(tok.len != 0){
          cTkList->add(cTkList, &tok);
          s.tkList->add(s.tkList, &tok);
        }
        
        s.indent = 0;
        tok = tokens_fnNewToken(s.x, s.y, s.indent);
        
        tok.chMap->add(tok.chMap, &chmap);
        
        tok.indent = s.indent;
        tokens_fnProcessToken(&tok, s.tkTST);
        
        if(tok.len != 0){
          cTkList->add(cTkList, &tok);
          s.tkList->add(s.tkList, &tok);
        }
        
        s.indent = 0;
        tok = tokens_fnNewToken(s.x+1, s.y, s.indent);
      }
      s.x++;
    } else {
      chmap.type = unique;
      
      switch (ch) {
        case ' ':
          tok.indent = s.indent;
          tokens_fnProcessToken(&tok, s.tkTST);
          
          if(tok.len != 0){
            cTkList->add(cTkList, &tok);
            s.tkList->add(s.tkList, &tok);
          }
          
          s.indent = 0;
          tok = tokens_fnNewToken(s.x+1, s.y, s.indent);
          
          s.x++; break;
        case 9:
          tok.indent = s.indent;
          tokens_fnProcessToken(&tok, s.tkTST);
          
          if(tok.len != 0){
            cTkList->add(cTkList, &tok);
            s.tkList->add(s.tkList, &tok);
          }
          
          s.indent++;
          s.x++; break;
        case '\n':
          tok.indent = s.indent;
          tokens_fnProcessToken(&tok, s.tkTST);
          
          if(tok.len != 0){
            cTkList->add(cTkList, &tok);
            s.tkList->add(s.tkList, &tok);
          }
          
          s.indent = 0;
          tok = tokens_fnNewToken(s.x, s.y+1, s.indent);
          
          s.y++; break;
        case '\0':
          tok.indent = s.indent;
          tokens_fnProcessToken(&tok, s.tkTST);
          
          if(tok.len != 0){
            cTkList->add(cTkList, &tok);
            s.tkList->add(s.tkList, &tok);
          }
          
          s.isEOF = true; break;
        default:
          puts("Unknown character treating it like a whitespace");
          tok.indent = s.indent;
          tokens_fnProcessToken(&tok, s.tkTST);
          
          if(tok.len != 0){
            cTkList->add(cTkList, &tok);
            s.tkList->add(s.tkList, &tok);
          }
          
          s.indent = 0;
          tok = tokens_fnNewToken(s.x+1, s.y, s.indent);
          
          s.x++; break;
      }
    }
  }
  
  parser_fnParse(s.cFile, prefs->logLevel, &tree, cTkList);
  
  { // Unsafe
    log.level = debug;
    char* msg = malloc(sizeof(char*));
    sprintf(msg, "main parser returned code `%d`\n", tree.rc);
    log.msg = msg;
    logging_fnLog(log, prefs->logLevel);
    free(msg);
  }
  
  printf("%d\n", tree.type);
  
  return tree;
}