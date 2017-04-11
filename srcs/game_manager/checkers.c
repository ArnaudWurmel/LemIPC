/*
** checkers.c for lemipc in /home/vicky/Bureau/EPITECH/tek2-2/PSU/PSU_2016_lemipc/srcs/game_manager
** 
** Made by Victorien Fischer
** Login   <victorien.fischer@epitech.eu>
** 
** Started on  Wed Mar 29 17:49:41 2017 Victorien Fischer
** Last update Sun Apr  2 18:07:16 2017 Arnaud WURMEL
*/

#include <string.h>
#include <sys/types.h>
#include "lemipc.h"

/*
** int		check_around_condition(size_t my, size_t *around)
**
** my : la team du joueur actuellement checké
** around : les teams des joueurs autour
**
** Renvoie 1 si my est entouré de deux de la même team
** (différente de la sienne et de 0 (case vide))
*/
static int	check_around_condition(unsigned int my, unsigned int *around)
{
  int		i;
  int		j;

  i = -1;
  while (++i < 4)
    {
      j = i;
      while (++j < 4)
	if (around[i] == around[j])
	  if (around[i] != 0 && around[i] != my)
	    return (1);
    }
  return (0);
}

/*
** int		check_around(t_player *player, const t_shared *shared)
**
** player : le joueur
** shared : les données partagées
**
** Cette fonction regarde autour du joueur pour savoir s'il est mort
*/
int		check_around(t_player *player, const t_shared *shared)
{
  int		x;
  int		y;
  unsigned int	around[8];

  x = (int)(player->p_position.x);
  y = (int)(player->p_position.y);
  bzero(around, sizeof(unsigned int) * 8);
  if (CORRECT_POS(x, y - 1))
    around[0] = shared->board[get_pos_board(x, y - 1)].team_number;
  if (CORRECT_POS(x + 1, y))
    around[1] = shared->board[get_pos_board(x + 1, y)].team_number;
  if (CORRECT_POS(x, y + 1))
    around[2] = shared->board[get_pos_board(x, y + 1)].team_number;
  if (CORRECT_POS(x - 1, y))
    around[3] = shared->board[get_pos_board(x - 1, y)].team_number;
  if (CORRECT_POS(x - 1, y - 1))
    around[4] = shared->board[get_pos_board(x - 1, y - 1)].team_number;
  if (CORRECT_POS(x + 1, y - 1))
    around[5] = shared->board[get_pos_board(x + 1, y - 1)].team_number;
  if (CORRECT_POS(x - 1, y + 1))
    around[6] = shared->board[get_pos_board(x - 1, y + 1)].team_number;
  if (CORRECT_POS(x + 1, y + 1))
    around[7] = shared->board[get_pos_board(x + 1, y + 1)].team_number;
  return (check_around_condition(player->team_number, around));
}
