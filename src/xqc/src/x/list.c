#include "../../include/x.h"

void x_ListAdd(x_List *xl, void *o);
void x_ListInsert(x_List *xl, void *o, int n);
void x_ListReplace(x_List *xl, void *o, int n);
void x_ListDel(x_List *xl, int n);
void* x_ListAt(x_List *xl, int n);

int x_ListRealloc(x_List *xl, int n);
int x_ListFIDX(x_List *xl, void *o);
int x_ListLIDX(x_List *xl, void *o);
int x_ListSize(x_List *xl);

void x_ListClear(x_List *xl);
void x_ListFree(x_List *xl);
void x_ListPrint(x_List *xl, int n, const char *type);

x_List* x_ListInit(size_t size){
  x_List *xl = malloc(sizeof(x_List));
  x_ListPriv *priv = malloc(sizeof(x_ListPriv));
  
  if(!xl || !priv){
    fprintf(stderr, "(x_List)[ERROR]: cannot allocate x_List!\n");
    return NULL;
  }
  
  priv->size = 0;
  priv->alloc_size = 0;
  priv->item_size = size;
  priv->items = NULL;
  
  xl->add = &x_ListAdd;
  xl->insert = &x_ListInsert;
  xl->replace = &x_ListReplace;
  xl->del = &x_ListDel;
  xl->at = &x_ListAt;
  
  xl->realloc = &x_ListRealloc;
  xl->f_idx = &x_ListFIDX;
  xl->l_idx = &x_ListLIDX;
  
  xl->size = &x_ListSize;
  xl->clear = &x_ListClear;
  xl->free = &x_ListFree;
  xl->print = &x_ListPrint;
  
  xl->priv = priv;
  
  return xl;
}

void x_ListAdd(x_List *xl, void *o){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  
  if(priv->size == priv->alloc_size && (x_ListRealloc(xl, priv->alloc_size*2) == 0)){
    return;
  }
  
  char *data = (char*) priv->items;
  data = data + priv->size * priv->item_size;
  memcpy(data, o, priv->item_size);
  priv->size++;
}

void x_ListInsert(x_List *xl, void *o, int n){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  
  if(n<0 || n>priv->size){
    fprintf(stderr, "(x_List)[ERROR]: insert position outside range - %d; n - %d.\n", priv->size, n);
    assert(n >= 0 && n <= priv->size);
    return;
  }

  if(priv->size == priv->alloc_size && x_ListRealloc(xl, priv->alloc_size * 2) == 0){
    return;
  }
  
  size_t step = priv->item_size;
  char *data = (char*) priv->items + n * step;
  memmove(data + step, data, (priv->size - n) * step);
  memcpy(data, o, step);
  priv->size++;
}

void x_ListReplace(x_List *xl, void *o, int n){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  
  if(n<0 || n>=priv->size){
    fprintf(stderr, "(x_List)[ERROR]: replace position outside range - %d; n - %d.\n", priv->size, n);
    assert(n >= 0 && n < priv->size);
    return;
  }

  char *data = (char*) priv->items;
  data = data + n * priv->item_size;
  memcpy(data, o, priv->item_size);
}

void x_ListDel(x_List *xl, int n){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  
  if(n<0 || n>=priv->size){
    fprintf(stderr, "(x_List)[ERROR]: remove position outside range - %d; n - %d.\n", priv->size, n);
    assert(n >= 0 && n < priv->size);
    return;
  }
  
  size_t step = priv->item_size;
  char *data = (char*)priv->items + n * step;
  memmove(data, data + step, (priv->size - n - 1) * step);
  priv->size--;
  
  if(priv->alloc_size > 3 * priv->size && priv->alloc_size >= 4){
    x_ListRealloc(xl, priv->alloc_size / 2);
  }
}

void* x_ListAt(x_List *xl, int n){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  
  if(n<0 || n>=priv->size){
    fprintf(stderr, "(x_List)[ERROR]: get position outside range - %d; n - %d.\n", priv->size, n);
    assert(n >= 0 && n < priv->size);
    return NULL;
  }

  char *data = (char*) priv->items;
  data = data + n * priv->item_size;
  return data;
}

int x_ListRealloc(x_List *xl, int n){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  if(n < priv->size){
    fprintf(stderr, "(x_List)[ERROR]: cannot realloc to '%i' size - count is '%i'\n", n, priv->size);
    assert(n >= priv->size);
    return 0;
  }
  
  if(n==0 && priv->alloc_size==0){
    n = 2;
  }
  
  void *ptr = realloc(priv->items, priv->item_size*n);
  
  if(!ptr){
    fprintf(stderr, "(x_List)[ERROR]: cannot reallocate memory!\n");
    return 0;
  }
  
  priv->items = ptr;
  priv->alloc_size = n;
  return 1;
}

int x_ListFIDX(x_List *xl, void *o){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  char *data = (char*) priv->items;
  size_t step = priv->item_size;
  size_t i = 0;
  int index = 0;
  for(; i < priv->size * step; i += step, index++){
    if(strncmp(data+i, o, step) == 0){
      return index;
    }
  }
  return -1;
}

int x_ListLIDX(x_List *xl, void *o){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  char *data = (char*) priv->items;
  size_t step = priv->item_size;
  int i = priv->size * step - step;
  int index = priv->size - 1;
  for(; i >= 0 ; i -= step, index--){
    if(strncmp(data+i, o, step) == 0){
      return index;
    }
  }
  return -1;
}

int x_ListSize(x_List *xl){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  return priv->size;
}

void x_ListClear(x_List *xl){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  free(priv->items);
  priv->items = NULL;
  priv->alloc_size = 0;
  priv->size = 0;
}

void x_ListFree(x_List *xl){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  free(priv->items);
  free(priv);
  free(xl);
  xl = NULL;
}

void x_ListPrint(x_List *xl, int n, const char *type){
  x_ListPriv *priv = (x_ListPriv*) xl->priv;
  printf("\n(x_List)[DEBUG]:  size = %i   item_size = %zu  alloc_size = %i \n", priv->size, priv->item_size, priv->alloc_size);
  
  if(n>0){
    n = (n > priv->size) ? priv->size : n;
    char *data = NULL;
    int i = 0;
    for(; i < n; i++){
      data = (char*) priv->items + i * priv->item_size;
      if(type==NULL) printf("%p  ", data);
      else if (strcmp(type, "char") == 0) printf("%c ", *(char*) data);
      else if (strcmp(type, "short") == 0) printf("%hi  ", *(short*) data);
      else if (strcmp(type, "int") == 0) printf("%i  ", *(int*) data);
      else if (strcmp(type, "long") == 0) printf("%li  ", *(long*) data);
      else if (strcmp(type, "uintptr_t") == 0) printf("%zx  ", (uintptr_t*) data);
      else if (strcmp(type, "size_t") == 0) printf("%zu  ", *(size_t*) data);
      else if (strcmp(type, "double") == 0) printf("%f  ", *(double*) data);
      else if (strcmp(type, "string") == 0) printf("%s\n", data);
      else { printf("Unknown type."); break; }
    }
    printf("\n\n");
  }
}