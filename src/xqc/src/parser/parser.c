#include "../../include/parser.h"

#define TOK tokens_stToken*

tokens_stToken* getTk(x_List* tkList, int i){
  return (tokens_stToken*) tkList->at(tkList, i);
}

void parser_fnParse(char* file, logging_eLevel lvl, ast_stSrcTree* tree, x_List* tkList){
  logging_stLog log = {.program = "xQParser"};
  
  log.level = debug;
  log.msg = "init success\n";
  logging_fnLog(log, lvl);
  
  int l_sz = tkList->size(tkList), i = 0;
  
  TOK pTK = NULL;
  
  while(i<l_sz){
    
    TOK cTK = getTk(tkList, i);
    if(i==0){
      pTK = cTK;
    }
    //printf("%s - %d - %d\n", tk->val, tk->len, tk->type);
    
    if(cTK->type==KW_module){
      if(i+1<l_sz){
        TOK nTK = getTk(tkList, i+1);
        if(cTK->y==nTK->y){
          if(cTK->x==0 && cTK->y==0 && cTK->indent==0){
            if(!strcmp(nTK->val, "main")){
              log.level = info;
              log.msg = "module mode detected\n";
              logging_fnLog(log, lvl);
              tree->type = mod;
            } else {
              if(nTK->type==SCOLON){
                printf("\n  %s:(Line: %d)[ERROR]: module name missing provide a valid module name if you want to use module mode else use the default script mode by removing all occurences of this pattern from the Main Source File: `module (main|SomeModuleName)[;]\n", file, cTK->y);
              } else {
                printf("\n  %s:(Line: %d)[ERROR]: invalid module name`%s` for Main Source File it must be `main` if you want to use module mode else use the default script mode by removing all occurences of this pattern from the Main Source File: `module (main|SomeModuleName)[;]`\n", file, cTK->y, nTK->val);
                printf("\n  \tmodule %s\n  \t       ^~~~", nTK->val);
              }
            }
          } else {
            if(nTK->type==SCOLON){
              printf("\n  %s:(Line: %d)[ERROR]: module name missing provide a valid module name also make sure module declaration must be at start of code file if you want to use module mode else use the default script mode by removing all occurences of this pattern from the Main Source File: `module (main|SomeModuleName)[;]\n", file, cTK->y);
            } else {
              printf("\n  %s:(Line: %d)[ERROR]: module declaration must be at start of code file if you want to use module mode else use the default script mode by removing all occurences of this pattern from the Main Source File: `module (main|SomeModuleName)[;]\n", file, cTK->y);
              printf("\n\tmodule %s\n  \t^~~~", nTK->val);
            }
          }
        } else {
          printf("\n  %s:(Line: %d)[ERROR]: module name missing provide valid module name if you want to use module mode else use the default script mode by removing all occurences of this pattern from the Main Source File: `module (main|SomeModuleName)[;]\n", file, cTK->y);
          i--;
        }
        i++;
      } else {
        printf("\n  %s:(Line: %d)[ERROR]: module name missing provide valid module name if you want to use module mode else use the default script mode by removing all occurences of this pattern from the Main Source File: `module (main|SomeModuleName)[;]\n", file, cTK->y);
      }
    }
    
    i++; pTK = cTK;
  }
  return;
}

