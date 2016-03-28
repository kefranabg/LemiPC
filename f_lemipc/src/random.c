/*
** random.c for random.c in /home/loeb_t/rendu/PSU_2013_lemipc/f_lemipc
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Sat Mar 22 17:06:02 2014 LOEB Thomas
** Last update Sun Mar 23 15:27:41 2014 LOEB Thomas
*/

#include		"lemipc.h"

static int		switch_char(t_lemipc *lemipc, int incr,
				    char rand, char check)
{
  if ((check & rand) == rand)
    return (rand);
  if (((rand == 1 && lemipc->pos % WIN_SIZE_X + 1 < WIN_SIZE_X) ||
       (rand == 2 && (int)lemipc->pos % WIN_SIZE_X - 1 >= 0) ||
       (rand == 4 && lemipc->pos / WIN_SIZE_X + 1 < WIN_SIZE_Y) ||
       (rand == 8 && (int)lemipc->pos / WIN_SIZE_X - 1 >= 0)) &&
      lemipc->map[lemipc->pos + incr] == 0)
    {
      lemipc->map[lemipc->pos] = 0;
      lemipc->pos += incr;
      lemipc->map[lemipc->pos] = lemipc->no_team;
      return (15);
    }
  else
    return (rand);
}

static int		g_inc[NB_DIRECTIONS] =
  {
    1,
    -1,
    WIN_SIZE_X,
    -WIN_SIZE_X
  };

void			move_random(t_lemipc *lemipc)
{
  unsigned char		direction;
  unsigned char		check;

  check = 0;
  while (check < 15)
    {
      direction = rand() % NB_DIRECTIONS;
      check |= switch_char(lemipc, g_inc[direction], pow(2, direction), check);
    }
}
