/*
** show_map.h for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Mon Mar 27 15:49:00 2017 Arnaud WURMEL
** Last update Sat Apr  1 19:39:07 2017 Arnaud WURMEL
*/

#ifndef SHOW_MAP_H_
# define SHOW_MAP_H_

typedef struct		s_window
{
  sfRenderWindow	*window;
}			t_window;

void			get_size(sfVector2f *);
void			get_colors(sfColor[5]);

#endif /* !SHOW_MAP_H_ */
