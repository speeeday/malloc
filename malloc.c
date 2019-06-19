/*
**
** Made by Valentin Nasraty
** Edited by Sanjay Chandrasekaran
**
*/

#include "sj_malloc.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STORAGE_ID "/SHM_TEST"
#define HEAP_SIZE (500 * (1 << 20))

void *base_bloc = NULL;
void *prog_break;
void *heap_min;
void *heap_max;

int sj_malloc_init() {
  
  int fd;
  int res;
  
  //initialize prog_break and heap_max, create shared mem heap

  // get shared memory file descriptor (NOT a file)
  fd = shm_open(STORAGE_ID, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    perror("open");
    return 10;
  }

  // extend shared memory object as by default it's initialized with size 0
  res = ftruncate(fd, HEAP_SIZE);
  if (res == -1) {
    perror("ftruncate");
    return 20;
  }

  // map shared memory to process address space
  void *addr = mmap(NULL, HEAP_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED) {
    perror("mmap");
    return 30;
  }

  fprintf(stdout, "Mapped Shared Memory Address: %p\n", addr);

  heap_min = addr;
  heap_max = (void *)((char *)addr + HEAP_SIZE);  

  *((t_bloc **)(addr)) = addr;
  addr = (void *)(((char *)(addr)) + 16);

  prog_break = addr;

  
  return 0;
  
}

// returns a ptr to the start of the shared memory area
// read the ptr at this addr to know the base address used when data was first written
// compute the delta with both these values and use that whenever dereferencing a ptr
void *sj_malloc_attach() {

  int fd;
  
  // get shared memory file descriptor (NOT a file)
  fd = shm_open(STORAGE_ID, O_RDONLY, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    perror("open");
    return NULL;
  }
  
  void *addr = mmap(NULL, HEAP_SIZE, PROT_READ, MAP_SHARED, fd, 0);
  
  if (addr == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }

  fprintf(stdout, "Mapped Shared Memory Address: %p\n", addr);

  return addr;
  
}

int sj_malloc_fini() {
  // mmap cleanup
  int res = munmap(heap_min, HEAP_SIZE);
  if (res == -1)
    {
      perror("munmap");
      return 40;
    }
  
  // shm_open cleanup
  int fd = shm_unlink(STORAGE_ID);
  if (fd == -1)
    {
      perror("unlink");
      return 100;
    }
  return 0;
}

void *sj_malloc(size_t size)
{
  t_bloc *this_bloc;

  trylock_thread();
  if ((long int)size < 0)
    return (unlock_thread());
  size = __ALIGN_ADDR__(size, 16);
  if ((this_bloc = sj_find_free_bloc(base_bloc, size)) != NULL)
    {
      if (sj_split_bloc(this_bloc, size) == 1)
	{
	  if ((this_bloc = sj_extend_heap(base_bloc, size)) == NULL)
	    return (unlock_thread());
	}
    }
  else
    {
      if ((this_bloc = sj_extend_heap(base_bloc, size)) == NULL)
	return (unlock_thread());
    }
  if (base_bloc == NULL)
    base_bloc = this_bloc;
  unlock_thread();
  return (this_bloc->data);
}
