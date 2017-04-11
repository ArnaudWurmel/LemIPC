/*
** init_sem.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sat Mar 25 20:50:38 2017 Arnaud WURMEL
** Last update Sat Apr  1 14:42:10 2017 Victorien Fischer
*/

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "lemipc.h"

/*
** unsigned char init_sem(t_shared *shared)
**
** shared : données partagées
**
** Cette fonction init les sémaphores.
*/
unsigned char	init_sem(t_shared *shared)
{
  shared->semid = semget(shared->key, 1, SHM_R | SHM_W);
  if (shared->semid == -1 && errno == ENOENT)
    {
      shared->semid = semget(shared->key, 1, IPC_CREAT | SHM_R | SHM_W);
      printf("Created sem %d\n", shared->semid);
      semctl(shared->semid, 0, SETVAL, 1);
    }
  if (shared->semid == -1)
    return (lemi_errno(0));
  return (init_msg(shared));
}
