/*
** msgq.c for msgq.c in /home/abgral_f/PSU_2013_lemipc/f_lemipc/src
**
** Made by abgral_f
** Login   <abgral_f@epitech.net>
**
** Started on  Sun Mar 23 15:57:38 2014 abgral_f
** Last update Mon Mar 24 14:33:04 2014 LOEB Thomas
*/

#include		"lemipc.h"

int                     send_msg(t_lemipc *lemipc)
{
  t_msg                 msg;

  msg.type = lemipc->killed_by;
  memset(msg.no_team, 0, MSG_LEN);
  sprintf(msg.no_team, MSG, lemipc->no_team, lemipc->killed_by);
  if (msgsnd(lemipc->msg_id, &msg, sizeof(msg), 0) == -1)
    return (lemipc_error(MSGSND_ERROR));
  return (EXIT_SUCCESS);
}

void			recieve_msg(t_lemipc *lemipc)
{
  t_msg                 msg;

  if (msgrcv(lemipc->msg_id, &msg, sizeof(msg),
	     lemipc->no_team, IPC_NOWAIT) != -1)
    printf("%s\n", msg.no_team);
}
