/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	init_north_south(t_data *data)
{
	if (data->player.dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plan_x = -0.66;
		data->player.plan_y = 0;
	}
	if (data->player.dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plan_x = 0.66;
		data->player.plan_y = 0;
	}
	return ;
}

void	init_east_west(t_data *data)
{
	if (data->player.dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plan_x = 0;
		data->player.plan_y = 0.66;
	}
	if (data->player.dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plan_x = 0;
		data->player.plan_y = -0.66;
	}
	return ;
}

void	init_player_dir(t_data *data)
{
    if (data->player.dir == 'N' || data->player.dir == 'S')
        init_north_south(data);
    else if (data->player.dir == 'E' || data->player.dir == 'W')
        init_east_west(data);
    return ;
}

