/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:49:33 by inaranjo          #+#    #+#             */
/*   Updated: 2023/12/05 15:50:22 by inaranjo         ###   ########.fr       */
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
    int i, j;

    i = 0;
    while (i < data->img.block_size) // Parcourir chaque ligne du carré
    {
        j = 0;
        while (j < data->img.block_size) // Parcourir chaque colonne de la ligne
        {
            my_mlx_pixel_put(data, draw_x + j, draw_y + i, color);
            j++;
        }
        i++;
    }
}

void draw_player_on_minimap(t_data *data)
{
    // Convertir les coordonnées du personnage en coordonnées de la minimap
    int player_x = (int)(data->player.pos_x * data->img.block_size);
    int player_y = (int)(data->player.pos_y * data->img.block_size);


    int player_size = data->img.block_size / 2; // Taille du marqueur du joueur
    int py = player_y - player_size / 2;
    while (py < player_y + player_size / 2)
    {
        int px = player_x - player_size / 2;
        while (px < player_x + player_size / 2)
        {
            my_mlx_pixel_put(data, py, px, 0xFF0000); // Rouge pour le joueur
            px++;
        }
        py++;
    }
}

void resize_block(t_data *data)
{
    // Ajuster la taille des blocs en fonction de la taille de la carte
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

    // Définir les dimensions de la minimap en fonction de la taille des blocs
    data->img.minimap_w = data->map_set.width * data->img.block_size;
    data->img.minimap_h = data->map_set.height * data->img.block_size;

    // Créer l'image de la minimap
    data->img.minimap_img = mlx_new_image(data->mlx, data->img.minimap_w, data->img.minimap_h);
    if (data->img.minimap_img == NULL)
    {
        printf("Échec de l'initialisation de la minimap\n");
        return;
    }

    data->img.minimap_addr = mlx_get_data_addr(data->img.minimap_img, &data->img.minimap_bpp, &data->img.minimap_line_length, &data->img.minimap_endian);

    // Dessiner la minimap
    y = 0;
    while (data->lvl[y])
    {
        x = 0;
        while (data->lvl[y][x])
        {
            draw_x = x * data->img.block_size;
            draw_y = y * data->img.block_size;

            if (data->lvl[y][x] == '1')
                draw_square(data, draw_x, draw_y, 0x00FF00); // Murs
            else if (data->lvl[y][x] == '0')
                draw_square(data, draw_x, draw_y, 0x00000000); // Espace vide

            x++;
        }
        y++;
    }

    draw_player_on_minimap(data);

    mlx_put_image_to_window(data->mlx, data->win, data->img.minimap_img, 0, 0);
    mlx_destroy_image(data->mlx, data->img.minimap_img);
}

