CC = gcc

CFLAGS = -c -Wextra -Wall -Werror

LIB_SRCS = libft/ft_putstr.c \
			libft/ft_bzero.c \
			libft/ft_putchar.c

LIB_OBJS = ft_putstr.o \
			ft_bzero.o \
			ft_putchar.o \

SRCS = check.c \
		map.c \
		main.c

OBJS = $(SRCS:.c=.o)

NAME = fillit

all: $(NAME)

$(NAME): $(OBJS) $(LIB_OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIB_OBJS)

ft_%.o : libft/ft_%.c
	$(CC) $(CFLAGS) -c $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f $(OBJS) $(LIB_OBJS)

fclean: clean
	-rm -f $(NAME)
	
re: fclean all
