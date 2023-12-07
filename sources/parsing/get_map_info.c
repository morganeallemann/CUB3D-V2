/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

char	*get_path(char *line, int x)
{
	int		len;
	char	*path;

	while (line[x] && (line[x] == ' ' || line[x] == '\t'))
		x++;
	len = x;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'
			&& line[len] != '\n'))
		len++;
	path = malloc(sizeof(char *) * (len - x) + 1);
	len = -1;
	while (line[x] && (line[x] != ' ' && line[x] != '\t' && line[x] != '\n'))
	{
		path[++len] = line[x];
		x++;
	}
	path[++len] = '\0';
	while (line[x] && (line[x] == ' ' || line[x] == '\t'))
		x++;
	if (line[x] && line[x] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	get_texture_dir(t_textures *textures, char *line, int x)
{
	if (line[x] == 'N' && line[x + 1] == 'O' && !textures->no)
		textures->no = get_path(line, x + 2);
	else if (line[x] == 'S' && line[x + 1] == 'O' && !textures->so)
		textures->so = get_path(line, x + 2);
	else if (line[x] == 'W' && line[x + 1] == 'E' && !textures->we)
		textures->we = get_path(line, x + 2);
	else if (line[x] == 'E' && line[x + 1] == 'A' && !textures->ea)
		textures->ea = get_path(line, x + 2);
	else
		return (1);
	return (0);
}

int	get_settings(t_data *data, char **map, int y, int x)
{
	while (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '\n')
		x++;
	if (ft_isprint(map[y][x]) && !ft_isdigit(map[y][x]))
	{
		if (map[y][x + 1] && ft_isprint(map[y][x + 1])
			&& (map[y][x + 1] != ' '))
		{
			if (get_texture_dir(&data->textures, map[y], x) != 0)
				return (-1);
			return (1);
		}
		else 
		{
			if (get_tex_color(&data->textures, map[y], x) != 0)
				return (-1);
			return (1);
		}
	}
	else if (ft_isdigit(map[y][x]))
	{
		if (create_map(data, map, y) != 0)
			return (-1);
		return (0);
	}
	return (2);
}

int	get_map_info(t_data *data, char **map)
{
	int	y;
	int	x;
	int	index;

	y = 0;
	index = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			index = get_settings(data, map, y, x);
			if (index == 1)
				break ;
			else if (index == 0)
				return (0);
			else if (index == -1)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
