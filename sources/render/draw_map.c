/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	put_img_pxl(t_img *img, int x, int y, int color)
{
	char	*pix;

	pix = img->address + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) pix = color;
}

void	check_frame(t_data *data, t_img *img, int x, int y)
{
	if (data->tex_pxl[y][x] > 0)
		put_img_pxl(img, x, y, data->tex_pxl[y][x]);
	else if (y < data->w_height / 2)
		put_img_pxl(img, x, y, data->textures.conv_ceiling);
	else if (y < data->w_height -1)
		put_img_pxl(img, x, y, data->textures.conv_floor);
}

void	draw_map(t_data *data)
{
	t_img	img;
	int		x;
	int		y;

	y = 0;
	init_img(&img);
	img.img = mlx_new_image(data->mlx, data->w_width, data->w_height);
	if (img.img == NULL)
	{
		err_msg("MLX init failed", 1);
		close_window(data, 1);
	}
	img.address = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	while (y < data->w_height)
	{
		x = -1;
		while (++x < data->w_width)
			check_frame(data, &img, x, y);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}
