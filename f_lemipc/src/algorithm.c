/*
** algorithm.c for algorithm.c in /home/abgral_f/rendu/PSU_2013_lemipc/src
**
** Made by abgral_f
** Login   <abgral_f@epitech.net>
**
** Started on  Fri Mar 21 18:19:38 2014 abgral_f
** Last update Thu Mar 27 18:47:17 2014 LOEB Thomas
*/

#include		"lemipc.h"

static bool		is_in_perim(int pos_ennemy, int pos_ally, int perim)
{
  int			y;
  int			x;

  y = pos_ennemy / WIN_SIZE_X - perim / 2;
  while (y != pos_ennemy / WIN_SIZE_X + perim / 2)
    {
      x = pos_ennemy % WIN_SIZE_X - perim / 2;
      while (x != pos_ennemy % WIN_SIZE_X + perim / 2)
	if (x + y * WIN_SIZE_X == pos_ally)
	  return (TRUE);
	else
	  x++;
      y++;
    }
  return (FALSE);
}

static bool		is_common_ally(int pos_ennemy, t_lemipc *lemipc, int perim)
{
  int			y;
  int			x;

  y = lemipc->pos / WIN_SIZE_X - perim / 2;
  while (y != (int)lemipc->pos / WIN_SIZE_X + perim / 2)
    {
      x = lemipc->pos % WIN_SIZE_X - perim / 2;
      while (x != (int)lemipc->pos % WIN_SIZE_X + perim / 2)
	if (x >= 0 && x < WIN_SIZE_X && y >= 0 && y < WIN_SIZE_Y
	    && lemipc->map[x + y * WIN_SIZE_X] == lemipc->no_team
	    && (x + y * WIN_SIZE_X) != (int)lemipc->pos
	    && is_in_perim(pos_ennemy, x + y * WIN_SIZE_X, perim) == TRUE)
	  return (TRUE);
	else
	  ++x;
      ++y;
    }
  return (FALSE);
}

static int		check_ennemy_to_attack(t_lemipc *lemipc, int perim)
{
  int			y;
  int			x;

  y = lemipc->pos / WIN_SIZE_X - perim / 2;
  while (y != (int)lemipc->pos / WIN_SIZE_X + perim / 2)
    {
      x = lemipc->pos % WIN_SIZE_X - perim / 2;
      while (x != (int)lemipc->pos % WIN_SIZE_X + perim / 2)
	if (x >= 0 && x < WIN_SIZE_X && y >= 0 && y < WIN_SIZE_Y
	    && lemipc->map[x + y * WIN_SIZE_X] != lemipc->no_team
	    && lemipc->map[x + y * WIN_SIZE_X] != 0
	    && is_common_ally(x + y * WIN_SIZE_X, lemipc, perim) == TRUE)
	  return (x + y * WIN_SIZE_X);
	else
	  ++x;
      ++y;
    }
  return (-1);
}

static int		nearest_ally(t_lemipc *lemipc, int perim)
{
  int			pos;
  int			y;
  int			x;

  pos = -1;
  y = lemipc->pos / WIN_SIZE_X - perim / 2;
  while (y != (int)lemipc->pos / WIN_SIZE_X + perim / 2)
    {
      x = lemipc->pos % WIN_SIZE_X - perim / 2;
      while (x != (int)lemipc->pos % WIN_SIZE_X + perim / 2)
	{
	  if (x >= 0 && x < WIN_SIZE_X && y >= 0 && y < WIN_SIZE_Y
	      && lemipc->map[x + y * WIN_SIZE_X] == lemipc->no_team
	      && (x + y * WIN_SIZE_X) != (int)lemipc->pos &&
	      (pos == -1 || !is_less_far(lemipc, pos, x + y * WIN_SIZE_X)))
	    pos = x + y * WIN_SIZE_X;
	  ++x;
	}
      ++y;
    }
  return (pos);
}

void			move_algorithm(t_lemipc *lemipc)
{
  int			pos_ennemy;
  int			pos_ally;

  if ((pos_ally = nearest_ally(lemipc, LARGE_PERIM_A)) != -1)
    if ((pos_ennemy = check_ennemy_to_attack(lemipc, LARGE_PERIM_E)) != -1)
      move_to(pos_ennemy, lemipc);
    else
      if (nearest_ally(lemipc, SHORT_PERIM) != -1)
	if ((pos_ennemy = check_ennemy_to_attack(lemipc, LARGE_PERIM_A)) != -1)
	  move_to(pos_ennemy, lemipc);
	else
	  move_random(lemipc);
      else
	move_to(pos_ally, lemipc);
  else
    move_random(lemipc);
}
