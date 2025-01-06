/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:18 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/06 14:47:41 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map;
	t_point	**points;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	map = map_dimension(argv[1]);
	points = points_init(&map);
	parse_map(points, argv[1], &map);
	iso_points(points, &map);
	vars.window_name = argv[1];
	init_fdf(&vars);
	create_image(&vars);
	main_draw(&vars, points, &map);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hooks(&vars, argv[1]);
	mlx_loop(vars.mlx);
	free_points(&map, points);
	return (0);
}
