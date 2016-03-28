##
## Makefile for Makefile in /home/loeb_t/rendu/PSU_2013_lemipc
## 
## Made by LOEB Thomas
## Login   <loeb_t@epitech.net>
## 
## Started on  Wed Mar 19 14:51:36 2014 LOEB Thomas
## Last update Sun Mar 23 16:02:55 2014 abgral_f
##

NAME	= lemipc

F_SRC	= src/

F_INC	= inc/

SRC	= $(F_SRC)lemipc.c		\
	  $(F_SRC)launch_player.c	\
	  $(F_SRC)check_player.c	\
	  $(F_SRC)algorithm.c		\
	  $(F_SRC)random.c		\
	  $(F_SRC)error.c		\
	  $(F_SRC)msgq.c		\
	  $(F_SRC)coord.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Werror -Wextra -I $(F_INC)

MATH	= -lm

all: $(NAME)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ) $(MATH)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
