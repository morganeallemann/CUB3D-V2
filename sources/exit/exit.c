#include "../includes/cub3d.h"

void	close_window(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->win && data->mlx)
	{
		free(data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
	if (data->mlx)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		free(data->mlx);
	}
	free_data(data);
	exit(code);
}