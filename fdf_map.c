#include "fdf.h"

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

	i = 0;
	while (i < map->height)
	{
		free(points[i]);
		i++;
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
	i = 0;
	while (i < map->height)
	{
		points[i] = (t_point *)malloc(map->width * sizeof(t_point));
		if (!points[i])
		{
			fprintf(stderr, "Error allocating memory for points row\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (points);
}
