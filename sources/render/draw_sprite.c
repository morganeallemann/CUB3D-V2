/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:43:51 by inaranjo          #+#    #+#             */
/*   Updated: 2023/12/10 17:48:13 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*int load_sprite_image(t_data *data, char *file_path)
{
    data->spr->img_spr = mlx_xpm_file_to_image(data->mlx, file_path, &data->spr->width, &data->spr->height);
    if (!data->spr->img_spr)
        return (0); // Échec du chargement de l'image

    data->spr->addr_spr = mlx_get_data_addr(data->spr->img_spr, &data->spr->bpp_spr, &data->spr->line_length_spr, &data->spr->endian_spr);
    return (1);
}


void draw_player_sprite(t_data *data)
{
    int x, y;

    // Convertir les coordonnées du joueur en coordonnées de la fenêtre
    x = (int)(data->player.pos_x * data->img.block_size - data->spr->width / 2);
    y = (int)(data->player.pos_y * data->img.block_size - data->spr->height / 2);

    // Afficher le sprite
    mlx_put_image_to_window(data->mlx, data->win, data->spr->addr_spr, x, y);
}
*/