/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_side.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int check_close(t_data *data, int y, int x)
{
	int max_len;

	max_len = ft_strlen(data->lvl[y]);
	if (y == 0 || y == data->map_set.height)
		return (1);
	if (x == 0 || x == max_len)
		return (1);
	if (data->lvl[y][x + 1] != '1' && data->lvl[y][x + 1] != '0')
		return (1);
	if (data->lvl[y][x - 1] != '1' && data->lvl[y][x - 1] != '0')
		return (1);
	if (data->lvl[y + 1][x] != '1' && data->lvl[y + 1][x] != '0')
		return (1);
	if (data->lvl[y - 1][x] != '1' && data->lvl[y - 1][x] != '0')
		return (1);
	else
		return (0);
}

int	checker_side(t_data *data, char **map)
{
	int	x;
	int	y;
	int	error;

	y = 0;
	error = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				error += check_close(data, y , x);
			x++;
		}
		y++;
	}
	if (error != 0)
		return (1);
	else
		return (0);
}
