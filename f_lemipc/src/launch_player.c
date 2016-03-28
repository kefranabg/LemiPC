/*
** launch_player.c for launch_player.c in /home/abgral_f/dev/lemipc2/src
**
** Made by abgral_f
** Login   <abgral_f@epitech.net>
**
** Started on  Thu Mar 20 14:45:54 2014 abgral_f
** Last update Mon Mar 24 14:31:27 2014 LOEB Thomas
*/

#include		"lemipc.h"

static int		put_player_on_map(t_lemipc *lemipc)
{
  unsigned int		rand_pos;

  rand_pos = rand() % MAP_SIZE;
  lemipc->pos = rand_pos;
  while (lemipc->map[lemipc->pos] != 0)
    {
      lemipc->pos = (lemipc->pos + 1) % MAP_SIZE;
      if (lemipc->pos == rand_pos)
	return (lemipc_error(NO_SPACE_ERROR));
    }
  lemipc->map[lemipc->pos] = lemipc->no_team;
  return (EXIT_SUCCESS);
}

static int		set_sem(t_lemipc *lemipc, int status)
{
  struct sembuf		sem_op;

  sem_op.sem_num = 0;
  sem_op.sem_flg = 0;
  sem_op.sem_op = status;
  if (semop(lemipc->sem_id, &sem_op, 1) == -1)
    return (lemipc_perror(SEMOP_ERROR));
  return (EXIT_SUCCESS);
}

static int		player_turn(t_lemipc *lemipc)
{
  if (set_sem(lemipc, LOCK) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((int)lemipc->pos == -1 && put_player_on_map(lemipc) == EXIT_FAILURE)
    return (set_sem(lemipc, UNLOCK));
  if (lemipc->is_alone == TRUE)
    lemipc->is_alone = player_is_alone(lemipc, FALSE);
  else if (player_is_alone(lemipc, FALSE) == TRUE)
    {
      lemipc->is_dead = TRUE;
      lemipc->is_alone = TRUE;
    }
  if (lemipc->is_alone == FALSE)
    {
      if (lemipc->is_dead == FALSE)
	lemipc->is_dead = player_is_surrounded(lemipc);
      if (lemipc->is_dead == FALSE)
	move_algorithm(lemipc);
    }
  usleep(SLEEP);
  if (lemipc->killed_by != 0 && send_msg(lemipc) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  recieve_msg(lemipc);
  return (set_sem(lemipc, UNLOCK));
}

int			launch_player(t_lemipc *lemipc)
{
  while (lemipc->is_dead == FALSE)
    if (player_turn(lemipc) == EXIT_FAILURE)
      return (EXIT_FAILURE);
  lemipc->map[lemipc->pos] = 0;
  if (lemipc->is_alone == TRUE && player_is_alone(lemipc, TRUE) == TRUE)
    {
      shmdt(lemipc->map);
      usleep(SLEEP);
      semctl(lemipc->sem_id, 0, IPC_RMID);
      shmctl(lemipc->shm_id, IPC_RMID, NULL);
      msgctl(lemipc->msg_id, IPC_RMID, NULL);
    }
  else
    shmdt(lemipc->map);
  return (EXIT_SUCCESS);
}
