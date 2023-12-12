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
	while (map[y] && map[y][0] != '\n')
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
	return ;
}

int	create_map(t_data *data, char **map, int y)
{
	get_dimension(y, data, map);
	printf("WIDTH:  %d\n", data->map_set.width);
	if (init_lvl(y, data) != 0)
		return (1);
	print_lvl(data);
	return (0);
}
