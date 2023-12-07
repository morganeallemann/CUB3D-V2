/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	checker_elem(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	data->player.dir = '0';
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n' && (map[i][j]))
		{
			if (!ft_strchr("10NSEW", map[i][j]))
				return (1);
			if (ft_strchr("NSEW", map[i][j]) && data->player.dir == '0')
				data->player.dir = map[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

int	checker_player(t_data *data, char **map)
{
	int	y;
	int	x;
	int	flag;

	y = -1;
	flag = 0;
	if (data->player.dir == '0')
		return (1);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				data->player.pos_x = (double)x + 0.5;
				data->player.pos_y = (double)y + 0.5;
				map[y][x] = '0';
				flag ++;
			}
		}
	}
	if (!data->player.pos_x || !data->player.pos_y || flag != 1)
		return (1);
	return (0);
}

int	check_order_elem(t_data *data)
{
	int	i;
	int	j;

	i = data->map_set.end_of_map;
	while (data->map_set.map[i])
	{
		j = 0;
		while (data->map_set.map[i][j])
		{
			if (data->map_set.map[i][j] != ' '
				&& data->map_set.map[i][j] != '\t'
				&& data->map_set.map[i][j] != '\r' 
				&& data->map_set.map[i][j] != '\n'
				&& data->map_set.map[i][j] != '\v'
				&& data->map_set.map[i][j] != '\f')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checker_map(t_data *data, char **map)
{
	if (!data->lvl)
		return (err_msg("Map missing", 1));
	if (data->map_set.height < 3 || data->map_set.width < 3)
		return (err_msg("Invalid map size", 1));
	if (checker_side(data, map) != 0)
		return (err_msg("Invalid map side", 1));
	if (checker_elem(data, map) != 0)
		return (err_msg("Invalid element on map", 1));
	if (checker_player(data, map) != 0)
		return (err_msg("Invalid player direction or too many player", 1));
	if (check_order_elem(data) != 0)
		return (err_msg("Invalid order in map fd", 1));
	return (0);
}
