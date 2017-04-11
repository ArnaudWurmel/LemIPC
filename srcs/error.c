/*
** error.c for lemipc in /home/fischerv/delivery/PSU/PSU_2016_lemipc
** 
** Made by Victorien Fischer
** Login   <fischerv@epitech.net>
** 
** Started on  Sat Mar 25 02:04:54 2017 Victorien Fischer
** Last update Sat Mar 25 02:25:22 2017 Victorien Fischer
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>

/*
** Prints an error depending on errno
** Returns value passed as parameter
*/
int	lemi_errno(unsigned char value)
{
  fprintf(stderr, "%s\n", strerror(errno));
  return (value);
}

/*
** Prints an error passed as parameter
** Returns value passed as parameter too
*/
int	lemi_error(int value, const char *binary, const char *msg)
{
  fprintf(stderr, msg, binary);
  return (value);
}
