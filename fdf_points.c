/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:34:09 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/19 20:00:31 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// kffedsf
int	calculate_color(int height, t_height_range range)
{
	float	height_percent;

	if (height == range.min)
		return (0x00008B);
	if (height == range.max)
		return (0xFFFFFF);
	if (range.max == range.min)
		return (0xFFFFFF);
	height_percent = (float)(height - range.min) / (range.max - range.min);
	if (height_percent < 0.25)
		return (interpolate_color(0x00008B, 0x228B22, height_percent * 4));
	else if (height_percent < 0.5)
		return (interpolate_color(0x228B22, 0x8B4513, (height_percent - 0.25)
				* 4));
	else if (height_percent < 0.75)
		return (interpolate_color(0x8B4513, 0xD3D3D3, (height_percent - 0.5)
				* 4));
	else
		return (interpolate_color(0xD3D3D3, 0xFFFFFF, (height_percent - 0.75)
				* 4));
}

static void	create_point(t_vars *vars, char **color_split,
		t_map_context *context)
{
	int	height;

	height = ft_atoi(color_split[0], vars);
	vars->points[context->i][context->j].x = context->j * vars->map->scale.base;
	vars->points[context->i][context->j].y = context->i * vars->map->scale.base;
	vars->points[context->i][context->j].z = height * vars->map->scale.z_scale;
	if (color_split[1])
		vars->points[context->i][context->j].color = ft_atoi_base(color_split[1]
				+ 2, 16);
	else
		vars->points[context->i][context->j].color = calculate_color(height,
				vars->map->height);
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
	fd = open_map_file(vars);
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
