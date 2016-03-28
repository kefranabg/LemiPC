/*
** error.c for error.c in /home/loeb_t/rendu/PSU_2013_lemipc
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Wed Mar 19 19:05:38 2014 LOEB Thomas
** Last update Wed Mar 19 19:06:26 2014 LOEB Thomas
*/

#include		"lemipc.h"

int			lemipc_error(char *message)
{
  fprintf(stderr, "%s\n", message);
  return (EXIT_FAILURE);
}

int			lemipc_perror(char *message)
{
  perror(message);
  return (EXIT_FAILURE);
}
