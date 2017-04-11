/*
** board_manager.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sat Mar 25 22:20:14 2017 Arnaud WURMEL
** Last update Sun Apr  2 17:09:48 2017 Arnaud WURMEL
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "lemipc.h"

/*
** void	detach_board(t_block *board)
**
** board : la map
**
** Détache le board (free);
*/
void	detach_board(t_block *board)
{
  shmdt(board);
}

/*
** static t_player	*get_board(const t_shared *shared)
**
** Renvoie le board.
*/
t_block		*get_board(const t_shared *shared)
{
  void		*shm;
  t_block	*board;

  if ((shm = shmat(shared->shmid, NULL, 0)) == (char *)-1)
    return (NULL);
  board = (t_block *)shm;
  return (board);
}

/*
** unsigned char	board_have_player(const t_shared *shared)
**
** Vérifie si le board contient des joueurs.
*/
unsigned char	board_have_player(const t_shared *shared)
{
  unsigned int	idx;

  idx = 0;
  while (idx < MAP_WIDTH * MAP_HEIGHT)
    {
      if (shared->board[idx].team_number)
	return (1);
      ++idx;
    }
  return (0);
}

/*
** unsigned char	board_create_p(const t_shared *shared,
**				       t_player *player)
**
** Ajoute un joueur au board.
*/
unsigned char	board_create_p(t_shared *shared,
			       t_player *player)
{
  char		err;

  if (semaphore_lock(shared))
    return (0);
  err = 0;
  player->p_position = player_position(shared->board, &err);
  if (err == 0)
    {
      shared->board[BOARD_ID_POS(player)].team_number = player->team_number;
    }
  player->player_id = rand() % 1280;
  semaphore_unlock(shared);
  return (!err);
}

/*
** void		board_delete_p(const t_shared *shared,
**			       const t_player *player)
**
** Supprime un joueur du board.
*/
void		board_delete_p(t_lemipc *lemipc)
{
  t_player	*player;

  player = &lemipc->player;
  memset(&(lemipc->shared.board[BOARD_ID_POS(player)]), 0, sizeof(t_block));
  message_displayer(&lemipc->player, &lemipc->shared);
  lemipc->is_dead = 1;
}
