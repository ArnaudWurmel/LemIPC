/*
** ia_manager.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Mon Mar 27 11:12:02 2017 Arnaud WURMEL
** Last update Sat Apr  1 21:56:52 2017 Arnaud WURMEL
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "lemipc.h"

/*
** static void	select_best(...)
**
** first : première position
** second : seconde position
** player : joueur
**
** Selectionne la meilleure position entre first et second
** pour le joueur player.
*/
static void	select_best(t_position **first, t_position *second,
			    const t_player *player)
{
  int		d_first;
  int		d_second;
  int		tmp;

  if (*first == NULL && second == NULL)
    return ;
  if (*first == NULL)
    {
      *first = second;
      return ;
    }
  if (second == NULL)
    return ;
  d_first = player->p_position.x - (*first)->x;
  tmp = player->p_position.y - (*first)->y;
  d_first = ABS(d_first) + ABS(tmp);
  d_second = player->p_position.x - second->x;
  tmp = player->p_position.y - second->y;
  d_second = ABS(d_second) + ABS(tmp);
  if (d_first > d_second)
    {
      (*first)->x = second->x;
      (*first)->y = second->y;
    }
  free(second);
}

/*
** t_position	*get_closest_enemy_rec(...)
**
** player : le joueur
** board : la map
** x : coordonnée x
** y : coordonnée y
**
** Récursive permettant de trouver l'ennemi le plus proche.
*/
t_position	*get_closest_enemy_rec(const t_player *player,
				       t_block *board,
				       int x,
				       int y)
{
  t_position	*ret;

  if (CORRECT_POS(x, y) == 0 ||
      board[x + (y * MAP_WIDTH)].team_number == MAX_TEAM + 1)
    return (NULL);
  if (board[x + (y * MAP_WIDTH)].team_number != 0 &&
      !board_is_team(board, x, y, player->team_number))
    return (create_position(x, y));
  board[x + (y * MAP_WIDTH)].team_number = MAX_TEAM + 1;
  ret = NULL;
  select_best(&ret, get_closest_enemy_rec(player, board, x + 1, y), player);
  select_best(&ret, get_closest_enemy_rec(player, board, x - 1, y), player);
  select_best(&ret, get_closest_enemy_rec(player, board, x, y + 1), player);
  select_best(&ret, get_closest_enemy_rec(player, board, x, y - 1), player);
  return (ret);
}

/*
** t_position	*get_closest_enemy(...)
**
** player : le joueur qui regarde
** board : la map
**
** Renvoie la position de l'ennemi le plus proche dans le 
** champs de vision du joueur. Renvoie NULL si aucun n'est
** trouvé.
*/
t_position	*get_closest_enemy(const t_player *player,
				  const t_block *board)
{
  t_position	*pos;
  t_block	*cpy;
  unsigned int	y;
  unsigned int	x;

  if ((cpy = malloc(sizeof(t_block) * MAP_WIDTH * MAP_HEIGHT)) == NULL)
    return (NULL);
  memcpy(cpy, board, sizeof(t_block) * MAP_WIDTH * MAP_HEIGHT);
  y = player->p_position.y;
  x = player->p_position.x;
  cpy[x + (y * MAP_WIDTH)].team_number = 0;
  pos = NULL;
  pos = get_closest_enemy_rec(player, cpy, x, y);
  free(cpy);
  return (pos);
}
