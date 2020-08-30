#ifndef XQC_X_H
#define XQC_X_H
#define _GNU_SOURCE

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

typedef struct {  
  int size;           /* Number of items in the list. */  
  int alloc_size;     /* Allocated size in quantity of items */  
  size_t item_size;   /* Size of each item in bytes. */  
  void *items;        /* Pointer to the list */  
} x_ListPriv;

typedef struct x_List {
  void (*add) (struct x_List *xl, void *o);
  void (*insert) (struct x_List *xl, void *o, int n);
  void (*replace) (struct x_List *xl, void *o, int n);
  void (*del) (struct x_List *xl, int n);
  void* (*at) (struct x_List *xl, int n);
  
  int (*realloc) (struct x_List *xl, int n);
  int (*f_idx) (struct x_List *xl, void *o);
  int (*l_idx) (struct x_List *xl, void *o);
  int (*size) (struct x_List *xl);
  
  void (*clear) (struct x_List *xl);
  void (*free) (struct x_List *xl);
  void (*print) (struct x_List *xl, int n, const char *type);
  
  x_ListPriv* priv;          /* RESTRICTED, private data */
} x_List;

x_List* x_ListInit(size_t size);

void* x_LoadFile(const char* path, size_t* nbytes);

#endif