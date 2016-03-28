/*
** graphic.c for graphic.c in /home/loeb_t/rendu/PSU_2013_lemipc/f_lemipc
**
** Made by LOEB Thomas
** Login   <loeb_t@epitech.net>
**
** Started on  Sat Mar 22 13:30:05 2014 LOEB Thomas
** Last update Thu Mar 27 18:39:16 2014 LOEB Thomas
*/

#include		"graphic.h"

static int		display_map(t_graphic *gui)
{
  unsigned int		count;
  unsigned int		color;

  count = -1;
  while (++count < MAP_SIZE)
    if (gui->map[count] != 0)
      {
	gui->rect.x = (count % WIN_SIZE_X) * SIZE_SPRITE;
	gui->rect.y = (count / WIN_SIZE_X) * SIZE_SPRITE;
	color = gui->map[count] * ((0xFFFFFF - 0x222222) / 254) + 0x222222;
	if (SDL_FillRect(gui->screen, &gui->rect,
			 SDL_MapRGB(gui->screen->format,
				    (color >> 16) & 0xFF,
				    (color >> 8) & 0xFF,
				    color & 0xFF)) == -1)
	  return (graphic_error(SDL_GetError()));
      }
  return (EXIT_SUCCESS);
}

static bool		map_empty(t_graphic *gui)
{
  unsigned int		count;

  count = -1;
  while (++count < MAP_SIZE)
    if (gui->map[count] != 0)
      return (FALSE);
  return (TRUE);
}

static int              get_shm(t_graphic *gui)
{
  if ((gui->shm_id = shmget(gui->key, MAP_SIZE, FLG(0))) == -1)
    return (graphic_perror(SHMGET_ERROR));
  else if ((gui->map = shmat(gui->shm_id, NULL, FLG(0))) == (void *)-1)
    return (graphic_perror(SHMAT_ERROR));
  return (EXIT_SUCCESS);
}

static int		graphic_bsc(char *path)
{
  t_graphic		gui;

  if ((gui.key = ftok(path, 0)) == -1)
    return (graphic_perror(FTOK_ERROR));
  if (get_shm(&gui) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (SDL_Init(SDL_INIT_VIDEO) == -1 ||
      (gui.screen = SDL_SetVideoMode(WIN_X, WIN_Y, SIZE_SPRITE,
				     SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    return (graphic_error(SDL_GetError()));
  SDL_WM_SetCaption(GAME_NAME, NULL);
  gui.rect.w = SIZE_SPRITE;
  gui.rect.h = SIZE_SPRITE;
  while (map_empty(&gui) == FALSE)
    if (SDL_FillRect(gui.screen, NULL, 0) == -1)
      return (graphic_error(SDL_GetError()));
    else if (display_map(&gui) == EXIT_FAILURE)
      return (EXIT_FAILURE);
    else if (SDL_Flip(gui.screen) == -1)
      return (graphic_error(SDL_GetError()));
    else
      usleep(SLEEP);
  SDL_Quit();
  shmdt(gui.map);
  return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
  if (ac > 2)
    return (graphic_error(USAGE));
  return (graphic_bsc((av[1] == NULL) ? KEY_GEN : av[1]));
}
