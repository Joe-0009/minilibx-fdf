/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:34:09 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/19 11:47:33 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calculate_color(int height, t_height_range range, int color)
{
	float	height_percent;

	if (height == 0)
		return (color);
	if (range.max == range.min)
		return (color);
	height_percent = (float)(height - range.min) / (range.max - range.min);
	if (height_percent < 0)
		height_percent = 0;
	if (height_percent > 1)
		height_percent = 1;
	return (0xFFFFFF - (int)(height_percent * 0x00FFFF));
}

static void	create_point(t_vars *vars, char **color_split,
		t_map_context *context)
{
	int		height;
	t_point	*point;

	point = &vars->points[context->i][context->j];
	height = ft_atoi(color_split[0], vars);
	point->x = context->j * vars->map->scale.base;
	point->y = context->i * vars->map->scale.base;
	point->z = height * vars->map->scale.z_scale;
	if (color_split[1])
		point->color = ft_atoi_base(color_split[1] + 2, 16);
	else
		point->color = calculate_color(height, vars->map->height, 0x0000FF);
}

static void	parse_line(char *line, t_vars *vars, t_map_context *context)
{
	char	**split;
	char	**color_split;
	int		j;

	if (!vars->points)
		ft_error();
	j = -1;
	split = ft_split(line, ' ');
	if (!split)
		return ;
	while (split[++j])
	{
		color_split = ft_split(split[j], ',');
		if (!color_split)
		{
			ft_free_strs(split);
			free(line);
			return ;
		}
		context->j = j;
		create_point(vars, color_split, context);
		ft_free_strs(color_split);
	}
	ft_free_strs(split);
}

void	parse_map(t_vars *vars)
{
	int				fd;
	char			*line;
	t_map_context	context;

	find_height_range(vars);
	calculate_scale(vars->map);
	context.i = 0;
	fd = open_map_file(vars->window_name);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, vars, &context);
		context.i++;
		free(line);
		line = get_next_line(fd);
	}
	cleanup_gnl(fd);
	close(fd);
}

void	points_init(t_vars *vars)
{
	int	i;

	vars->points = malloc(vars->map->dim.height * sizeof(t_point *));
	if (!vars->points)
		ft_error();
	i = -1;
	while (++i < vars->map->dim.height)
	{
		vars->points[i] = malloc(vars->map->dim.width * sizeof(t_point));
		if (!vars->points[i])
		{
			while (--i >= 0)
				free(vars->points[i]);
			free(vars->points);
			ft_error();
		}
	}
}
