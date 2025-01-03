#include "get_next_line/get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 2000
#define HEIGHT 2000

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

void	init_fdf(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		fprintf(stderr, "Error initializing mlx\n");
		exit(EXIT_FAILURE);
	}
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, vars->window_name);
	if (!vars->win)
	{
		fprintf(stderr, "Error creating window\n");
		free(vars->mlx);
		exit(EXIT_FAILURE);
	}
}

int	ft_words_count(char const *s, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && !word)
		{
			word = 1;
			count++;
		}
		else if (*s == c)
		{
			word = 0;
		}
		s++;
	}
	return (count);
}

static char	*ft_str_s_dup(char const *s, char c, int *start)
{
	char	*dup;
	int		end;
	int		i;

	end = 0;
	while (s[*start + end] && s[*start + end] != c)
		end++;
	dup = (char *)calloc(end + 1, 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < end)
	{
		dup[i] = s[*start];
		(*start)++;
		i++;
	}
	return (dup);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	strs = (char **)calloc((ft_words_count(s, c) + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c && s[i++])
			continue ;
		strs[j] = ft_str_s_dup(s, c, &i);
		if (!strs[j++])
			return (ft_free_strs(strs), NULL);
	}
	strs[j] = NULL;
	return (strs);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	result;

	sign = 1;
	result = 0;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > LONG_MAX)
		return (0 - (sign == 1));
	return (result * sign);
}

int	close_window_esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{ // Correct keycode for ESC in X11
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
	}
	return (0);
}

int	close_window_x(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit(0);
	return (0);
}

void	create_image(t_vars *vars)
{
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img.img)
	{
		fprintf(stderr, "Error creating image\n");
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(EXIT_FAILURE);
	}
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
}

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = vars->img.addr + (y * vars->img.line_length + x
				* (vars->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	interpolate_color(int color1, int color2, float fraction)
{
	int	red;
	int	green;
	int	blue;

	red = ((1 - fraction) * ((color1 >> 16) & 0xFF)) + (fraction
			* ((color2 >> 16) & 0xFF));
	green = ((1 - fraction) * ((color1 >> 8) & 0xFF)) + (fraction
			* ((color2 >> 8) & 0xFF));
	blue = ((1 - fraction) * (color1 & 0xFF)) + (fraction * (color2 & 0xFF));
	return ((red << 16) | (green << 8) | blue);
}

void	draw_line_low_slope(t_vars *vars, int dx, int dy, t_point *a,
		t_point *b)
{
	int		i;
	int		p;
	float	fraction;

	fraction = 0.05;
	i = -1;
	p = 2 * abs(dy) - abs(dx);
	put_pixel(vars, a->x, a->y, a->color);
	while (++i < abs(dx))
	{
		fraction = (float)i / abs(dx);
		if (dx > 0)
			a->x += 1;
		else
			a->x -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				a->y += 1;
			else
				a->y -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		put_pixel(vars, a->x, a->y, interpolate_color(a->color, b->color,
				fraction));
	}
}

void	draw_line_high_slope(t_vars *vars, int dx, int dy, t_point *a,
		t_point *b)
{
	int		p;
	int		i;
	float	fraction;

	fraction = 0.05;
	i = -1;
	p = 2 * abs(dx) - abs(dy);
	put_pixel(vars, a->x, a->y, a->color);
	while (++i < abs(dy))
	{
		fraction = (float)i / abs(dy);
		if (dy > 0)
			a->y += 1;
		else
			a->y -= 1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			if (dx > 0)
				a->x += 1;
			else
				a->x -= 1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		put_pixel(vars, a->x, a->y, interpolate_color(a->color, b->color,
				fraction));
	}
}

void	iso_point(t_point *a)
{
	int	prev_x;
	int	prev_y;

	prev_x = a->x;
	prev_y = a->y;
	// Isometric transformation
	a->x = (prev_x - prev_y) * cos(0.523599) + WIDTH / 2;         
		// cos(30 degrees)
	a->y = -a->z + (prev_x + prev_y) * sin(0.523599) + HEIGHT / 2;
		// sin(30 degrees)
}

void	draw_line(t_vars *vars, t_point a, t_point b)
{
	int	dx;
	int	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (abs(dx) > abs(dy))
		draw_line_low_slope(vars, dx, dy, &a, &b);
	else
		draw_line_high_slope(vars, dx, dy, &a, &b);
}

void	iso_points(t_point **points, int width, int height)
{
	int	i;
	int	j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			iso_point(&points[i][j]);
		}
	}
}

t_map	map_dimension(char *file_name)
{
	int		height;
	int		fd;
	char	*line;
	t_map	map;

	height = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)))
	{
		map.width = ft_words_count(line, ' ');
		height++;
		free(line);
	}
	close(fd);
	map.height = height;
	return (map);
}

void	parse_map(t_point **points, char *file_name, int spacing)
{
	int		fd;
	char	**split;
	int		j;
	int		i;
	char	*line;
	int		color;
	char	**color_split;

	i = 0;
	fd = open(file_name, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		j = 0;
		split = ft_split(line, ' ');
		while (split[j])
		{
			color_split = ft_split(split[j], ',');
			if (color_split[1])
			{
				points[i][j] = (t_point){j * spacing, i * spacing, spacing
					* ft_atoi(color_split[0]), (int)strtol(color_split[1], NULL,
						16)};
			}
			else
			{
				color = 0x277fba;
				if (ft_atoi(split[j]) != 0)
					color = 0x36a8f5;
				points[i][j] = (t_point){j * spacing, i * spacing, spacing
					* ft_atoi(split[j]), color};
			}
			ft_free_strs(color_split);
			j++;
		}
		ft_free_strs(split);
		free(line);
		i++;
	}
	close(fd);
}

void	free_points(t_map *map, t_point **points)
{
	int	i;

	for (i = 0; i < map->height; i++)
	{
		free(points[i]);
	}
	free(points);
}

t_point	**points_init(t_map *map)
{
	t_point	**points;
	int		i;

	points = (t_point **)malloc(map->height * sizeof(t_point *));
	if (!points)
	{
		fprintf(stderr, "Error allocating memory for points\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < map->height; i++)
	{
		points[i] = (t_point *)malloc(map->width * sizeof(t_point));
		if (!points[i])
		{
			fprintf(stderr, "Error allocating memory for points row\n");
			exit(EXIT_FAILURE);
		}
	}
	return (points);
}

void	main_draw(t_vars *vars, t_point **points, t_map *map)
{
	int i, j;
	for (i = 0; i < map->height; i++)
	{
		for (j = 0; j < map->width - 1; j++)
		{
			draw_line(vars, points[i][j], points[i][j + 1]);
		}
	}
	for (i = 0; i < map->height - 1; i++)
	{
		for (j = 0; j < map->width; j++)
		{
			draw_line(vars, points[i][j], points[i + 1][j]);
		}
	}
}

void	mlx_hooks(t_vars *vars, char *str)
{
	vars->window_name = str;
	init_fdf(vars);
	mlx_hook(vars->win, 2, 1L << 0, close_window_esc, vars);
	mlx_hook(vars->win, 17, 0, close_window_x, vars);
	create_image(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_point	**points;
	t_map	map;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	map = map_dimension(argv[1]);
	points = points_init(&map);
	mlx_hooks(&vars, argv[1]);
	parse_map(points, argv[1], 0.01 * HEIGHT);
	iso_points(points, map.width, map.height);
	main_draw(&vars, points, &map);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
	free_points(&map, points);
	return (EXIT_SUCCESS);
}
