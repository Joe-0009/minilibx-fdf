#include "fdf.h"

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
