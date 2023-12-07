/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	copy_map(t_data *data, int i, int j)
{
	while (data->map_set.map[i][j] && data->map_set.map[i][j] != '\n')
	{
		data->lvl[i][j] = data->map_set.map[i][j];
		j++;
	}
}

int	init_lvl(int i, t_data *data)
{
	int	y;
	int	x;

	y = -1;
	data->lvl = malloc(sizeof(char *) * (data->map_set.height + 1));
	if (!data->lvl)
		return (err_msg("Malloc allocation failed", 1));
	while (++y < data->map_set.height)
	{
		x = -1;
		data->lvl[y] = malloc(sizeof(char) * (data->map_set.width + 1));
		if (!data->lvl[y])
			return (err_msg("Malloc allocation failed", 1));
		while (data->map_set.map[i][++x] && data->map_set.map[i][x] != '\n')
			data->lvl[y][x] = data->map_set.map[i][x];
		if (data->lvl[y][--x] != '1')
			p_err("Map is not close");
		while (++x < data->map_set.width)
			data->lvl[y][x] = '1';
		data->lvl[y][x] = '\0';
		i++;
	}
	data->lvl[y] = NULL;
	return (0);
}

void	get_dimension(int map_start_index, t_data *data, char **map)
{
	int	map_height;
	int	max_width;
	int	line_length;
	int	y;

	map_height = 0;
	max_width = 0;
	line_length = 0;
	y = map_start_index;
	while (map[y])
	{
		line_length = ft_strlen(map[y]);
		if (line_length > max_width)
			max_width = line_length;
		map_height++;
		y++;
		line_length = 0;
	}
	data->map_set.end_of_map = y;
	data->map_set.height = map_height;
	data->map_set.width = max_width;
}

void	convert_empty_to_wall(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->lvl[y])
	{
		x = 0;
		while (data->lvl[y][x]) 
		{
			if (data->lvl[y][x] == ' ')
				data->lvl[y][x] = '1';
			x++;
		}
		y++;
	}
}

int	create_map(t_data *data, char **map, int y)
{
	get_dimension(y, data, map);
	printf("Hauteur de la carte : %d\n", data->map_set.height);
	printf("Largeur de la carte : %d\n", data->map_set.width);
	if (init_lvl(y, data) != 0)
		return (1);
	convert_empty_to_wall(data);
	print_lvl(data);
	return (0);
}
