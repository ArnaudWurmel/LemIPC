/*
** game_manager.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sun Mar 26 23:10:46 2017 Arnaud WURMEL
** Last update Sun Apr  2 22:11:47 2017 Arnaud WURMEL
*/

#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "lemipc.h"

/*
** static unsigned char have_position_in_queue(...)
**
** shared : données partagées
** message_id : id du message
** pos : la position à vérifier
**
** Renvoie 1 si pos est dans le message message_id.
** Sinon 0.
*/
static unsigned char	have_position_in_queue(const t_shared *shared,
					       unsigned int message_id,
					       t_position *pos)
{
  t_order		order;

  if (msgrcv(shared->msgid, &order, sizeof(t_order) - sizeof(long int),
	     message_id, IPC_NOWAIT) > 0)
    {
      pos->x = order.acquire_pos.x;
      pos->y = order.acquire_pos.y;
      order.mtype = message_id;
      if (order.signal != 0)
	{
	  order.signal -= 1;
	  msgsnd(shared->msgid, &order, sizeof(t_order) - sizeof(long int),
		 IPC_NOWAIT);
	}
      return (1);
    }
  return (0);
}

/*
** static void	get_reachable_pos_rt(...)
**
** Suite de get_reachable_pos.
*/
static void	get_reachable_pos_rt(t_position *ret, t_position *tmp)
{
  ret->x = tmp->x;
  ret->y = tmp->y;
  free(tmp);
}

/*
** static t_position	get_reachable_pos(...)
**
** shared : données partagées
** player : le joueur
** end : valeur modifiée si fin
**
** Cette fonction renvoie la position que devra atteindre le joueur
*/
static t_position	get_reachable_pos(const t_shared *shared,
					  t_player *player,
					  char *end)
{
  t_order		order;
  t_position		ret;
  t_position		*tmp;

  bzero(&ret, sizeof(t_position));
  if (player->leader == FOLLOWER &&
      have_position_in_queue(shared, player->team_number + 1, &ret))
    player->leader = FOLLOWER;
  else
    {
      player->leader = LEADER;
      if ((tmp = get_closest_enemy(player, shared->board)) != NULL)
	get_reachable_pos_rt(&ret, tmp);
      else
	*end = 1;
      order.mtype = player->team_number + 1;
      order.acquire_pos.x = ret.x;
      order.acquire_pos.y = ret.y;
      order.signal = SIGNAL_PROPAGATION;
      msgsnd(shared->msgid, &order,
	     sizeof(t_order) - sizeof(long int), IPC_NOWAIT);
    }
  return (ret);
}

/*
** static void	check_end_game(t_lemipc *lemipc)
**
** lemipc : structure du joueur courant
**
** Vérifie si le jeu est fini pour le joueur courant.
*/
static void	check_end_game(t_lemipc *lemipc)
{
  if (lemipc->is_dead == 0)
    {
      if (semaphore_lock(&lemipc->shared) == 0)
	{
	  board_delete_p(lemipc);
	  semaphore_unlock(&lemipc->shared);
	}
      else
	exit(1);
    }
}

/*
** void		game_loop(t_lemipc *lemipc)
**
** lemipc : Données du joueur.
**
** Cette fonction va faire vivre le joueur lemipc.
*/
void		game_loop(t_lemipc *lemipc)
{
  t_position	point;
  char		e;

  e = 0;
  while (lemipc->is_dead == 0 && can_start_game(&lemipc->shared) == 0);
  while (lemipc->is_dead == 0 && e == 0 &&
	 last_player_in_board(lemipc->shared.board) == 0)
    {
      if (semaphore_lock(&lemipc->shared) == 0)
	{
	  if (check_around(&lemipc->player, &lemipc->shared))
	    board_delete_p(lemipc);
	  else
	    {
	      point = get_reachable_pos(&lemipc->shared, &lemipc->player, &e);
	      if (!e)
		move_p(&lemipc->player, &lemipc->shared, point);
	    }
	  semaphore_unlock(&lemipc->shared);
	}
      else
	e = 1;
    }
  check_end_game(lemipc);
}
