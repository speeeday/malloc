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
  sj_malloc_init();

  
  struct pts_t *p1 = sj_malloc(sizeof(struct pts_t));
  struct pts_t *p2 = sj_malloc(sizeof(struct pts_t));
  struct pts_t *p3 = sj_malloc(sizeof(struct pts_t));
  struct pts_t *p4 = sj_malloc(sizeof(struct pts_t));
  struct pts_t *p5 = sj_malloc(sizeof(struct pts_t));
  struct pts_t *p6 = sj_malloc(sizeof(struct pts_t));

  fprintf(stdout, "p1: %p\n", p1);
  
  const char *name1 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  const char *name2 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  const char *name3 = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
  const char *name4 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
  const char *name5 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  const char *name6 = "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD";
  const char *name7 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  const char *name8 = "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
  const char *name9 = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
  
  char *n1 = sj_malloc(strlen(name1)+1);
  char *n2 = sj_malloc(strlen(name2)+1);
  char *n3 = sj_malloc(strlen(name3)+1);
  sj_free(n2);
  char *n4 = sj_malloc(strlen(name4)+1);
  char *n5 = sj_malloc(strlen(name5)+1);
  char *n6 = sj_malloc(strlen(name6)+1);
  sj_free(n5);
  char *n7 = sj_malloc(strlen(name7)+1);
  sj_free(n7);
  char *n8 = sj_malloc(strlen(name8)+1);
  char *n9 = sj_malloc(strlen(name9)+1);

  strcpy(n1, name1);
  strcpy(n3, name3);
  strcpy(n4, name4);
  strcpy(n6, name6);
  strcpy(n8, name8);
  strcpy(n9, name9);


  p1->name = n1;
  p1->next = p2;

  p2->name = n3;
  p2->next = p3;

  p3->name = n4;
  p3->next = p4;

  p4->name = n6;
  p4->next = p5;

  p5->name = n8;
  p5->next = p6;

  p6->name = n9;
  p6->next = NULL;

    
  
  fprintf(stdout, "sleeping...\n");
  if (argc < 2) {
    sleep(5);
  }
  else {
    sleep(atoi(argv[1]));
  }
  sj_malloc_fini();
  return 0;
}
