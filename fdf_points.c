/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:34:09 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/07 16:10:08 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_points(int map_height, t_point **points)
{
	int	i;

	i = 0;
	if (points)
	{
		while (i < map_height)
			free(points[i++]);
		free(points);
	}
}

static void	create_point(t_point *point, char **color_split,
		t_map_context *context)
{
	int	height;

	height = ft_atoi(color_split[0]);
	point->x = context->j * context->map->scale.base;
	point->y = context->i * context->map->scale.base;
	point->z = height * context->map->scale.z_scale;
	if (color_split[1])
		point->color = (int)strtol(color_split[1], NULL, 16);
	else
		point->color = calculate_color(height, &context->map->height);
}

static void	parse_line(char *line, t_point **points, t_map_context *context)
{
	char	**split;
	char	**color_split;
	int		j;

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
		create_point(&points[context->i][j], color_split, context);
		ft_free_strs(color_split);
	}
	ft_free_strs(split);
}

void	parse_map(t_point **points, char *file_name, t_map *map)
{
	int				fd;
	char			*line;
	t_map_context	context;

	find_height_range(file_name, map);
	calculate_scale(map);
	context.map = map;
	context.i = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, points, &context);
		context.i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_point	**points_init(t_map *map)
{
	t_point	**points;
	int		i;

	points = malloc(map->dim.height * sizeof(t_point *));
	if (!points)
		exit(0);
	i = 0;
	while (i < map->dim.height)
	{
		points[i] = malloc(map->dim.width * sizeof(t_point));
		if (!points[i])
		{
			while (--i >= 0)
				free(points[i]);
			free(points);
			exit(0);
		}
		i++;
	}
	return (points);
}
