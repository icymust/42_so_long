NAME    = so_long
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = src/main.c src/map.c src/map_check.c src/game_hooks.c src/game_utils.c \
lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c \
lib/libft/ft_memset.c lib/libft/ft_strlen.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJS)
# 	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Llib/mlx -lmlx -lz -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re