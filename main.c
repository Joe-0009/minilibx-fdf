#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars vars;
	t_point **points;
	t_map map;

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