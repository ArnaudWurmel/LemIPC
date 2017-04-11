/*
** player_manager.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sun Mar 26 21:53:18 2017 Arnaud WURMEL
** Last update Sun Apr  2 21:00:12 2017 Victorien Fischer
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "lemipc.h"

/*
** static int	count_available_pos(t_block *board)
**
** board : la map
**
** Cette fonction renvoie le nombre de position disponible.
*/
static int	count_available_pos(const t_block *board)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (i < MAP_WIDTH * MAP_HEIGHT)
    {
      if (board[i].team_number == 0)
	++count;
      ++i;
    }
  return (count);
}

/*
** static t_position	*get_all_position(t_block *board, int *size)
**
** board : la map
** size : nombre de position disponible
**
** Renvoie un tableau de toutes les positions disponibles.
*/
static t_position	*get_all_position(const t_block *board,
					  int *size)
{
  t_position		*pos;
  unsigned int		y;
  unsigned int		x;
  unsigned int		i;

  if ((*size = count_available_pos(board)) == 0 ||
      (pos = calloc(1, sizeof(t_position) * (*size))) == NULL)
    return (NULL);
  y = 0;
  i = 0;
  while (y < MAP_HEIGHT)
    {
      x = 0;
      while (x < MAP_WIDTH)
	{
	  if (board[x + (y * MAP_WIDTH)].team_number == 0)
	    {
	      pos[i].x = x;
	      pos[i++].y = y;
	    }
	  ++x;
	}
      ++y;
    }
  return (pos);
}

/*
** t_position	player_position(...)
**
** board : la map
** err : contiendra le code d'erreur
**
** Renvoie la position du joueur dans le board.
*/
t_position	player_position(const t_block *board, char *err)
{
  t_position	*pos;
  t_position	ret;
  int		size;
  int		pos_cr;

  bzero(&ret, sizeof(t_position));
  if ((pos = get_all_position(board, &size)) == NULL)
    {
      *err = 1;
      return (ret);
    }
  pos_cr = rand() % size;
  memcpy(&ret, &pos[pos_cr], sizeof(t_position));
  free(pos);
  return (ret);
}
