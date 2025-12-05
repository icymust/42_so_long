NAME = so_long
BONUS_NAME = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/map.c src/map_check.c src/game_hooks.c src/game_utils.c \
src/game_render.c src/map_utils.c src/flood.c src/flood_utils.c

BONUS = bonus/main.c bonus/map.c bonus/map_check.c bonus/game_hooks.c bonus/game_utils.c \
bonus/game_render.c bonus/map_utils.c bonus/flood.c bonus/flood_utils.c bonus/alien_move.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)
LIBFT = lib/libft/libft.a
MLX = -Llib/mlx -lmlx -lz -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(MLX) $(LIBFT) -o $(BONUS_NAME)

all: $(NAME)

bonus: $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus