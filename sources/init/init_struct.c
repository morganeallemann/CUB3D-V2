/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	init_map(t_map *map)
{
	map->fd = 0;
	map->nb_lines = 0;
	map->height = 0;
	map->width = 0;
	map->end_of_map = 0;
	map->map = NULL;
}

void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plan_x = 0.0;
	player->plan_y = 0.0;
	player->move_on = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotation = 0;
}

void	init_img(t_img *img)
{
	img->img = NULL;
	img->address = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->img_h = 0;
	img->img_w = 0;
	img->minimap_img = NULL;
	img->minimap_addr = NULL;
	img->minimap_bpp = 0;
	img->minimap_line_length = 0;
	img->minimap_endian = 0;
	img->minimap_w = 0;
	img->minimap_h = 0;
	img->minimap_y = 0;
	img->minimap_x = 0;
	img->block_size = 0;
}

void	init_ray(t_ray *ray)
{
	ray->cam = 0.0;
	ray->dir_x = 0.0;
	ray->dir_y = 0.0;
	ray->wall_dist = 0.0;
	ray->wall = 0.0;
	ray->side_x = 0.0;
	ray->side_y = 0.0;
	ray->delta_x = 0.0;
	ray->delta_y = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->line_h = 0;
	ray->start_draw = 0;
	ray->end_draw = 0;
	ray->side = 0;
	ray->step_x = 0;
	ray->step_y = 0;
}

void	init_struct(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->w_height = W_HEIGHT;
	data->w_width = W_WIDTH;
	data->lvl = NULL;
	data->tex = NULL;
	data->tex_pxl = NULL;
	init_map(&data->map_set);
	init_player(&data->player);
	init_tex_data(&data->textures);
	init_img(&data->img);
	init_ray(&data->ray);
}
