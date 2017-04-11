/*
** moves.c for lemipc in /home/vicky/Bureau/EPITECH/tek2-2/PSU/PSU_2016_lemipc/srcs/game_manager
** 
** Made by Victorien Fischer
** Login   <victorien.fischer@epitech.eu>
** 
** Started on  Wed Mar 29 17:56:24 2017 Victorien Fischer
** Last update Sat Apr  1 22:26:02 2017 Arnaud WURMEL
*/

#include <stdlib.h>
#include <stdio.h>
#include "lemipc.h"

/*
** void			move_player_at(...)
**
** player : le joueur à déplacer
** board : la map
** at : la position
** shared : les données partagées
**
** Déplace un joueur à une position donnée
*/
static unsigned char	move_player_at(t_player *player,
				       t_block *board,
				       t_position *at,
				       const t_shared *shared)
{
  if (board[BOARD_CALC(at)].team_number == 0)
    {
      board[BOARD_ID_POS(player)].team_number = 0;
      player->p_position = *at;
      board[BOARD_CALC(at)].team_number = player->team_number;
      message_displayer(player, shared);
      return (1);
    }
  return (0);
}

/*
** unsigned char	move_p_vertical(...)
**
** player : le joueur
** board : la map
** delta_x : le mouvement vertical
** shared : les données partagées
**
** Cette fonction va faire se déplacer un joueur de
** façon verticale.
*/
static unsigned char	move_p_vertical(t_player *player,
					t_block *board,
					int delta_y,
					const t_shared *shared)
{
  char			moved;
  t_position		pos;

  moved = 0;
  if (delta_y < 0 && player->p_position.y > 0)
    {
      pos.x = player->p_position.x;
      pos.y = player->p_position.y - 1;
      moved = 1;
    }
  else if (delta_y > 0 && player->p_position.y + 1 < MAP_HEIGHT)
    {
      pos.x = player->p_position.x;
      pos.y = player->p_position.y + 1;
      moved = 1;
    }
  if (moved)
    moved = move_player_at(player, board, &pos, shared);
  return (moved);
}

/*
** unsigned char	move_p_horizontal(...)
**
** player : le joueur
** board : la map
** delta_x : le mouvement horizontal
** shared : les données partagées
**
** Cette fonction va faire se déplacer un joueur de
** façon horizontale.
*/
static unsigned char	move_p_horizontal(t_player *player,
					  t_block *board,
					  int delta_x,
					  const t_shared *shared)
{
  char			moved;
  t_position		pos;

  moved = 0;
  if (delta_x < 0 && player->p_position.x > 0)
    {
      pos.x = player->p_position.x - 1;
      pos.y = player->p_position.y;
      moved = 1;
    }
  else if (delta_x > 0 && player->p_position.x + 1 < MAP_WIDTH)
    {
      pos.x = player->p_position.x + 1;
      pos.y = player->p_position.y;
      moved = 1;
    }
  if (moved)
    moved = move_player_at(player, board, &pos, shared);
  return (moved);
}

/*
** static void	move_randomly(...)
**
** player : joueur qui va se déplacer
** board : la map
** shared : les données partagées
**
** Déplace un joueur de façon aléatoire.
*/
static void	move_randomly(t_player *player, t_block *board,
			      const t_shared *shared)
{
  int		dir;
  t_position	pos;

  dir = rand() % 4;
  pos = player->p_position;
  if (player->p_position.y > 0 && dir == 0)
    pos.y -= 1;
  if (player->p_position.x + 1 < MAP_WIDTH && dir == 1)
    pos.x += 1;
  if (player->p_position.y + 1 < MAP_WIDTH && dir == 2)
    pos.y += 1;
  if (player->p_position.x > 0 && dir == 3)
    pos.x -= 1;
  move_player_at(player, board, &pos, shared);
}

/*
** void		move_p(t_player *player, const t_shared *shared)
**
** player : le joueur qui va se déplacer
** shared : les données partagées
**
** Cette fonction va faire se déplacer le joueur.
*/
void		move_p(t_player *player,
		       t_shared *shared,
		       t_position to_reach)
{
  int		x_delta;
  int		y_delta;
  int		moved;

  moved = 1;
  x_delta = to_reach.x - player->p_position.x;
  y_delta = to_reach.y - player->p_position.y;
  if (ABS(x_delta) < ABS(y_delta))
    {
      if ((moved = move_p_vertical(player, shared->board,
				   y_delta, shared)) == 0)
  	moved = move_p_horizontal(player, shared->board, x_delta, shared);
    }
  else if ((moved = move_p_horizontal(player, shared->board,
				      x_delta, shared)) == 0)
    moved = move_p_vertical(player, shared->board, y_delta, shared);
  if (moved == 0 && ((ABS(x_delta) > 1 || ABS(y_delta) > 1)))
    move_randomly(player, shared->board, shared);
}
