/*
** display_manager.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sun Mar 26 22:18:13 2017 Arnaud WURMEL
** Last update Sun Apr  2 23:10:07 2017 Arnaud WURMEL
*/

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include "lemipc.h"

/*
** unsigned char can_start_game(...)
**
** shared : données partagées
**
** Renvoie 1 si la partie peut démarrer, 0 sinon.
*/
unsigned char	can_start_game(const t_shared *shared)
{
  unsigned int	team_count[MAX_TEAM];
  unsigned int	idx;
  unsigned int	save;

  bzero(team_count, sizeof(unsigned int) * MAX_TEAM);
  idx = 0;
  while (idx < MAP_WIDTH * MAP_HEIGHT)
    {
      if (shared->board[idx].team_number)
	team_count[(shared->board[idx].team_number - 1) % MAX_TEAM] += 1;
      ++idx;
    }
  idx = 0;
  save = 0;
  while (idx < MAX_TEAM)
    {
      if (team_count[idx] > 1 && !save)
	save = 1;
      else if (team_count[idx] > 1 && save)
	return (1);
      ++idx;
    }
  return (0);
}

/*
** static unsigned int	last_player_in_board(...)
**
** board : la map
**
** Renvoie l'id du dernier joueur sur la map.
** Si plusieurs teams encore présentes, renvoie 0.
*/
unsigned int	last_player_in_board(const t_block *board)
{
  unsigned int	idx;
  unsigned int	save;

  idx = 0;
  save = 0;
  while (idx < MAP_WIDTH * MAP_HEIGHT)
    {
      if (board[idx].team_number)
	{
	  if (save == 0)
	    save = board[idx].team_number;
	  else if (save && board[idx].team_number != save)
	    return (0);
	}
      ++idx;
    }
  return (save);
}

/*
** static void	*display_thread(void *ptr_shared)
*/
static void	*display_thread(void *ptr_lemipc)
{
  t_lemipc	*lemipc;
  t_shared	*shared;
  t_message	message;
  unsigned int	size;
  unsigned int	ret;

  size = sizeof(t_message) - sizeof(long int);
  lemipc = (t_lemipc *)ptr_lemipc;
  shared = &lemipc->shared;
  while (can_start_game(shared) == 0 && lemipc->should_leave == 0)
    display(shared);
  ret = 0;
  while (board_have_player(shared) && lemipc->should_leave == 0)
    {
      if (!ret && (ret = last_player_in_board(shared->board)))
	printf("Winner : %d\n", ret);
      if (msgrcv(shared->msgid, &message, size, DISPLAY, IPC_NOWAIT) > 0)
	{
	  display(shared);
	}
    }
  display_exit();
  pthread_exit(NULL);
  return (NULL);
}

/*
** void		display_started(t_lemipc *lemipc)
**
** lemipc : structure du joueur
**
** Démarre l'affichage du programme et lance le
** premier joueur.
*/
void		display_starter(t_lemipc *lemipc)
{
  pthread_t	thread;

  if (pthread_create(&thread, NULL, display_thread, lemipc))
    return ;
  game_loop(lemipc);
  pthread_join(thread, NULL);
}
