#include "../includes/cub3d.h"

void	put_img_pxl(t_img *img, int j, int i, int color)
{
	int	pxl;

	pxl = i * (img->line_length / 4) + j;
	img->address[pxl] = color;
}

void	check_frame(t_data *data, t_img *img, int i, int j)
{
	if (data->tex_pxl[i][j] > 0)
		put_img_pxl(img, j, i, data->tex_pxl[i][j]);
	else if (i < data->w_height / 2)
		put_img_pxl(img, j, i, data->textures.conv_ceiling);
	else if (i < data->w_height -1)
		put_img_pxl(img, j, i, data->textures.conv_floor);
}

void	draw_map(t_data *data)
{
	t_img	img;
	int		i;
	int		j;

	i = 0;
	init_img(&img);
	img.img = mlx_new_image(data->mlx, data->w_height, data->w_height);
	if (img.img == NULL)
	{
		err_msg("MLX init failed", 1);
		close_window(data, 1);
	}
	img.address = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	while (i < data->w_height)
	{
		j = 0;
		while (j < data->w_width)
		{
			check_frame(data, &img, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}
