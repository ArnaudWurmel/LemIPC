/*
** get_values.c for lemipc in /home/vicky
** 
** Made by Victorien Fischer
** Login   <victorien.fischer@epitech.eu>
** 
** Started on  Sat Apr  1 15:14:57 2017 Victorien Fischer
** Last update Sat Apr  1 22:23:31 2017 Arnaud WURMEL
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "lemipc.h"

void	get_size(sfVector2f *size)
{
  size->x = (500 / MAP_WIDTH);
  size->y = (500 / MAP_WIDTH);
}

void	get_colors(sfColor team_color[5])
{
  team_color[0] = sfColor_fromRGB(230, 126, 34);
  team_color[1] = sfColor_fromRGB(46, 204, 113);
  team_color[2] = sfColor_fromRGB(231, 76, 60);
  team_color[3] = sfColor_fromRGB(236, 240, 241);
  team_color[4] = sfColor_fromRGB(52, 152, 219);
}
