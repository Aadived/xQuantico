#include "../../include/tokens.h"

struct TkNode* newNode(char ch){
  struct TkNode* temp = (struct TkNode*) malloc(sizeof(struct TkNode)); 
  temp->ch = ch;
  temp->isEoS = 0;
  temp->l = temp->m = temp->r = NULL;
  
  return temp;
};

void insertTk(struct TkNode** root, char* word, tokens_eType val){
  if(!(*root)){
    *root = newNode(*word);
  }
  
  if((*word)<(*root)->ch){
    insertTk(&((*root)->l), word, val);
  } else if((*word)>(*root)->ch){
    insertTk(&((*root)->r), word, val);
  } else {
    if(*(word+1)){
      insertTk(&((*root)->m), word+1, val);
    } else {
      (*root)->isEoS = 1;
      (*root)->val = val;
    }
  }
};

void iterTkTST(struct TkNode* root, char* kBuf, int depth){
  if(root){
    iterTkTST(root->l, kBuf, depth);
    kBuf[depth] = root->ch;
    
    if(root->isEoS){
      kBuf[depth+1] = '\0';
      tokens_eType val = root->val;
      printf( "%s - %d\n", kBuf, val);
    }
    
    iterTkTST(root->m, kBuf, depth + 1);
    iterTkTST(root->r, kBuf, depth);
  }
};

void traverseTkTST(struct TkNode* root){
  char kBuf[50];
  iterTkTST(root, kBuf, 0);
};

tokens_eType searchTk(struct TkNode *root, char *word){
  if(!root){
    return unknown;
  }
  
  if(*word < (root)->ch){
    return searchTk(root->l, word);
  } else if(*word > (root)->ch){
    return searchTk(root->r, word);
  } else {
    if(*(word+1) == '\0'){
      return root->val;
    } else {
      return searchTk(root->m, word+1);
    }
  }
};

struct TkNode* initTk(){
  struct TkNode* root = NULL;
  
  insertTk(&root, "+", PLUS);
  insertTk(&root, "++", DPLUS);
	insertTk(&root, "-", MINUS);
	insertTk(&root, "--", DMINUS);
	insertTk(&root, "*", STAR);
	insertTk(&root, "**", DSTAR);
	insertTk(&root, "/", SLASH);
	insertTk(&root, "//", DSLASH);
	insertTk(&root, "%", PERCENT);
	insertTk(&root, "^", CARET);
	insertTk(&root, "!", NOT);
	insertTk(&root, "&", AND);
	insertTk(&root, "|", PIPE);
	insertTk(&root, "&&", DAND);
	insertTk(&root, "||", DPIPE);
	insertTk(&root, "<<", SHL);
	insertTk(&root, ">>", SHR);
	insertTk(&root, "+=", PLUSEQ);
	insertTk(&root, "-=", MINUSEQ);
	insertTk(&root, "*=", STAREQ);
	insertTk(&root, "/=", SLASHEQ);
	insertTk(&root, "%=", PERCENTEQ);
	insertTk(&root, "^=", CARETEQ);
	insertTk(&root, "&=", ANDEQ);
	insertTk(&root, "|=", OREQ);
	insertTk(&root, "<<=", SHLEQ);
	insertTk(&root, ">>=", SHREQ);
	insertTk(&root, "=", EQ);
	insertTk(&root, "==", EQEQ);
	insertTk(&root, ":=", DECEQ);
	insertTk(&root, "!=", NOTEQ);
	insertTk(&root, ">", GT);
	insertTk(&root, ">=", GTEQ);
	insertTk(&root, "<", LT);
	insertTk(&root, "<=", LTEQ);
	insertTk(&root, "@", AT);
	insertTk(&root, ".", DOT);
	insertTk(&root, "..", DDOT);
	insertTk(&root, "...", TDOT);
	insertTk(&root, ",", COMMA);
	insertTk(&root, ";", SCOLON);
	insertTk(&root, ":", COLON);
	insertTk(&root, "::", DCOLON);
	insertTk(&root, "->", FARROW);
	insertTk(&root, "<-", BARROW);
	insertTk(&root, "<=>", DARROW);
	insertTk(&root, "=>", SARROW);
	insertTk(&root, "#", HASH);
	insertTk(&root, "$", DOLLAR);
	insertTk(&root, "?", QMARK);
	insertTk(&root, "~", TILDE);
	insertTk(&root, "`", BTICK);
	insertTk(&root, "{", LCBR);
	insertTk(&root, "}", RCBR);
	insertTk(&root, "(", LPAR);
	insertTk(&root, ")", RPAR);
	insertTk(&root, "[", LSBR);
	insertTk(&root, "]", RSBR);
	
