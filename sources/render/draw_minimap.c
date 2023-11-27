/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:49:33 by inaranjo          #+#    #+#             */
/*   Updated: 2023/11/27 18:10:40 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    // if (x < 0 || x >= data->img.minimap_w || y < 0 || y >= data->img.minimap_h)
    // {
    //     //printf("je suis en dehors de la map");
    //     return ;
    // }
    
    char	*dst;

    dst = data->img.minimap_addr+ (y * data->img.minimap_line_length + x * (data->img.minimap_bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_square(t_data *data, int draw_y, int draw_x, int color)
{
    int i;
    int j;
    
    i = 0;
    while (i < data->img.block_size)
    {
        j = 0;
        while (j < data->img.block_size)
        {
            my_mlx_pixel_put(data, draw_y + i, draw_x + j, color);
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
    
    data->img.minimap_w = 10; // 10 max - min , avant segfault
    data->img.minimap_h = 40; // 40 max - min avant segfault
    data->img.block_size = 5;

    data->img.minimap_img = mlx_new_image(data->mlx, data->img.minimap_w , data->img.minimap_h );
    if (data->img.minimap_img == NULL)
    {
        printf("fail init minimap");
    }
    printf("Taille de la minimap(draw_minimap()): largeur %d, hauteur %d\n", data->map_set.width, data->map_set.height);
    data->img.minimap_addr = mlx_get_data_addr(data->img.minimap_img, &data->img.minimap_bpp, &data->img.minimap_line_length, &data->img.minimap_endian);


    y = 0;
    while (data->lvl[y])
    {
        printf("Debut boucle [y] -->hauter: %d\n", y);
        printf("Ligne %d: %s\n", y, data->lvl[y]); 
        x = 0;
        while (data->lvl[y][x])
        {
            printf("Debut boucle [x] -->largeur: %d\n", x);
            printf("index_x: %d, index_y: %d\n", x, y);
            draw_x = x * data->img.block_size;
            draw_y = y * data->img.block_size;
            printf("draw_x: %d, draw_y: %d\n", draw_x, draw_y);  

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


