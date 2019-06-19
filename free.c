/*
** free.c for free in /home/nasrat_v/rendu/tek2/sj_malloc/PSU_2020_sj_malloc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Feb  5 17:28:11 2017 Valentin Nasraty
** Last update Sun Feb 12 14:57:28 2017 Valentin Nasraty
*/

#include "sj_malloc.h"

void *base_bloc;
void *prog_break;

void sj_free(void *ptr)
{
  t_bloc *bloc;

  trylock_thread();
  if (ptr == NULL || (bloc = sj_get_bloc(ptr)) == NULL)
    {
      unlock_thread();
      return;
    }
  if (bloc->data == ptr && bloc->isFree == false)
    {
      bloc->isFree = true;
      bloc = sj_fusion_free_bloc(bloc);
      if (bloc == base_bloc && bloc->next == NULL)
	{
	  prog_break = (char*)bloc + getpagesize();
	  base_bloc = NULL;
	}
    }
  unlock_thread();
}
