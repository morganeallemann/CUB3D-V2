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

int	init_lvl(int ind, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_set.height)
	{
		j = 0;
		data->lvl[i] = malloc(sizeof(char) * (data->map_set.width + 1));
		if (!data->lvl[i])
			return (err_msg("Malloc allocation failed", 1));
		while (data->map_set.map[ind][j] && data->map_set.map[ind][j] != '\n')
		{
			data->lvl[i][j] = data->map_set.map[ind][j];
			j++;
		}
		j--;
		while (++j < data->map_set.width)
			data->lvl[i][j] = '1';
		data->lvl[i][j] = '\0';
		ind++;
	}
	data->lvl[i] = NULL;
	return (0);
}

void	get_dimension(int map_start_index, t_data *data, char **map)
{
	int	map_height;
	int	max_width;
	int	line_length;
	int	i;

	map_height = 0;
	max_width = 0;
	line_length = 0;
	i = map_start_index;
	while (map[i])
	{
		line_length = ft_strlen(map[i]);
		if (line_length > max_width)
			max_width = line_length;
		map_height++;
		i++;
	}
	data->map_set.end_of_map = i;
	data->map_set.height = map_height;
	data->map_set.width = max_width;
}

void	convert_empty_to_wall(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (data->lvl[x])
	{
		y = 0;
		while (data->lvl[x][y]) 
		{
			if (data->lvl[x][y] == ' ')
				data->lvl[x][y] = '1';
			y++;
		}
		x++;
	}
}

int	create_map(t_data *data, char **map, int i)
{
	get_dimension(i, data, map);
	printf("Hauteur de la carte : %d\n", data->map_set.height);
	printf("Largeur de la carte : %d\n", data->map_set.width);
	data->lvl = (char **)malloc(sizeof(char *) * data->map_set.height + 1);
	if (!data->lvl)
		return (err_msg("Malloc allocation failed", 1));
	if (init_lvl(i, data) != 0)
		return (1);
	convert_empty_to_wall(data);
	return (0);
}
