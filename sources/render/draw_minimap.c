/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:20:17 by inaranjo          #+#    #+#             */
/*   Updated: 2023/12/12 15:08:58 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{  
    char	*dst;

    dst = data->img.minimap_addr + 
    (y * data->img.minimap_line_length + x * (data->img.minimap_bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_square(t_data *data, int draw_x, int draw_y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < data->img.block_size)
    {
        j = 0;
        while (j < data->img.block_size)
        {
            my_mlx_pixel_put(data, draw_x + j, draw_y + i, color);
            j++;
        }
        i++;
    }
}

void draw_player(t_data *data)
{
    int player_x;
    int player_y;
    int player_size;
    int py;

    mini_player(data, &player_x, &player_y);
    player_size = data->img.block_size / 2;
    py = player_y - player_size / 2;
    while (py < player_y + player_size / 2)
    {
        int px = player_x - player_size / 2;
        while (px < player_x + player_size / 2)
        {
            my_mlx_pixel_put(data, px, py, 0xFF0000);
            px++;
        }
        py++;
    }
}

void resize_block(t_data *data)
{
    if (data->map_set.width < 300 || data->map_set.height < 300)
        data->img.block_size = 10;
    else if (data->map_set.width < 700 || data->map_set.height < 700)
        data->img.block_size = 15;
    else
        data->img.block_size = 30;
}

void draw_minimap(t_data *data)
{
    int y;
    int x;
    int draw_x;
    int draw_y;
    
    resize_block(data);
    data->img.minimap_w = (data->map_set.width  - 1) * data->img.block_size;
    data->img.minimap_h = data->map_set.height * data->img.block_size;
    data->img.minimap_img = mlx_new_image(data->mlx,
    data->img.minimap_w, data->img.minimap_h);
    if (data->img.minimap_img == NULL)
    {
        free(data->img.minimap_img);
        p_err("Init map_img failed");
    }
    data->img.minimap_addr = mlx_get_data_addr(data->img.minimap_img,
    &data->img.minimap_bpp, &data->img.minimap_line_length,
    &data->img.minimap_endian);
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
    draw_player(data);
    draw_fov(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.minimap_img, 0, 0);
    mlx_destroy_image(data->mlx, data->img.minimap_img);
}