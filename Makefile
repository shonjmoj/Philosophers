CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = philo/philosophers.a

SRC = ft_atoi.c \
		philo/utils.c \
		philo/print.c \

OBJ = ${SRC:.c=.o}

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)
	$(CC) $(CFLAGS) -lpthread philo/philosophers.c $(NAME) -o philo_m

all : $(NAME)

%.o : %.c philosophers.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME) a.out philo_m

re : fclean all