/*
** utilities.c for lemipc in /home/vicky/Bureau/EPITECH/tek2-2/PSU/PSU_2016_lemipc/srcs/game_manager
** 
** Made by Victorien Fischer
** Login   <victorien.fischer@epitech.eu>
** 
** Started on  Wed Mar 29 17:52:02 2017 Victorien Fischer
** Last update Sat Apr  1 15:21:16 2017 Arnaud WURMEL
*/

#include <stdlib.h>
#include <sys/types.h>
#include "lemipc.h"

/*
** t_position	*create_position(...)
**
** x : coordonnée x
** y : coordonnée y
**
** Crée une struct t_position avec (x;y)
*/
t_position	*create_position(unsigned int x, unsigned int y)
{
  t_position	*res;

  if (!(res = malloc(sizeof(t_position))))
    return (NULL);
  res->x = x;
  res->y = y;
  return (res);
}

/*
** int		board_is_team(...)
**
** board : la map
** x : coordonnée x
** y : coordonnée y
** team : la team à vérifier
**
** Renvoie 1 si la team à la position (x;y) est team ou 0,
** sinon 0.
*/
int		board_is_team(const t_block *board, int x, int y,
			      unsigned int team)
{
  unsigned int	team_board;

  if (CORRECT_POS(x, y))
    {
      team_board = board[get_pos_board(x, y)].team_number;
      return (team_board == team || !team_board);
    }
  return (0);
}

/*
** int		get_pos_board(int x, int y)
**
** x : la position x dans le board
** y : la position y dans le board
**
** Renvoie l'index de la position (x;y) dans le board
*/
int		get_pos_board(int x, int y)
{
  return (x + (y * MAP_WIDTH));
}
