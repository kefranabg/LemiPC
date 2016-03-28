/*
** error.c for error.c in /home/loeb_t/rendu/PSU_2013_lemipc/f_graphic
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Sat Mar 22 13:46:24 2014 LOEB Thomas
** Last update Sat Mar 22 13:47:13 2014 LOEB Thomas
*/

#include		"graphic.h"

int			graphic_error(char *message)
{
  fprintf(stderr, "%s\n", message);
  return (EXIT_FAILURE);
}

int			graphic_perror(char *message)
{
  perror(message);
  return (EXIT_FAILURE);
}
