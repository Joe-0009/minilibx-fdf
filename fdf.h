#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 2000
# define HEIGHT 2000

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	*window_name;
	t_image	img;
}			t_vars;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
}			t_map;

void		init_fdf(t_vars *vars);
int			ft_words_count(char const *s, char c);
char		*ft_str_s_dup(char const *s, char c, int *start);
void		ft_free_strs(char **strs);
char		**ft_split(char const *s, char c);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			close_window_esc(int keycode, t_vars *vars);
int			close_window_x(t_vars *vars);
void		create_image(t_vars *vars);
void		put_pixel(t_vars *vars, int x, int y, int color);
int			interpolate_color(int color1, int color2, float fraction);
void		draw_line_low_slope(t_vars *vars, int dx, int dy, t_point *a,
				t_point *b);
void		draw_line_high_slope(t_vars *vars, int dx, int dy, t_point *a,
				t_point *b);
void		iso_point(t_point *a);
void		iso_points(t_point **points, int width, int height);
void		draw_line(t_vars *vars, t_point a, t_point b);
t_map		map_dimension(char *file_name);
void		parse_map(t_point **points, char *file_name, int spacing);
void		free_points(t_map *map, t_point **points);
t_point		**points_init(t_map *map);
void		main_draw(t_vars *vars, t_point **points, t_map *map);
void		mlx_hooks(t_vars *vars, char *str);

#endif