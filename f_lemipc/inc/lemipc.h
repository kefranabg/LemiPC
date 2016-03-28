/*
** lemipc.h for lemipc.h in /home/loeb_t/rendu/PSU_2013_lemipc
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Wed Mar 19 14:53:06 2014 LOEB Thomas
** Last update Mon Mar 24 15:56:02 2014 LOEB Thomas
*/

#ifndef			LEMIPC_H_
# define		LEMIPC_H_

# include		<unistd.h>
# include		<time.h>
# include		<stdlib.h>
# include		<stdio.h>
# include		<string.h>
# include		<math.h>
# include		<sys/types.h>
# include		<sys/ipc.h>
# include		<sys/sem.h>
# include		<sys/shm.h>
# include		<sys/msg.h>

# define		NB_DIRECTIONS	4
# define		KEY_GEN		"/"
# define		WIN_SIZE_X	30
# define		WIN_SIZE_Y	30
# define                LARGE_PERIM_A	(WIN_SIZE_X * 2)
# define                LARGE_PERIM_E	21
# define                SHORT_PERIM	3
# define		MAP_SIZE	(WIN_SIZE_X * WIN_SIZE_Y)
# define		LOCK		-1
# define		UNLOCK		1
# define		FLG(x)		(x * IPC_CREAT) | SHM_R | SHM_W
# define		SLEEP		75000

# define		MSG		"A member of the team %d was killed by the team %d !"
# define		MSG_LEN		64

typedef enum		e_bool
  {
    TRUE		= 0,
    FALSE		= 1
  }			bool;

typedef struct		s_msg
{
  long			type;
  char			no_team[MSG_LEN];
}			t_msg;

typedef struct		s_lemipc
{
  key_t			key;
  int			shm_id;
  int			sem_id;
  int			msg_id;
  unsigned char		*map;
  unsigned char		no_team;
  unsigned int		pos;
  bool			is_alone;
  bool			is_dead;
  unsigned char		killed_by;
}			t_lemipc;

typedef struct		s_rand
{
  int			(*switch_char)(t_lemipc *, int, char, char);
  int			incr;
}			t_rand;

/*
** PROTOTYPES
*/

void                    recieve_msg(t_lemipc *);
int                     send_msg(t_lemipc *);
void			move_to(int, t_lemipc *);
bool                    is_less_far(t_lemipc *, int, int);
int                     launch_player(t_lemipc *);
bool			player_is_surrounded(t_lemipc *);
bool			player_is_alone(t_lemipc *, bool);
void			move_algorithm(t_lemipc *);
void			move_random(t_lemipc *);

/*
** ERROR_HANDLING
*/

int			lemipc_error(char *);

# define		USAGE		"USAGE: ./lemipc [N°TEAM] [PATH]"
# define		NO_TEAM_ERROR	"ERROR: Team number must be between 1 and 255"
# define		NO_SPACE_ERROR	"ERROR: No more space on the map"

int			lemipc_perror(char *);

# define		FTOK_ERROR	"ERROR: System call 'ftok' failed"
# define		SHMGET_ERROR	"ERROR: System call 'shmget' failed"
# define		SEMGET_ERROR	"ERROR: System call 'semget' failed"
# define		SHMAT_ERROR	"ERROR: System call 'shmat' failed"
# define		SEMCTL_ERROR	"ERROR: System call 'semctl' failed"
# define		SEMOP_ERROR	"ERROR: System call 'semop' failed"
# define		MSGGET_ERROR	"ERROR: System call 'msgget' failed"
# define		MSGSND_ERROR	"ERROR: System call 'msgsnd' failed"

#endif
