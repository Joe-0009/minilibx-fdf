/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_height.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:59 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/16 14:19:58 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	process_height(char *str, t_vars *vars)
{
	int	current_height;

	if (!str || !vars || !vars->map)
	{
		cleanup_all(vars);
		ft_error();
		return (-1);
	}
	current_height = ft_atoi(str, vars);
	if (current_height == INT_MIN)
		return (-1);
	if (current_height < vars->map->height.min)
		vars->map->height.min = current_height;
	if (current_height > vars->map->height.max)
		vars->map->height.max = current_height;
	return (0);
}

static void	process_line_heights(char **split, t_vars *vars, char *line, int fd)
{
	int		i;
	char	**color_split;

	i = -1;
	while (split[++i])
	{
		color_split = ft_split(split[i], ',');
		if (process_height(color_split[0], vars) == -1)
		{
			ft_free_strs(color_split);
			ft_free_strs(split);
			free(line);
			cleanup_gnl(fd);
			cleanup_all(vars);
			ft_error();
		}
		ft_free_strs(color_split);
	}
}

void	find_height_range(t_vars *vars)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open_map_file(vars->window_name);
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		process_line_heights(split, vars, line, fd);
		ft_free_strs(split);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
