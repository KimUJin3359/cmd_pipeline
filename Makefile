CC = gcc
CFAGS = -Wall -Werror -Wextra

NAME = pipex

INCDIR = ./includes/

SRCS = ./srcs/ft_main.c \
       ./srcs/ft_pipe.c \
       ./srcs/ft_split.c \
       ./srcs/ft_strjoin.c

OBJS = ${SRCS:.c=.o}

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCDIR)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean :
	rm -rf ./srcs/*.o

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
