/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	init_tex_data(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->ea = NULL;
	textures->we = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
	textures->size = TXT_SIZE;
	textures->x = 0;
	textures->y = 0;
	textures->type = 0;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->conv_ceiling = 0;
	textures->conv_floor = 0;
}

void	init_tex_pxl(t_data *data)
{
	int	i;

	i = 0;
	if (data->tex_pxl)
		free_tab((void **)data->tex_pxl);
	data->tex_pxl = ft_calloc(data->w_height + 1, sizeof * data->tex_pxl);
	if (!data->tex_pxl)
	{
		err_msg("Malloc allocation failed", 1);
		close_window(data, 1);
	}
	while (i < data->w_height)
	{
		data->tex_pxl[i] = ft_calloc(data->w_width + 1,
				sizeof * data->tex_pxl[i]);
		if (!data->tex_pxl[i])
		{
			err_msg("Malloc allocation failed", 1);
			close_window(data, 1);
		}
		i++;
	}
	return ;
}

t_img	*load_xpm(t_data *data, char *path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
	{
		err_msg("Malloc allocation failed", 1);
		close_window(data, 1);
	}
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->img_w, &img->img_h);
	if (!img->img)
	{
		free(img);
		p_err("MLX init ptr failed");
	}
	img->address = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	return (img);
}

void	init_tex(t_data *data)
{
	data->tex = malloc(sizeof(t_img *) * 5);
	data->tex[NO] = load_xpm(data, data->textures.no);
	data->tex[SO] = load_xpm(data, data->textures.so);
	data->tex[WE] = load_xpm(data, data->textures.we);
	data->tex[EA] = load_xpm(data, data->textures.ea);
	data->tex[EOF_MAP] = NULL;
}
