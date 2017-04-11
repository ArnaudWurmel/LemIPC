/*
** init_shm.c for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Sat Mar 25 00:14:51 2017 Arnaud WURMEL
** Last update Sun Apr  2 18:14:50 2017 Arnaud WURMEL
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lemipc.h"

/*
** Delete IPCs
*/
void	deinit_shm(const t_shared *shared)
{
  if (semaphore_lock(shared) == 0)
    {
      shmctl(shared->shmid, IPC_RMID, NULL);
      msgctl(shared->msgid, IPC_RMID, NULL);
      semctl(shared->semid, 1, IPC_RMID);
    }
}

/*
** static unsigned char init_board(const t_shared *shared)
**
** shared : les données partagées
**
** Cette fonction init la map partagée.
*/
static unsigned char	init_board(const t_shared *shared)
{
  void			*shm;

  if ((shm = shmat(shared->shmid, NULL, 0)) == (char *)-1)
    return (0);
  bzero(shm, sizeof(t_block) * MAP_WIDTH * MAP_HEIGHT);
  return (1);
}

/*
** unsigned char init_shm(...)
**
** shared : les données partagées
** path : chemin
**
** Cette fonction init la mémoire partagée.
*/
unsigned char	init_shm(t_shared *shared, const char *path)
{
  key_t		key;
  unsigned int	shsize;

  key = ftok(path, 13);
  if (key == -1)
    return (lemi_errno(0));
  shared->delegate = 0;
  shared->key = key;
  shsize = sizeof(t_block) * MAP_WIDTH * MAP_HEIGHT;
  shared->shmid = shmget(key, shsize, SHM_R | SHM_W);
  if (shared->shmid == -1 && errno == ENOENT)
    {
      shared->delegate = 1;
      shared->shmid = shmget(key, shsize, IPC_CREAT | SHM_R | SHM_W);
      if (shared->shmid != -1 && init_board(shared) == 0)
	return (1);
      printf("Create shm with id : %d\n", shared->shmid);
    }
  if (shared->shmid == -1)
    return (lemi_errno(0));
  shared->board = get_board(shared);
  if (shared->board == NULL)
    return (0);
  return (init_sem(shared));
}
