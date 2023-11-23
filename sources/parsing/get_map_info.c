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

char	*get_path(char *line, int j)
{
	int		len;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'
			&& line[len] != '\n'))
		len++;
	path = malloc(sizeof(char *) * (len - j) + 1);
	len = -1;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
	{
		path[++len] = line[j];
		j++;
	}
	path[++len] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	get_texture_dir(t_textures *textures, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && !textures->no)
		textures->no = get_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !textures->so)
		textures->so = get_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !textures->we)
		textures->we = get_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !textures->ea)
		textures->ea = get_path(line, j + 2);
	else
		return (1);
	return (0);
}

int	get_settings(t_data *data, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& (map[i][j + 1] != ' '))
		{
			if (get_texture_dir(&data->textures, map[i], j) != 0)
				return (-1);
			return (1);
		}
		else 
		{
			if (get_tex_color(&data->textures, map[i], j) != 0)
				return (-1);
			return (1);
		}
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (create_map(data, map, i) != 0)
			return (-1);
		return (0);
	}
	return (2);
}

int	get_map_info(t_data *data, char **map)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			index = get_settings(data, map, i, j);
			if (index == 1)
				break ;
			else if (index == 0)
				return (0);
			else if (index == -1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
