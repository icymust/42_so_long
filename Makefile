NAME    = so_long
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = main.c lib/gnl/get_next_line.c \
lib/gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJS)
# 	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -lz -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re