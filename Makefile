##
## Makefile for  in /home/nasrat_v/rendu/tek2/malloc/PSU_2020_malloc
## 
## Made by Valentin Nasraty
## Login   <valentin.nasraty@epitech.eu>
## 
## Started on  Fri Feb  3 15:34:25 2017 Valentin Nasraty
## Last update Sun Feb 12 23:05:18 2017 Valentin Nasraty
##

SRC		=  malloc.c \
	   	   free.c \
		   realloc.c \
		   manage_bloc.c \
		   get_bloc.c \
		   copy.c \
		   thread_safe.c \
		   basic_func.c

NAME		= libmy_malloc.so

CFLAGS  	= -c -fpic -W -Wall -ansi -pedantic -std=gnu99 -lrt

CC		= cc

OBJ		= $(SRC:.c=.o)

all:		 $(NAME)
		make set
		make get

$(NAME):	$(OBJ)
		$(CC) -g -c -fpic $(SRC) $(CFLAGS) -lpthread -lrt

clean:
		rm -f $(OBJ) set get

fclean:		clean
		rm -f $(NAME)

re: 		fclean all

set:
		gcc -g -o set set.c *.o -lrt -lpthread

get:
		gcc -g -o get get.c *.o -lrt -lpthread
