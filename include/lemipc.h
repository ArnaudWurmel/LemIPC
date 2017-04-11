/*
** lemipc.h for lemipc in /home/wurmel/rendu/PSU_2016_lemipc
** 
** Made by Arnaud WURMEL
** Login   <wurmel_a@epitech.net>
** 
** Started on  Mon Mar 20 10:58:09 2017 Arnaud WURMEL
** Last update Sun Apr  2 22:57:14 2017 Arnaud WURMEL
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

/*
** Boards informations
*/
# define MAP_WIDTH 30
# define MAP_HEIGHT 30
# define MAX_TEAM 8
# define SIGNAL_PROPAGATION 0

/*
** Macros
*/
# define ABS(my_val) ((my_val) < 0) ? -(my_val) : (my_val)
# define IS_NUMBER_CHAR(x) (x == '-' || x == '+' || (x >= '0' && x <= '9'))
# define BOARD_ID_POS(p) (p->p_position.x + (p->p_position.y * MAP_WIDTH))
# define BOARD_CALC(p) (p->x + (p->y * MAP_WIDTH))
# define CORRECT_X(x) (x >= 0 && x < MAP_WIDTH)
# define CORRECT_Y(y) (y >= 0 && y < MAP_HEIGHT)
# define CORRECT_POS(x, y) (CORRECT_X(x) && CORRECT_Y(y))

/*
** enum
*/
enum		e_playertype
  {
    FOLLOWER = 0,
    LEADER = 1
  };

/*
** Structures
*/
typedef struct	s_pos
{
  int		x;
  int		y;
}		t_pos;

typedef struct	s_position
{
  unsigned int	x;
  unsigned int	y;
}		t_position;

typedef struct	s_block
{
  unsigned int	team_number;
}		t_block;

typedef struct	s_player
{
  unsigned int	player_id;
  t_position	p_position;
  unsigned int	team_number;
  unsigned char	leader;
}		t_player;

typedef struct	s_shared
{
  key_t		key;
  int		shmid;
  int		semid;
  int		msgid;
  unsigned char	delegate;
  t_block	*board;
}		t_shared;

typedef struct	s_lemipc
{
  t_player	player;
  t_shared	shared;
  unsigned int	is_dead;
  unsigned int	should_leave;
}		t_lemipc;

/*
** Message queue structure / Enum
*/
enum		e_msgtype
  {
    DISPLAY = 1
  };

struct		s_message
{
  long int	mtype;
  unsigned int	team_id;
} __attribute__((packed));

typedef struct s_message t_message;

struct		s_order
{
  long int	mtype;
  t_position	acquire_pos;
  unsigned int	signal;
} __attribute__((packed));

typedef struct s_order t_order;

/*
** Contained into eval_arg.c
*/
t_lemipc	*eval_arg(const char **);

/*
** Contained into init_shm.c
*/
unsigned char	init_shm(t_shared *, const char *);
void		deinit_shm(const t_shared *);
/*
** Contained into init_sem.c
*/
unsigned char	init_sem(t_shared *);

/*
** Contained into init_msg.c
*/
unsigned char	init_msg(t_shared *);

/*
** Contained into error.c
*/
int		lemi_error(int, const char *, const char *);
int		lemi_errno(unsigned char);

/*
** Contained into board_manager.c
*/
void		detach_board(t_block *);
t_block		*get_board(const t_shared *);
unsigned char	board_create_p(t_shared *, t_player *);
unsigned char	board_have_player(const t_shared *);
void		board_delete_p(t_lemipc *);

/*
** Contained into semaphore_manager.c
*/
unsigned char	semaphore_lock(const t_shared *);
unsigned char	semaphore_unlock(const t_shared *);

/*
** Contained into player_manager.c
*/
t_position	player_position(const t_block *, char *);

/*
** Contained into display_manager.c
*/
void		display_starter(t_lemipc *);
unsigned char	can_start_game(const t_shared *);
unsigned int	last_player_in_board(const t_block *);

/*
** Contained into message_manager.c
*/
void		message_displayer(const t_player *, const t_shared *);

/*
** Contained into game_manager.c
*/
void		game_loop(t_lemipc *);

/*
** Contained into show_map.c
*/
void		display(const t_shared *);
void		display_exit();

/*
** =================================================>
** ===== > GAME
** =================================================>
*/
/*
** CHECKERS
*/
int		check_around(t_player *, const t_shared *);

/*
** MOVES
*/
void		move_p(t_player *, t_shared *, t_position);

/*
** UTILITIES
*/
int		get_pos_board(int, int);
int		board_is_team(const t_block *, int, int, unsigned int);
t_position	*create_position(unsigned int, unsigned int);

/*
** IA_MANAGER
*/
t_position	ia_position_reach(const t_player *,
				  const t_block *);
t_position	*get_closest_enemy(const t_player *,
				   const t_block *);

#endif /* !LEMIPC_H_ */
