#include "fdf.h"

int	close_window_esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
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

void	mlx_hooks(t_vars *vars, char *str)
{
	vars->window_name = str;
	init_fdf(vars);
	mlx_hook(vars->win, 2, 1L << 0, close_window_esc, vars);
	mlx_hook(vars->win, 17, 0, close_window_x, vars);
	create_image(vars);
}
