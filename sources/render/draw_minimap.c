/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:49:33 by inaranjo          #+#    #+#             */
/*   Updated: 2023/11/27 14:14:48 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->img.minimap_addr+ (y * data->img.minimap_line_length + x * (data->img.minimap_bpp / 8));
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
            my_mlx_pixel_put(data, draw_x + i, draw_y + j, color);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_data *data)
{
    int y;
    int x;
    int draw_x;
    int draw_y;

    init_img(&data->img);  // Initialisation de la structure t_img pour la minimap
    
    data->img.minimap_w = 200;
    data->img.minimap_h = 200;
    data->img.block_size = 5;

    data->img.minimap_img = mlx_new_image(data->mlx, data->img.minimap_w , data->img.minimap_h );
    if (data->img.minimap_img == NULL)
    {
        printf("fail init minimap");
    }
    data->img.minimap_addr = mlx_get_data_addr(data->img.minimap_img, &data->img.minimap_bpp, &data->img.minimap_line_length, &data->img.minimap_endian);

    y = 0;
    while (data->lvl[y])
    {
        x = 0;
        while (data->lvl[y][x])
        {
            draw_x = x * data->img.block_size;
            draw_y = y * data->img.block_size;

            if (data->lvl[y][x] == '1')
            {
                draw_square(data, draw_x, draw_y, 0x00FFFFFF); // Blanc pour les murs
            }
            else if (data->lvl[y][x] == '0')
            {
                draw_square(data, draw_x, draw_y, 0x00000000); // Noir pour l'espace vide
            }

            x++;
        }
        y++;
    }
    // Affichage de la minimap
    mlx_put_image_to_window(data->mlx, data->win, data->img.minimap_img, 0,0);
    mlx_destroy_image(data->mlx, data->img.minimap_img);
}

