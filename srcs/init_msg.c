/*
** init_msg.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sat Mar 25 21:07:37 2017 Arnaud WURMEL
** Last update Sat Apr  1 14:09:06 2017 Victorien Fischer
*/

#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "lemipc.h"

/*
** unsigned char init_msg(t_shared *shared)
**
** shared : données partagées
**
** Cette fonction init. la message queue.
*/
unsigned char	init_msg(t_shared *shared)
{
  shared->msgid = msgget(shared->key, SHM_R | SHM_W);
  if (shared->msgid == -1 && errno == ENOENT)
    {
      shared->msgid = msgget(shared->key, IPC_CREAT | SHM_R | SHM_W);
      printf("Created message queue with id : %d\n", shared->msgid);
    }
  if (shared->msgid == -1)
    return (lemi_errno(0));
  return (1);
}
