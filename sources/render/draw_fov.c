/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:26:58 by inaranjo          #+#    #+#             */
/*   Updated: 2023/12/12 14:28:54 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cal_sx_sy(int x0, int y0, int x1, int y1, int *sx, int *sy)
{
	if (x0 < x1)
		*sx = 1;
	else
		*sx = -1;
	if (y0 < y1)
		*sy = 1;
	else
		*sy = -1;
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	deltas[2];
	int	steps[2];
	int	err[2];

	cal_sx_sy(x0, y0, x1, y1, &steps[0], &steps[1]);
	deltas[0] = abs(x1 - x0);
	deltas[1] = abs(y1 - y0);
	err[0] = deltas[0] - deltas[1];
	while (x0 != x1 || y0 != y1)
	{
		my_mlx_pixel_put(data, x0, y0, color);
		err[1] = err[0] * 2;
		if (err[1] > -deltas[1])
		{
			err[0] -= deltas[1];
			x0 += steps[0];
		}
		if (err[1] < deltas[0])
		{
			err[0] += deltas[0];
			y0 += steps[1];
		}
	}
	my_mlx_pixel_put(data, x1, y1, color);
}

void	fat_line(t_data *data, int x0, int y0, int x1, int y1, int color, int fat)
{
	int	i;
	int	offsetx;
	int	offsety;

	i = -fat / 2;
	while (i <= fat / 2)
	{
		offsetx = (int)(i * sin(atan2((double)(y1 - y0), (double)(x1 - x0))));
		offsety = (int)(i * cos(atan2((double)(y1 - y0), (double)(x1 - x0))));
		draw_line(data,
			x0 + offsetx, y0 - offsety, x1 + offsetx, y1 - offsety, color);
		i++;
	}
}

void	cast_ray(t_data *data, int player_x, int player_y, double ray_angle)
{
	double	ray_pos[2];
	int		map_pos[2];
	double	dist;

	dist = 0;
	while (dist < MAX_RAY_DISTANCE)
	{
		ray_pos[0] = player_x + cos(ray_angle) * dist;
		ray_pos[1] = player_y + sin(ray_angle) * dist;
		map_pos[0] = (int)ray_pos[0] / data->img.block_size;
		map_pos[1] = (int)ray_pos[1] / data->img.block_size;
		if (map_pos[0] < 0 || map_pos[0] >= data->map_set.width
			|| map_pos[1] < 0 || map_pos[1] >= data->map_set.height)
			break ;
		if (data->lvl[map_pos[1]][map_pos[0]] == '1')
		{
			fat_line(data, player_x, player_y, (int)ray_pos[0],
				(int)ray_pos[1], FOV_COLOR, FAT_RAY);
			break ;
		}
		if (dist >= MAX_RAY_DISTANCE - 0.5)
			fat_line(data, player_x, player_y, (int)ray_pos[0],
				(int)ray_pos[1], FOV_COLOR, FAT_RAY);
		dist += 0.5;
	}
}

void	draw_fov(t_data *data)
{
	double	fov;
	double	angles[2];
	int		i_player[2];
	double	ray_angle;
	int		i;

	fov = M_PI / 3.0;
	angles[0] = data->player.dir - (fov / 2);
	angles[1] = data->player.dir + (fov / 2);
	i = 0;
	mini_player(data, &i_player[0], &i_player[1]);
	while (i < NBR_RAYS)
	{
		ray_angle = angles[0] + (angles[1] - angles[0]) * i / (NBR_RAYS - 1);
		cast_ray(data, i_player[0], i_player[1], ray_angle);
		i++;
	}
}
