/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:18 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/07 18:28:06 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	map = map_dimension(argv[1]);
	vars.points = points_init(&map);
	parse_map(vars.points, argv[1], &map);
	iso_points(vars.points, &map);
	vars.window_name = argv[1];
	init_fdf(&vars);
	create_image(&vars);
	main_draw(&vars, vars.points, &map);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	vars.dim.height = map.dim.height;
	mlx_hooks(&vars, argv[1]);
	mlx_loop(vars.mlx);
	return (0);
}
