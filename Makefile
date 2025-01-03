NAME = fdf
CC = gcc
CFLAGS = -Os -Ofast -Wall -Wextra -Werror
MLX_FLAGS = -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
SRCS = fdf_initialization.c \
    fdf_utils.c \
    fdf_events.c \
    fdf_drawing.c \
    fdf_transform.c \
    fdf_map.c \
    main.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
    $(CC) $(CFLAGS) -Imlx_linux -c $< -o $@

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) libmlx.a $(MLX_FLAGS) -o $@

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
