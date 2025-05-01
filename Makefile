# File: Makefile

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDES= -I./
SRC		= main.c philo_routine.c utils.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
    $(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -pthread -o $@

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re: fclean all
