NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
MLX = libmlx.a

SRCS = main.c \
       fdf_events.c \
       fdf_events2.c \
       fdf_file_utils.c \
       fdf_height.c \
       fdf_init.c \
       fdf_draw.c \
       fdf_line.c \
       fdf_pixel.c \
       fdf_transform.c \
       fdf_parallel.c \
       fdf_utils.c \
       ft_split.c \
       rotation.c \
       fdf_points.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(MLX) $(FRAMEWORKS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all clean

.PHONY: all clean fclean re
