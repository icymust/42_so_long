NAME    = so_long
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = src/main.c src/map.c src/map_check.c src/game_hooks.c src/game_utils.c \
src/game_render.c src/map_utils.c src/flood.c  src/flood_utils.c \

OBJS = $(SRCS:.c=.o)
LIBFT = lib/libft/libft.a
MLX = -Llib/mlx -lmlx -lz -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re