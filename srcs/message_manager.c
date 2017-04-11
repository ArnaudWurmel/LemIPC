/*
** message_manager.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Mon Mar 27 11:12:26 2017 Arnaud WURMEL
** Last update Sat Apr  1 14:45:28 2017 Victorien Fischer
*/

#include <sys/types.h>
#include <sys/msg.h>
#include "lemipc.h"

/*
** void		message_displayer
**
** player : le joueur
** shared : données partagées
**
** Envoie un message dont l'auteur est le joueur.
*/
void		message_displayer(const t_player *player,
				  const t_shared *shared)
{
  t_message	message;

  message.mtype = DISPLAY;
  message.team_id = player->team_number;
  msgsnd(shared->msgid, &message, sizeof(t_message) - sizeof(long int),
	 IPC_NOWAIT);
}
