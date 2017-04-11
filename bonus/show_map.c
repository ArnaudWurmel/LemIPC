/*
** show_map.c for LemIPC Bonus in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Mon Mar 27 14:39:29 2017 Arnaud WURMEL
** Last update Sun Apr  2 22:56:59 2017 Arnaud WURMEL
*/

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.h>
#include "lemipc.h"
#include "show_map.h"

/*
** t_window		*get_window(...)
**
** Renvoie la window.
*/
t_window		*get_window(t_window *win, char keep)
{
  static t_window	*curr = NULL;

  if (keep)
    curr = win;
  return (curr);
}

/*
** t_window	*create_window()
**
** Crée la fenêtre.
*/
t_window	*create_window()
{
  t_window	*window;
  sfVideoMode	mode;

  mode.width = 500;
  mode.height = 500;
  mode.bitsPerPixel = 32;
  if ((window = malloc(sizeof(t_window))) == NULL)
    return (NULL);
  if ((window->window = sfRenderWindow_create(mode, "LemIPC",
					      sfClose, NULL)) == NULL)
    {
      return (NULL);
    }
  return (window);
}

/*
** static void		draw_board(...)
**
** Affiche la map.
*/
static void		draw_board(t_window *win,
				   const t_block *board)
{
  t_pos			pos;
  sfRectangleShape	*rec;
  sfVector2f		siz;
  sfVector2f		pos_p;
  sfColor		team_color[5];

  get_colors(team_color);
  get_size(&siz);
  sfRectangleShape_setSize((rec = sfRectangleShape_create()), siz);
  pos.y = -1;
  while (++pos.y < MAP_HEIGHT)
    {
      pos_p.y = pos.y * siz.y;
      pos.x = -1;
      while (++pos.x < MAP_WIDTH)
	{
	  pos_p.x = pos.x * siz.x;
	  sfRectangleShape_setFillColor(rec,
	  team_color[board[pos.x + (pos.y * MAP_WIDTH)].team_number % 5]);
	  sfRectangleShape_setPosition(rec, pos_p);
	  if (board[pos.x + (pos.y * MAP_WIDTH)].team_number)
	    sfRenderWindow_drawRectangleShape(win->window, rec, NULL);
	}
    }
}

void		display(const t_shared *shared)
{
  t_window	*win;
  sfEvent	e;

  if ((win = get_window(NULL, 0)) == NULL &&
      ((win = create_window())) == NULL)
    return ;
  if (sfRenderWindow_isOpen(win->window))
    {
      if (sfRenderWindow_pollEvent(win->window, &e))
	{
	  if (e.type == sfEvtClosed)
	    sfRenderWindow_close(win->window);
	}
      sfRenderWindow_clear(win->window, sfColor_fromRGB(52, 73, 94));
      draw_board(win, shared->board);
      sfRenderWindow_display(win->window);
    }
  get_window(win, 1);
}

void		display_exit()
{
  t_window	*win;

  win = get_window(NULL, 0);
  if (win && win->window)
    {
      sfRenderWindow_destroy(win->window);
      free(win);
    }
  get_window(NULL, 1);
}
