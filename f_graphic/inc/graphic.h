/*
** graphic.h for graphic.h in /home/loeb_t/rendu/PSU_2013_lemipc/f_graphic
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Sat Mar 22 13:30:32 2014 LOEB Thomas
** Last update Sun Mar 23 18:35:39 2014 abgral_f
*/

#ifndef			GRAPHIC_H_
# define		GRAPHIC_H_

# include		<unistd.h>
# include		<time.h>
# include		<stdlib.h>
# include		<stdio.h>
# include		<string.h>
# include		<sys/types.h>
# include		<sys/ipc.h>
# include		<sys/shm.h>
# include		<SDL/SDL.h>

# define		KEY_GEN		"/"
# define		GAME_NAME	"lemipc | loeb_t - abgral_f"
# define		SIZE_SPRITE	32
# define		WIN_SIZE_X	30
# define		WIN_SIZE_Y	30
# define		MAP_SIZE	(WIN_SIZE_X * WIN_SIZE_Y)
# define		WIN_X		(WIN_SIZE_X * SIZE_SPRITE)
# define		WIN_Y		(WIN_SIZE_Y * SIZE_SPRITE)
# define		FLG(x)		(x * IPC_CREAT) | SHM_R | SHM_W
# define		SLEEP		75000

typedef enum		e_bool
  {
    TRUE		= 0,
    FALSE		= 1
  }			bool;

typedef struct		s_graphic
{
  key_t			key;
  int			shm_id;
  unsigned char		*map;
  SDL_Surface		*screen;
  SDL_Rect		rect;
}			t_graphic;

/*
** PROTOTYPES
*/

/*
** ERROR_HANDLING
*/

int			graphic_error(char *);

# define		USAGE		"USAGE: ./graphic [PATH]"

int			graphic_perror(char *);

# define		FTOK_ERROR	"ERROR: System call 'ftok' failed"
# define		SHMGET_ERROR	"ERROR: System call 'shmget' failed"
# define		SHMAT_ERROR	"ERROR: System call 'shmat' failed"

#endif
