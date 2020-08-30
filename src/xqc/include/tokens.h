#ifndef XQC_TOKENS_H
#include "x.h"

#include "logging.h"
#define XQC_TOKENS_H

typedef enum tokens_eType {
  unknown,          // 
	EoF,              // +1
	IDENT,            // +2
	NUMBER,           // +3
	STRING,           // +4
	STRPART,          // +5
	CHARTK,           // +6
	
	PLUS,             // +7  (+)
	DPLUS,            // +8  (++)
	MINUS,            // +9  (-)
	DMINUS,           // +10 (--)
	STAR,             // +11 (*)
	DSTAR,            // +12 (**)
	SLASH,            // +13 (/)
	DSLASH,           // +14 (//)
	PERCENT,          // +15 (%)
	CARET,            // +16 (^)
	NOT,              // +17 (!)
	AND,              // +18 (&)
	PIPE,             // +19 (|)
	DAND,             // +20 (&&)
	DPIPE,            // +21 (||)
	SHL,              // +22 (<<)
	SHR,              // +23 (>>)
	PLUSEQ,           // +24 (+=)
	MINUSEQ,          // +25 (-=)
	STAREQ,           // +26 (*=)
	SLASHEQ,          // +27 (/=)
	PERCENTEQ,        // +28 (%=)
	CARETEQ,          // +29 (^=)
	ANDEQ,            // +30 (&=)
	OREQ,             // +31 (|=)
	SHLEQ,            // +32 (<<=)
	SHREQ,            // +33 (>>=)
	EQ,               // +34 (=)
	EQEQ,             // +35 (==)
	DECEQ,            // +36 (:=)
	NOTEQ,            // +37 (!=)
	GT,               // +38 (>)
	GTEQ,             // +39 (>=)
	LT,               // +40 (<)
	LTEQ,             // +41 (<=)
	AT,               // +42 (@)
	USCR,             // +43 (_)
	DOT,              // +44 (.)
	DDOT,             // +45 (..)
	TDOT,             // +46 (...)
	COMMA,            // +47 (,)
	SCOLON,           // +48 (;)
	COLON,            // +49 (:)
	DCOLON,           // +50 (::)
	FARROW,           // +51 (->)
	BARROW,           // +52 (<-)
	DARROW,           // +53 (<=>)
	SARROW,           // +54 (=>)
	HASH,             // +55 (#)
	DOLLAR,           // +56 ($)
	QMARK,            // +57 (?)
	TILDE,            // +58 (~)
	BTICK,            // +59 (`)
	LCBR,             // +60 ( { )
	RCBR,             // +61 ( } )
	LPAR,             // +62 ( ( )
	RPAR,             // +63 ( ) )
	LSBR,             // +64 ( [ )
	RSBR,             // +65 ( ] )
	COMMENT,          // +66
	NEWLINE,          // +67
	
	KW_BEGIN,         // +68
	KW_abstract,      // +69
	KW_and,           // +70
	KW_as,            // +71
	KW_asm,           // +72
	KW_assert,        // +73
	KW_asynchronous,  // +74
	KW_auto,          // +75
	KW_await,         // +76
	KW_any,           // +77
	KW_alias,         // +78
	KW_align,         // +79
	KW_break,         // +80
	KW_become,        // +81
	KW_case,          // +82
	KW_constant,      // +83
	KW_continue,      // +84
	KW_catalyst,      // +85
	KW_do,            // +86
	KW_dynamic,       // +87
	KW_default,       // +88
	KW_defer,         // +89
	KW_delete,        // +90
	KW_else,          // +91
	KW_enumerate,     // +92
	KW_export,        // +93
	KW_extern,        // +94
	KW_extends,       // +95
	KW_except,        // +96
	KW_expect,        // +97
	KW_false,         // +98
	KW_final,         // +99
	KW_finally,       // +100
	KW_for,           // +101
	KW_from,          // +102
	KW_function,      // +103
	KW_global,        // +104
	KW_goto,          // +105
	KW_if,            // +106
	KW_implicit,      // +107
	KW_implies,       // +108
	KW_import,        // +109
	KW_in,            // +110
	KW_init,          // +111
	KW_interface,     // +112
	KW_is,            // +113
	KW_kill,          // +114
	KW_lambda,        // +115
	KW_lazy,          // +116
	KW_let,           // +117
	KW_loop,          // +118
	KW_match,         // +119
	KW_module,        // +120
	KW_move,          // +121
	KW_mutable,       // +122
	KW_new,           // +123
	KW_none,          // +124
	KW_not,           // +125
	KW_object,        // +126
	KW_operator,      // +127
	KW_or,            // +128
	KW_override,      // +129
	KW_private,       // +130
	KW_protected,     // +131
	KW_public,        // +132
	KW_raise,         // +133
	KW_reference,     // +134
	KW_register,      // +135
	KW_requires,      // +136
	KW_return,        // +137
	KW_select,        // +138
	KW_self,          // +139
	KW_sizeof,        // +140
	KW_skip,          // +141
	KW_static,        // +142
	KW_struct,        // +143
	KW_super,         // +144
	KW_switch,        // +145
	KW_synchronous,   // +146
	KW_template,      // +147
	KW_this,          // +148
	KW_trait,         // +149
	KW_true,          // +150
	KW_try,           // +151
	KW_type,          // +152
	KW_typeof,        // +153
	KW_unsafe,        // +154
	KW_unsized,       // +155
	KW_use,           // +156
	KW_using,         // +157
	KW_variable,      // +158
	KW_value,         // +159
	KW_virtual,       // +160
	KW_void,          // +161
	KW_volatile,      // +162
	KW_was,           // +163
	KW_what,          // +164
	KW_when,          // +165
	KW_where,         // +166
	KW_while,         // +167
	KW_with,          // +168
	KW_yield,         // +169
	KW_END,           // +170
	
	// for future: embed,shared,lock,rlock,likely,unlikely,offsetof,union,
} tokens_eType;

struct TkNode {
  char ch;
  tokens_eType val;
  
  bool isEoS;
  
  struct TkNode *l, *m, *r;
};

struct TkNode* newNode(char ch);

void insertTk(struct TkNode** root, char* word, tokens_eType val);

void iterTkTST(struct TkNode* root, char* kBuf, int depth);

void traverseTkTST(struct TkNode* root);

tokens_eType searchTk(struct TkNode *root, char *word);

struct TkNode* initTk();

typedef enum tokens_eCHType {
  unique,
  digit,
  ucLetter,
  lcLetter,
  letter,
  alphanum,
  delimiter,
  symbol,
  mixed,
} tokens_eCHType;

typedef struct tokens_stToken tokens_stToken;

typedef struct tokens_stCHMap {
  char val;
  tokens_eCHType type;
} tokens_stCHMap;

struct tokens_stToken {
  tokens_eType type;
  x_List* chMap;
  char* val;
  int x;
  int y;
  int indent;
  int len;
};

tokens_stToken tokens_fnNewToken(int x, int y, int ind);
void tokens_fnProcessToken(tokens_stToken* tk, struct TkNode* tkTST);

#endif