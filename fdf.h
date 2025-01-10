/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:45 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/10 14:54:25 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1600
# define HEIGHT 1600

// keyscode
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_I 105
# define KEY_Z 122
# define KEY_O 111
# define KEY_P 112
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_SPACE 32

# define KEY_ESC 65307

typedef struct s_dimensions
{
	int				width;
	int				height;
}					t_dimensions;
typedef enum e_projection
{
	ISO,
	PARALLEL_TOP,
	PARALLEL_FRONT,
	PARALLEL_SIDE
}					t_projection;

typedef struct s_scale
{
	float			base;
	float			z_scale;
	float			iso_angle;
	float			zoom_factor;
	t_projection	projection;
}					t_scale;

typedef struct s_offset
{
	int				x;
	int				y;
	int				offset_x;
	int				offset_y;
}					t_offset;

typedef struct s_height_range
{
	int				min;
	int				max;
}					t_height_range;

typedef struct s_map
{
	t_dimensions	dim;
	t_scale			scale;
	t_offset		center;
	t_height_range	height;
}					t_map;

typedef struct s_map_context
{
	t_map			*map;
	int				i;
	int				j;
}					t_map_context;

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	int				color;
}					t_point;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	char			*window_name;
	t_image			*img;
	t_point			**points;
	t_dimensions	dim;
	t_map			*map;
}					t_vars;

typedef struct s_bounds
{
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
}					t_bounds;

# define ERR_MLX_INIT "Error initializing mlx"
# define ERR_WIN_CREATE "Error creating window"
# define ERR_IMG_CREATE "Error creating image"

void				cleanup_image(t_vars *vars);
void				cleanup_window(t_vars *vars);
void				init_fdf(t_vars *vars);
void				create_image(t_vars *vars);

// File operations
int					open_map_file(char *file_name);
void				ft_free_strs(char **strs);
t_map				map_dimension(char *file_name);

// projection
void				project_point(t_point *a, t_map *map);
void				parallel_point_top(t_point *a);
void				parallel_point_front(t_point *a);
void				parallel_point_side(t_point *a);
void				apply_projection(t_point **points, t_map *map);

// Height processing
int					calculate_color(int height, t_height_range *range);
void				calculate_scale(t_map *map);
void				find_height_range(char *file_name, t_map *map);

// Point management
void				parse_map(t_point **points, char *file_name, t_map *map);
void				free_points(int map_height, t_point **points);
t_point				**points_init(t_map *map);

// Transformation
void				find_map_boundaries(t_point **points, t_map *map,
						t_bounds *bounds);
void				move_map(t_point **points, t_map *map, int new_offset_x,
						int new_offset_y);
void				iso_point(t_point *a, float angle);
void				iso_points(t_vars *vars);
void				update_zoom(t_vars *vars, float zoom_delta);

// Utility functions
int					ft_words_count(char const *s, char c);
char				**ft_split(char const *s, char c);
int					ft_atoi(const char *str);

// Pixel operations
void				put_pixel(t_vars *vars, int x, int y, int color);
int					interpolate_color(int color1, int color2, float fraction);

// Line drawing
void				draw_line_low_slope(t_vars *vars, int dx, int dy,
						t_point *a, t_point *b);
void				draw_line_high_slope(t_vars *vars, int dx, int dy,
						t_point *a, t_point *b);
void				draw_line(t_vars *vars, t_point a, t_point b);

// Main drawing
void				main_draw(t_vars *vars);

// Event handling
int					close_window_esc(int keycode, t_vars *vars);
int					close_window_x(t_vars *vars);
int					reset_shape(int keycode, t_vars *vars, int *total_offset_x,
						int *total_offset_y);
void				change_projection(t_vars *vars);
int					handle_movement(int keycode, t_vars *vars);
int					zoom_in_and_out(int keycode, t_vars *vars);
int					rotate(int keycode, t_vars *vars);
void				mlx_hooks(t_vars *vars, char *str);

// rotation
void				rotate_point(t_point *point, float angle, char axis,
						t_bounds *bounds);
void				apply_rotation(t_vars *vars, float angle, char axis);
void				draw_new_image(t_vars *vars);

#endif