/*
** main.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Mon Mar 20 10:43:29 2017 Arnaud WURMEL
** Last update Sun Apr  2 19:00:09 2017 Arnaud WURMEL
*/

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "lemipc.h"

static void		init_rand()
{
  struct timeval	time;

  gettimeofday(&time, NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void		handler(int signum,
				siginfo_t *siginfo,
				void *context)
{
  static t_lemipc	*lemipc = NULL;

  (void)siginfo;
  if (signum == -42 && context)
    lemipc = (t_lemipc *)context;
  else if (lemipc && signum == SIGINT)
    {
      lemipc->should_leave = 1;
      if (semaphore_lock(&lemipc->shared) == 0)
	{
	  board_delete_p(lemipc);
	  semaphore_unlock(&lemipc->shared);
	}
    }
}

static void		init_sigaction(t_lemipc *lemipc)
{
  struct sigaction	act;

  bzero(&act, sizeof(struct sigaction));
  act.sa_sigaction = &handler;
  act.sa_flags = SA_SIGINFO;
  handler(-42, NULL, lemipc);
  sigaction(SIGINT, &act, NULL);
}

/*
** int		main(int ac, const char **av)
**
** Fonction principale du lemipc.
** Return 1 si le programme échoue.
*/
int		main(int ac, const char **av)
{
  t_lemipc	*lemipc;

  if (ac != 3)
    {
      fprintf(stderr, "%s: Argument error"
	      "\n%s [PATH_SHARED] [TEAM_NUMBER]\n", av[0], av[0]);
      return (1);
    }
  init_rand();
  if (!(lemipc = eval_arg(&av[1])) ||
      board_create_p(&lemipc->shared, &lemipc->player) == 0)
    return (1);
  init_sigaction(lemipc);
  if (lemipc->shared.delegate)
    display_starter(lemipc);
  else
    game_loop(lemipc);
  if (board_have_player(&lemipc->shared) == 0)
    deinit_shm(&lemipc->shared);
  free(lemipc);
  return (0);
}
