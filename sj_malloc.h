/*
** malloc.h for malloc in /home/nasrat_v/rendu/tek2/malloc
**
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
**
** Started on  Fri Feb  3 08:50:24 2017 Valentin Nasraty
** Last update Sun Feb 12 23:05:53 2017 Valentin Nasraty
*/

#ifndef __SJ_MALLOC_H__
#define __SJ_MALLOC_H__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

extern void    	*base_bloc;
extern void     *heap_max;
extern void     *heap_min;
extern void     *prog_break;


typedef struct 	s_bloc
{
  struct s_bloc	*next;
  struct s_bloc	*prev;
  bool	       	isFree;
  size_t       	getSize;
  void	       	*data;
  char		just_for_align_header;
}	       	t_bloc;

# define __HEADER_SIZE__ sizeof(struct s_bloc)
# define __ALIGN_ADDR__(size, power) (((size - 1) / power + 1) * power)

/* __MALLOC__ */
void   		*sj_malloc(size_t size);
int sj_malloc_init();
int sj_malloc_fini();
void *sj_malloc_attach();

/* __FREE__ */
void   		sj_free(void *ptr);

/* __REALLOC__ */
void   		*sj_realloc(void *ptr, size_t size);
void   		*sj_realloc_func(t_bloc *bloc, void *ptr, size_t size);

/* __MANAGE_BLOC__ */
void   		sj_create_rest_bloc(t_bloc *bloc, size_t size, int pagesize);
t_bloc 		*sj_extend_heap(t_bloc *last_bloc, size_t size);
int    		sj_split_bloc(t_bloc *this_bloc, size_t size);
t_bloc 		*sj_fusion_free_bloc(t_bloc *bloc);

/* __GET_BLOC__ */
t_bloc 		*sj_find_free_bloc(t_bloc *bloc, size_t size);
void   		*sj_get_bloc(void *ptr);

/* __COPY__ */
void   		sj_copy_data(t_bloc *bloc, t_bloc *new_bloc);
t_bloc 		*sj_copy_bloc(t_bloc *bloc, size_t size);

/* __BASIC_FUNC__ */
void		my_putchar(char c);
int		my_strlen(char *str);
void		my_putstr(char *str);

/* __SHOW_ALLOC_MEM__ */
void		my_put_nbr(size_t nb);
void		my_put_hex(size_t nb);
void		show_alloc_mem();

/* __THREAD_SAFE__ */
void   		*trylock_thread();
void   		*unlock_thread();

#endif /* !__SJ_MALLOC_H__ */
