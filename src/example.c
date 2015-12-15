#include <stdio.h>
#include <string.h>
#include "mem_pool/mem_pool.h"

int main(int argc,char *argv[])
{

  mem_pool p;
  mem_pool_create(&p,4,4);
  int *d=mem_pool_alloc(&p);
  *d=32;
  printf("%d\n",*d);
  float *f=mem_pool_alloc(&p);
  *f=312.5;
  printf("%f\n",*f);
  char *s=mem_pool_alloc(&p);
  strcpy(s,"hiz");
  printf("%s\n",s);
  mem_pool_free(&p,d);
  mem_pool_free(&p,f);
  mem_pool_free(&p,s);
  mem_pool_destroy(&p);
  
  
  return 0;
}
