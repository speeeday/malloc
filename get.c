#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "sj_malloc.h"
#include "set.h"

#define STORAGE_ID "/SHM_TEST"

int main(int argc, char *argv[])
{

  t_bloc **addr = (t_bloc **)sj_malloc_attach();
  void *otheraddr = (void *)(*(addr));
  void *myaddr = (void *)addr;

  unsigned long mydelta = myaddr - otheraddr;

#define DELTA(p) ((void *)(((char *)(p))+mydelta))
  
  t_bloc *addrr = (t_bloc *)(((char *)(addr)) + 16);
  
  struct pts_t *cur = (struct pts_t *)(addrr->data);
  
  while (cur != NULL) {
    cur = DELTA(cur);
    fprintf(stdout, "%s\n", (char *)DELTA(cur->name));
    //fprintf(stdout, "Computed %p from %p with delta of %lx\n", DELTA(cur->next), cur->next, mydelta);
    cur = cur->next;
  }
  
  return 0;
}
