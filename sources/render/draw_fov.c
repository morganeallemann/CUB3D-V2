/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:26:58 by inaranjo          #+#    #+#             */
/*   Updated: 2023/12/12 17:09:15 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void cal_sx_sy(t_geometry *geo, int *sx, int *sy)
{
    if (geo->x1 < geo->x2)
        *sx = 1;
    else
        *sx = -1;
    if (geo->y1 < geo->y2)
        *sy = 1;
    else
        *sy = -1;
}


void draw_line(t_data *data, t_geometry *geo, int color)
{
    int deltas[2];
    int steps[2];
    int err[2];

    cal_sx_sy(geo, &steps[0], &steps[1]);
    deltas[0] = abs(geo->x2 - geo->x1);
    deltas[1] = abs(geo->y2 - geo->y1);
    err[0] = deltas[0] - deltas[1];

    while (geo->x1 != geo->x2 || geo->y1 != geo->y2)
    {
        my_mlx_pixel_put(data, geo->x1, geo->y1, color);
        err[1] = err[0] * 2;
        if (err[1] > -deltas[1])
        {
            err[0] -= deltas[1];
            geo->x1 += steps[0];
        }
        if (err[1] < deltas[0])
        {
            err[0] += deltas[0];
            geo->y1 += steps[1];
        }
    }
    my_mlx_pixel_put(data, geo->x2, geo->y2, color);
}

void fat_line(t_data *data, t_geometry *geo, int color, int fat)
{
    int i;
    int offsetx;
    int offsety;

    i = -fat / 2;
    while (i <= fat / 2)
    {
        offsetx = (int)(i * sin(atan2(geo->dy, geo->dx)));
        offsety = (int)(i * cos(atan2(geo->dy, geo->dx)));

        t_geometry offset_geo = *geo;
        offset_geo.x1 += offsetx;
        offset_geo.y1 -= offsety;
        offset_geo.x2 += offsetx;
        offset_geo.y2 -= offsety;

        draw_line(data, &offset_geo, color);
        i++;
    }
}


void cast_ray(t_data *data, int player_x, int player_y, double ray_angle)
{
    double dist;
    t_geometry geo;

    dist = 0;
    while (dist < MAX_RAY_DISTANCE)
    {
        geo.x1 = player_x;
        geo.y1 = player_y;
        geo.x2 = (int)(player_x + cos(ray_angle) * dist);
        geo.y2 = (int)(player_y + sin(ray_angle) * dist);
        geo.dx = cos(ray_angle);
        geo.dy = sin(ray_angle);

        int map_pos[2];
        map_pos[0] = geo.x2 / data->img.block_size;
        map_pos[1] = geo.y2 / data->img.block_size;
		if (map_pos[0] < 0 || map_pos[0] >= data->map_set.width
            || map_pos[1] < 0 || map_pos[1] >= data->map_set.height)
            break;

        if (data->lvl[map_pos[1]][map_pos[0]] == '1')
        {
            fat_line(data, &geo, FOV_COLOR, FAT_RAY);
            break;
        }
		if (dist >= MAX_RAY_DISTANCE - 0.5)
            fat_line(data, &geo, FOV_COLOR, FAT_RAY);

        dist += 0.5;
    }
}

void draw_fov(t_data *data)
{
    double fov;
    double angles[2];
    int i;
    double ray_angle;

    fov = M_PI / 3.0;
    angles[0] = data->player.dir - (fov / 2);
    angles[1] = data->player.dir + (fov / 2);
    i = 0;

    int i_player[2];
    mini_player(data, &i_player[0], &i_player[1]);

    while (i < NBR_RAYS)
    {
        ray_angle = angles[0] + (angles[1] - angles[0]) * i / (NBR_RAYS - 1);
        cast_ray(data, i_player[0], i_player[1], ray_angle);
        i++;
    }
}

