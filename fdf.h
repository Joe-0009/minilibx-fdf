/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:45 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/13 12:32:02 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// System includes
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// Window dimensions
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

/*
** Type definitions
*/
typedef enum e_projection
{
	ISO,
	PARALLEL_TOP,
	PARALLEL_FRONT,
	PARALLEL_SIDE
}					t_projection;

// Geometry structures
typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	int				color;
}					t_point;

typedef struct s_line_params
{
	int				dx;
	int				dy;
	t_point			*start;
	t_point			*end;
}					t_line_params;

typedef struct s_bounds
{
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
}					t_bounds;

// Map structures
typedef struct s_dimensions
{
	int				width;
	int				height;
}					t_dimensions;

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

// Context and state structures
typedef struct s_map_context
{
	t_map			*map;
	int				i;
	int				j;
}					t_map_context;

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

/*
** Function prototypes
*/
// Point operations
void				ft_error(void);
void				points_init(t_vars *vars);
void				parse_map(t_vars *vars);
void				free_points(int map_height, t_point **points);

// Core initialization and cleanup
void				init_fdf(t_vars *vars);
void				cleanup_image(t_vars *vars);
void				cleanup_window(t_vars *vars);
void				create_image(t_vars *vars);
void				cleanup_all(t_vars *vars);

// Map operations and scaling
void				find_map_boundaries(t_point **points, t_map *map,
						t_bounds *bounds);
int					open_map_file(char *file_name);
void				calculate_scale(t_map *map);
void				find_height_range(t_vars *vars);
t_map				map_dimension(t_vars *vars);

// Transformations and movement
void				move_map(t_point **points, t_map *map, int new_offset_x,
						int new_offset_y);
void				update_zoom(t_vars *vars, float zoom_factor);
void				iso_point(t_point *a, float angle);
void				iso_points(t_vars *vars);

// Rotation
void				apply_rotation(t_vars *vars, float angle, char axis);

// Parallel
void				apply_projection(t_point **points, t_map *map);

// Drawing operations
int					interpolate_color(int color1, int color2, float fraction);
void				draw_new_image(t_vars *vars);
void				main_draw(t_vars *vars);
void				put_pixel(t_vars *vars, int x, int y, int color);
void				draw_line(t_vars *vars, t_point a, t_point b);

// Event handling
void				change_projection(t_vars *vars);
void				mlx_hooks(t_vars *vars, char *str);
int					handle_movement(int keycode, t_vars *vars);
int					zoom_in_and_out(int keycode, t_vars *vars);
int					rotate(int keycode, t_vars *vars);

// Utility functions
int					ft_words_count(char const *s, char c);
char				**ft_split(char const *s, char c);
int					ft_atoi(const char *str, t_vars *vars);
void				ft_free_strs(char **strs);
int					ft_atoi_base(char *str, int base);

#endif