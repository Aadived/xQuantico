#include "../../include/x.h"

void* x_LoadFile(const char* path, size_t* nbytes) {
  int fd;
  if((fd = open(path, O_RDONLY, 0)) < 0){
    return NULL;
  }
  
  struct stat fs;
  if(fstat(fd, &fs) < 0){
    close(fd);
    return NULL;
  }
  
  size_t size = fs.st_size;
  if(nbytes!=NULL && *nbytes>0 && *nbytes<fs.st_size){
    size = *nbytes;
  }
  
  void *buf = malloc(size + 1);
  if(buf==NULL){
    close(fd);
    return NULL;
  }
  
  ssize_t count = read(fd, buf, size);
  close(fd);
  
  if(count!=size){
    free(buf);
    return NULL;
  }
  
  ((char *) buf)[count] = '\0';
  
  if(nbytes != NULL){
    *nbytes = count;
  }
  
  return buf;
}