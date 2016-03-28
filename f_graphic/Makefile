##
## Makefile for Makefile in /home/loeb_t/rendu/PSU_2013_lemipc
## 
## Made by LOEB Thomas
## Login   <loeb_t@epitech.net>
## 
## Started on  Wed Mar 19 14:51:36 2014 LOEB Thomas
## Last update Sat Mar 22 13:46:21 2014 LOEB Thomas
##

NAME	= graphic

F_SRC	= src/

F_INC	= inc/

SRC	= $(F_SRC)graphic.c		\
	  $(F_SRC)error.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Werror -Wextra -I $(F_INC)

SDL	= -lSDL

all: $(NAME)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ) $(SDL)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
