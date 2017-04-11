/*
** eval_arg.c for lemIPC in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Fri Mar 24 23:56:14 2017 Arnaud WURMEL
** Last update Sun Apr  2 20:59:39 2017 Victorien Fischer
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "lemipc.h"

/*
** Checks if string is a number
** Prints an error message otherwise
**
** Possible return value :
** - 0: Not a number
** - 1: Is a number
*/
static unsigned char	is_num(const char *string)
{
  unsigned int		idx;

  idx = -1;
  while (string[++idx])
    if (!(IS_NUMBER_CHAR(string[idx])))
      return (lemi_error(0, string, "'%s': Isn't a number.\n"));
  if (atoi(string) <= 0)
    return (lemi_error(0, string, "'%s': Must be a positive number.\n"));
  return (1);
}

/*
** Checks if path is a directory
** Prints an error message otherwise
**
** Return values :
** - 0: Not a directory
** - 1: Is directory
*/
static unsigned char	is_directory(const char *path)
{
  struct stat		sb;

  if (stat(path, &sb))
    return (lemi_error(0, path, "'%s': No such file or directory.\n"));
  if (sb.st_mode & S_IFDIR)
    return (1);
  return (lemi_error(0, path, "'%s': Isn't a directory.\n"));
}

/*
** Initializes t_lemipc with arg value
**
** Return value :
** - NULL: Parsing arg failed, error report on stderr
** - t_lemipc *: Parsing succefully executed
*/
t_lemipc	*eval_arg(const char **to_eval)
{
  t_lemipc	*ret;

  if (is_directory(to_eval[0]) == 0 || is_num(to_eval[1]) == 0)
    return (NULL);
  if ((ret = malloc(sizeof(t_lemipc))) == NULL)
    return (NULL);
  memset(ret, 0, sizeof(t_lemipc));
  ret->player.team_number = (atoi(to_eval[1]) % MAX_TEAM) + 1;
  if (init_shm(&ret->shared, to_eval[0]) == 0)
    {
      free(ret);
      return (NULL);
    }
  return (ret);
}
