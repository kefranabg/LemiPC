/*
** coord.c for coord.c in /home/abgral_f/PSU_2013_lemipc/f_lemipc/src
**
** Made by abgral_f
** Login   <abgral_f@epitech.net>
**
** Started on  Sun Mar 23 13:44:42 2014 abgral_f
** Last update Mon Mar 24 15:42:57 2014 LOEB Thomas
*/

#include		"lemipc.h"

static void             assign_new_pos(t_lemipc *lemipc, int prio, int other)
{
  if (lemipc->map[prio + lemipc->pos] == 0)
    {
      lemipc->map[lemipc->pos] = 0;
      lemipc->pos = prio + lemipc->pos;
      lemipc->map[lemipc->pos] = lemipc->no_team;
    }
  else if (lemipc->map[other + lemipc->pos] == 0)
    {
      lemipc->map[lemipc->pos] = 0;
      lemipc->pos = other + lemipc->pos;
      lemipc->map[lemipc->pos] = lemipc->no_team;
    }
  else
    move_random(lemipc);
}

static int              compare_coord(int coord_one, int coord_two)
{
  if (coord_one < coord_two)
    return (1);
  if (coord_one > coord_two)
    return (-1);
  return (0);
}

void			move_to(int pos, t_lemipc *lemipc)
{
  int                   move_x;
  int                   move_y;
  unsigned int          rand_pos;

  move_x = compare_coord((int)lemipc->pos % WIN_SIZE_X, pos % WIN_SIZE_X);
  move_y = compare_coord((int)lemipc->pos / WIN_SIZE_X, pos / WIN_SIZE_X);
  if (move_x == 0)
    assign_new_pos(lemipc, move_y * WIN_SIZE_X, move_y * WIN_SIZE_X);
  else if (move_y == 0)
    assign_new_pos(lemipc, move_x, move_x);
  else
    {
      rand_pos = rand() % 2;
      if (rand_pos == 0)
	assign_new_pos(lemipc, move_x, move_y * WIN_SIZE_X);
      else
	assign_new_pos(lemipc, move_y * WIN_SIZE_X, move_x);
    }
}

bool			is_less_far(t_lemipc *lemipc, int pos_one, int pos_two)
{
  int                   x_one;
  int                   y_one;
  int                   x_two;
  int                   y_two;

  if ((x_one = lemipc->pos % WIN_SIZE_X - pos_one % WIN_SIZE_X) < 0)
    x_one *= -1;
  if ((y_one = lemipc->pos / WIN_SIZE_X - pos_one / WIN_SIZE_X) < 0)
    y_one *= -1;
  if ((x_two = lemipc->pos % WIN_SIZE_X - pos_two % WIN_SIZE_X) < 0)
    x_two *= -1;
  if ((y_two = lemipc->pos / WIN_SIZE_X - pos_two / WIN_SIZE_X) < 0)
    y_two *= -1;
  if ((y_two + x_two) < (y_one + x_one))
    return (TRUE);
  return (FALSE);
}
