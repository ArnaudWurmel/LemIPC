/*
** show_map.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Mon Mar 27 14:35:47 2017 Arnaud WURMEL
** Last update Sat Apr  1 18:41:50 2017 Arnaud WURMEL
*/

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "lemipc.h"

/*
** void		board_displayer(const t_shared *shared)
**
** Affiche le board des joueurs.
*/
void		display(const t_shared *shared)
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  while (y < MAP_HEIGHT)
    {
      x = 0;
      while (x < MAP_WIDTH)
	{
	  printf("%d", shared->board[x + (y * MAP_WIDTH)].team_number);
	  if (x + 1 < MAP_WIDTH)
	    printf(" ");
	  ++x;
	}
      printf("\n");
      ++y;
    }
  printf("\n");
}

/*
** SDL Only
*/
void	display_exit()
{

}