	// KW_BEGIN
	insertTk(&root, "abstract", KW_abstract);
	insertTk(&root, "and", KW_and);
	insertTk(&root, "as", KW_as);
	insertTk(&root, "asm", KW_asm);
	insertTk(&root, "assert", KW_assert);
	insertTk(&root, "async", KW_asynchronous);
	insertTk(&root, "auto",	KW_auto);
	insertTk(&root, "await", KW_await);
	insertTk(&root, "any", KW_any);
	insertTk(&root, "alias", KW_alias);
	insertTk(&root, "align", KW_align);
	insertTk(&root, "break", KW_break);
	insertTk(&root, "become", KW_become);
	insertTk(&root, "case", KW_case);
	insertTk(&root, "const", KW_constant);
	insertTk(&root, "continue", KW_continue);
	insertTk(&root, "catalyst", KW_catalyst);
	insertTk(&root, "do", KW_do);
	insertTk(&root, "dyn", KW_dynamic);
	insertTk(&root, "dynamic", KW_dynamic);
	insertTk(&root, "default", KW_default);
	insertTk(&root, "defer", KW_defer);
	insertTk(&root, "del", KW_delete);
	insertTk(&root, "delete", KW_delete);
	insertTk(&root, "else", KW_else);
	insertTk(&root, "enum", KW_enumerate);
	insertTk(&root, "enumerate", KW_enumerate);
	insertTk(&root, "export", KW_export);
	insertTk(&root, "extern", KW_extern);
	insertTk(&root, "extend", KW_extends);
	insertTk(&root, "except", KW_except);
	insertTk(&root, "expect", KW_expect);
	insertTk(&root, "false", KW_false);
	insertTk(&root, "False", KW_false);
	insertTk(&root, "final", KW_final);
	insertTk(&root, "finally", KW_finally);
	insertTk(&root, "for", KW_for);
	insertTk(&root, "from", KW_from);
	insertTk(&root, "fn", KW_function);
	insertTk(&root, "fun", KW_function);
	insertTk(&root, "func", KW_function);
	insertTk(&root, "function", KW_function);
	insertTk(&root, "global", KW_global);
	insertTk(&root, "goto", KW_goto);
	insertTk(&root, "if", KW_if);
	//KW_implicit
	insertTk(&root, "implies", KW_implies);
	insertTk(&root, "import", KW_import);
	insertTk(&root, "in", KW_in);
	insertTk(&root, "init", KW_init);
	// KW_interface
	insertTk(&root, "is", KW_is);
	// KW_kill
	// KW_lambda
	// KW_lazy
	insertTk(&root, "let", KW_let);
	insertTk(&root, "loop", KW_loop);
	// KW_match
	insertTk(&root, "mod", KW_module);
	insertTk(&root, "module", KW_module);
	// KW_move
	insertTk(&root, "mut", KW_mutable);
	insertTk(&root, "mutable", KW_mutable);
	//KW_new,           // +123
	insertTk(&root, "nil", KW_none);
	insertTk(&root, "Nil", KW_none);
	insertTk(&root, "none", KW_none);
	insertTk(&root, "None", KW_none);
	insertTk(&root, "null", KW_none);
	insertTk(&root, "Null", KW_none);
	insertTk(&root, "not", KW_not);
	//KW_object,        // +126
	//KW_operator,      // +127
	insertTk(&root, "or", KW_or);
	//KW_override,      // +129
	//KW_private,       // +130
	//KW_protected,     // +131
	//KW_public,        // +132
	//KW_raise,         // +133
	//KW_reference,     // +134
	//KW_register,      // +135
	//KW_requires,      // +136
	insertTk(&root, "ret", KW_return);
	insertTk(&root, "return", KW_return);
	//KW_select,        // +138
	//KW_self,          // +139
	//KW_sizeof,        // +140
	//KW_skip,          // +141
	//KW_static,        // +142
	insertTk(&root, "struct", KW_struct);
	//KW_super,         // +144
	insertTk(&root, "switch", KW_switch);
	insertTk(&root, "sync", KW_synchronous);
	insertTk(&root, "templ", KW_template);
	insertTk(&root, "template", KW_template);
	//KW_this,          // +148
	//KW_trait,         // +149
	insertTk(&root, "true", KW_true);
	insertTk(&root, "True", KW_true);
	//KW_try,           // +151
	insertTk(&root, "type", KW_type);
	//KW_typeof,        // +153
	//KW_unsafe,        // +154
	//KW_unsized,       // +155
	//KW_use,           // +156
	//KW_using,         // +157
	insertTk(&root, "var", KW_variable);
	insertTk(&root, "variable", KW_variable);
	//KW_value,         // +159
	//KW_virtual,       // +160
	//KW_volatile,      // +162
	//KW_was,           // +163
	//KW_what,          // +164
	//KW_when,          // +165
	//KW_where,         // +166
	insertTk(&root, "while", KW_while);
	//KW_with,          // +168
	//KW_yield,
  
  //traverseTkTST(root);
  
  return root;
};

tokens_stToken tokens_fnNewToken(int x, int y, int ind){
  return (tokens_stToken){
    .type = unknown,
    .chMap = x_ListInit(sizeof(tokens_stCHMap)),
    .x = x,
    .y = y,
    .indent = ind,
  };
};

void tokens_fnProcessToken(tokens_stToken* tok, struct TkNode* tkTST){
  int l_sz = tok->chMap->size(tok->chMap);
  
  tok->len = l_sz;
  tok->x -= tok->indent;
  tok->val = (char*)malloc(sizeof(char)*l_sz);
  
  tokens_eCHType T;
  
  for(int i=0;i<l_sz;i++){
    tokens_stCHMap* ch = (tokens_stCHMap*) tok->chMap->at(tok->chMap, i);
    
    tok->val[i] = ch->val;
    if(i==0){
      T = ch->type;
      
      if(T==digit){
        tok->type = NUMBER;
      } else if(T==letter || T==ucLetter || T==lcLetter){
        tok->type = IDENT;
      }
    }
  }
  
  tok->val[l_sz] = '\0';
  
  if(tok->len != 0){
    tokens_eType t = searchTk(tkTST, tok->val);
    
    if(t != unknown){
      tok->type = t;
    }
    
    //printf("%s - %d - %d (%d, %d, %d)\n", tok->val, tok->len, tok->type, tok->x, tok->y, tok->indent);
  }
  
  return;
};