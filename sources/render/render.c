/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	mini_player(t_data *data, int *player_x, int *player_y)
{
	*player_x = (int)(data->player.pos_x * data->img.block_size);
	*player_y = (int)(data->player.pos_y * data->img.block_size);
}

static void	render_raycast(t_data *data)
{
	init_ray(&data->ray);
	init_tex_pxl(data);
	raycasting(data, &data->player);
	draw_map(data);
}

void	render_images(t_data *data)
{
	render_raycast(data);
	set_minimap(data);
}

int	render(t_data *data)
{
	data->player.move_on += event_player(data);
	if (data->player.move_on == 0)
		return (0);
	render_images(data);
	return (0);
}
