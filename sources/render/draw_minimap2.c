/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:20:17 by inaranjo          #+#    #+#             */
/*   Updated: 2023/12/12 15:08:58 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap(t_data *data)
{
	int	y;
	int	x;
	int	draw_x;
	int	draw_y;

	y = 0;
	while (data->lvl[y])
	{
		x = 0;
		while (data->lvl[y][x])
		{
			draw_x = x * data->img.block_size;
			draw_y = y * data->img.block_size;
			if (data->lvl[y][x] == '1')
				draw_square(data, draw_x, draw_y, 0x000000);
			else if (data->lvl[y][x] == '0')
				draw_square(data, draw_x, draw_y, 0xD2B48C);
			else
				draw_square(data, draw_x, draw_y, 0x000000);
			x++;
		}
		y++;
	}
}
