/*
** semaphore_manager.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sun Mar 26 21:37:15 2017 Arnaud WURMEL
** Last update Sun Apr  2 22:12:15 2017 Arnaud WURMEL
*/

#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/sem.h>
#include "lemipc.h"

/*
** unsigned char semaphore_lock(const t_shared *shared)
**
** shared : les données partagées
**
** Lock la sémaphore.
*/
unsigned char	semaphore_lock(const t_shared *shared)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = -1;
  if (semop(shared->semid, &sops, 1) == -1)
    exit(1);
  return (0);
}

/*
** unsigned char semaphore_unlock(const t_shared *shared)
**
** shared : les données partagées
**
** Unlock la sémaphore.
*/
unsigned char	semaphore_unlock(const t_shared *shared)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = 1;
  if (semop(shared->semid, &sops, 1) == -1)
    exit(1);
  usleep(100000);
  return (0);
}
