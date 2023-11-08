#include "../includes/cub3d.h"

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	 if (!data->mlx)
		close_window(data, 1);
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	if (!data->win)
		close_window(data, 1);
	data->img.img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	data->img.address = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_length, &data->img.endian);
	return ;
}