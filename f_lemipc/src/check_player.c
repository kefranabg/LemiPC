/*
** check_player.c for check_player.c in /home/loeb_t/rendu/PSU_2013_lemipc
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Fri Mar 21 16:40:51 2014 LOEB Thomas
** Last update Mon Mar 24 14:40:10 2014 LOEB Thomas
*/

#include		"lemipc.h"

static bool		check_around(unsigned char around[8],
				     t_lemipc *lemipc)
{
  unsigned char		count;
  unsigned char		tmp;

  count = -1;
  while (++count < 8)
    {
      tmp = -1;
      while (++tmp < 8)
	if (tmp != count &&
	    around[tmp] == around[count] &&
	    around[tmp] != 0 && around[tmp] != lemipc->no_team)
	  {
	    lemipc->killed_by = around[tmp];
	    return (TRUE);
	  }
    }
  return (FALSE);
}

bool			player_is_surrounded(t_lemipc *lemipc)
{
  unsigned char		around[8];

  memset(around, 0, 8);
  if (lemipc->pos >= WIN_SIZE_X)
    {
      if (lemipc->pos % WIN_SIZE_X > 0)
        around[0] = lemipc->map[lemipc->pos - WIN_SIZE_X - 1];
      around[1] = lemipc->map[lemipc->pos - WIN_SIZE_X];
      if (lemipc->pos % WIN_SIZE_X < WIN_SIZE_X - 1)
        around[2] = lemipc->map[lemipc->pos - WIN_SIZE_X + 1];
    }
  if (lemipc->pos % WIN_SIZE_X > 0)
    around[3] = lemipc->map[lemipc->pos - 1];
  if (lemipc->pos % WIN_SIZE_X < WIN_SIZE_X - 1)
    around[4] = lemipc->map[lemipc->pos + 1];
  if (lemipc->pos < MAP_SIZE - WIN_SIZE_X)
    {
      if (lemipc->pos % WIN_SIZE_X > 0)
        around[5] = lemipc->map[lemipc->pos + WIN_SIZE_X - 1];
      around[6] = lemipc->map[lemipc->pos + WIN_SIZE_X];
      if (lemipc->pos % WIN_SIZE_X < WIN_SIZE_X - 1)
        around[7] = lemipc->map[lemipc->pos + WIN_SIZE_X + 1];
    }
  return (check_around(around, lemipc));
}

bool			player_is_alone(t_lemipc *lemipc, bool flag)
{
  unsigned int		count;

  count = -1;
  while (++count < MAP_SIZE)
    if (lemipc->map[count] != 0 &&
	(flag == TRUE || lemipc->map[count] != lemipc->no_team))
      return (FALSE);
  return (TRUE);
}
