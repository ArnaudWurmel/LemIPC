##
## Makefile for LemIPC in /home/wurmel/rendu/PSU_2016_lemipc
## 
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
## 
## Started on  Mon Mar 20 10:45:39 2017 Arnaud WURMEL
## Last update Sat Apr  1 15:45:26 2017 Victorien Fischer
##

RM=		rm -f

SRCS_PATH=	srcs

SRCS=		$(SRCS_PATH)/main.c			\
		$(SRCS_PATH)/eval_arg.c			\
		$(SRCS_PATH)/init_sem.c			\
		$(SRCS_PATH)/init_shm.c			\
		$(SRCS_PATH)/init_msg.c			\
		$(SRCS_PATH)/board_manager.c		\
		$(SRCS_PATH)/semaphore_manager.c	\
		$(SRCS_PATH)/player_manager.c		\
		$(SRCS_PATH)/display_manager.c		\
		$(SRCS_PATH)/message_manager.c		\
		$(SRCS_PATH)/game_manager.c		\
		$(SRCS_PATH)/game_manager/moves.c	\
		$(SRCS_PATH)/game_manager/checkers.c	\
		$(SRCS_PATH)/game_manager/ia_manager.c	\
		$(SRCS_PATH)/game_manager/utilities.c	\
		$(SRCS_PATH)/show_map.c			\
		$(SRCS_PATH)/error.c

SRCS_BONUS=	$(SRCS_PATH)/main.c			\
		$(SRCS_PATH)/eval_arg.c			\
		$(SRCS_PATH)/init_sem.c			\
		$(SRCS_PATH)/init_shm.c			\
		$(SRCS_PATH)/init_msg.c			\
		$(SRCS_PATH)/board_manager.c		\
		$(SRCS_PATH)/semaphore_manager.c	\
		$(SRCS_PATH)/player_manager.c		\
		$(SRCS_PATH)/display_manager.c		\
		$(SRCS_PATH)/message_manager.c		\
		$(SRCS_PATH)/game_manager.c		\
		$(SRCS_PATH)/game_manager/moves.c	\
		$(SRCS_PATH)/game_manager/checkers.c	\
		$(SRCS_PATH)/game_manager/ia_manager.c	\
		$(SRCS_PATH)/game_manager/utilities.c	\
		bonus/show_map.c			\
		bonus/get_values.c			\
		$(SRCS_PATH)/error.c

OBJS=		$(SRCS:.c=.o)

OBJS_BONUS=	$(SRCS_BONUS:.c=.o)

NAME=		lemipc

CC=		gcc

CFLAGS+=	-I ./include -Wall -Wextra -Werror -I ~/.csfml/

LD_FLAGS=	-lpthread

LD_BONUS=	-lcsfml-graphics -lcsfml-window -lcsfml-window

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LD_FLAGS)

bonus:		$(OBJS_BONUS)
		$(CC) $(OBJS_BONUS) -o $(NAME) $(LD_FLAGS) $(LD_BONUS)

clean:
		$(RM) $(OBJS)
		$(RM) $(OBJS_BONUS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

all:		$(NAME)
