NAME = so_long
BONUS_NAME = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/map.c src/map_check.c src/game_hooks.c src/game_utils.c \
src/game_render.c src/map_utils.c src/flood.c src/flood_utils.c

BONUS = bonus/main.c bonus/map.c bonus/map_check.c bonus/game_hooks.c bonus/game_utils.c \
bonus/game_render.c bonus/map_utils.c bonus/flood.c bonus/flood_utils.c bonus/alien_move.c \
bonus/game_render_end.c bonus/alien_move_utils.c 

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)
LIBFT = lib/libft/libft.a
MLX_LIB = lib/mlx/libmlx.a
MLX = -Llib/mlx -lmlx -lz -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	make -C lib/libft

$(MLX_LIB):
	make -C lib/mlx

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(LIBFT) $(MLX_LIB) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(MLX) $(LIBFT) -o $(BONUS_NAME)

bonus: $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make -C lib/libft clean
	make -C lib/mlx clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C lib/libft fclean
	make -C lib/mlx clean

re: fclean all

.PHONY: all clean fclean re bonus