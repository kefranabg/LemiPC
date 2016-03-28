/*
** main.c for main.c in /home/loeb_t/rendu/PSU_2013_lemipc
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Wed Mar 19 14:52:56 2014 LOEB Thomas
** Last update Tue Feb 10 09:48:34 2015 abgral_f
*/

#include		"lemipc.h"

static int		get_sem(t_lemipc *lemipc)
{
  if ((lemipc->sem_id = semget(lemipc->key, 1, FLG(0))) == -1)
    {
      if ((lemipc->sem_id = semget(lemipc->key, 1, FLG(1))) == -1)
	return (lemipc_perror(SEMGET_ERROR));
      else if (semctl(lemipc->sem_id, 0, SETVAL, 1) == -1)
	return (lemipc_perror(SEMCTL_ERROR));
    }
  return (EXIT_SUCCESS);
}

static int		get_shm(t_lemipc *lemipc)
{
  unsigned int		count;

  if ((lemipc->shm_id = shmget(lemipc->key, MAP_SIZE, FLG(0))) == -1)
    if ((lemipc->shm_id = shmget(lemipc->key, MAP_SIZE, FLG(1))) == -1)
      return (lemipc_perror(SHMGET_ERROR));
    else if ((lemipc->map = shmat(lemipc->shm_id, NULL, FLG(0))) == (void *)-1)
      return (lemipc_perror(SHMAT_ERROR));
    else
      {
	count = -1;
	while (++count < MAP_SIZE)
	  lemipc->map[count] = 0;
      }
  else
    if ((lemipc->map = shmat(lemipc->shm_id, NULL, FLG(0))) == (void *)-1)
      return (lemipc_perror(SHMAT_ERROR));
  return (EXIT_SUCCESS);
}

static int		get_msgq(t_lemipc *lemipc)
{
  if ((lemipc->msg_id = msgget(lemipc->key, FLG(0))) == -1)
    if ((lemipc->msg_id = msgget(lemipc->key, FLG(1))) == -1)
      return (lemipc_perror(MSGGET_ERROR));
  return (EXIT_SUCCESS);
}

static int		lemipc_bsc(int no_team, char *path)
{
  t_lemipc		lemipc;

  if (no_team < 1 || no_team > 255)
    return (lemipc_error(NO_TEAM_ERROR));
  if ((lemipc.key = ftok(path, 0)) == -1)
    return (lemipc_perror(FTOK_ERROR));
  lemipc.no_team = no_team;
  lemipc.pos = -1;
  lemipc.killed_by = 0;
  lemipc.is_alone = TRUE;
  lemipc.is_dead = FALSE;
  if (get_shm(&lemipc) == EXIT_FAILURE ||
      get_sem(&lemipc) == EXIT_FAILURE ||
      get_msgq(&lemipc) == EXIT_FAILURE ||
      launch_player(&lemipc) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
  if (ac != 2 && ac != 3)
    return (lemipc_error(USAGE));
  srand(clock());
  return (lemipc_bsc(atoi(av[1]), (av[2] == NULL) ? KEY_GEN : av[2]));
}
