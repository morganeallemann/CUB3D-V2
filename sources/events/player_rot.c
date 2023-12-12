/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rot.c	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	rotation(t_data *data, double speed_r)
{
    t_player	*p;
    double		old_dir_x, old_plan_x;

    p = &data->player;
    old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(speed_r) - p->dir_y * sin(speed_r);
    p->dir_y = old_dir_x * sin(speed_r) + p->dir_y * cos(speed_r);

    old_plan_x = p->plan_x;
    p->plan_x = p->plan_x * cos(speed_r) - p->plan_y * sin(speed_r);
    p->plan_y = old_plan_x * sin(speed_r) + p->plan_y * cos(speed_r);

    // Mise à jour de data->player.dir
    data->player.dir = atan2(p->dir_y, p->dir_x);

    return (1);
}

int	player_rot(t_data *data, double rot)
{
	int		move;
	double	speed_r;

	move = 0;
	speed_r = 0.1 * rot;
	move += rotation(data, speed_r);
	return (move);
}
