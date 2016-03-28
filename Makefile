##
## Makefile for Makefile in /home/loeb_t/rendu/PSU_2013_lemipc
## 
## Made by LOEB Thomas
## Login   <loeb_t@epitech.net>
## 
## Started on  Sat Mar 22 13:17:49 2014 LOEB Thomas
## Last update Sun Mar 23 16:02:42 2014 abgral_f
##

PROG	= lemipc

F_PROG	= f_$(PROG)/

GUI	= graphic

F_GUI	= f_$(GUI)/

all: $(PROG) $(GUI)

$(PROG):
	make -C $(F_PROG) all
	cp $(F_PROG)$(PROG) .

$(GUI):
	make -C $(F_GUI) all
	cp $(F_GUI)$(GUI) .

clean:
	make -C $(F_PROG) clean
	make -C $(F_GUI) clean

fclean:
	rm -f $(PROG)
	rm -f $(GUI)
	make -C $(F_PROG) fclean
	make -C $(F_GUI) fclean

re: fclean all
