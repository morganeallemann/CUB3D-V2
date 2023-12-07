/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	get_nbr_lines(char *map_fd)
{
	int		fd;
	int		nb_lines;
	char	*temp;

	nb_lines = 0;
	fd = open(map_fd, O_RDONLY);
	if (fd == -1)
	{
		perror("ERREUR: Fichier non compatible\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		temp = get_next_line(fd);
		while (temp)
		{
			free(temp);
			temp = get_next_line(fd);
			nb_lines++;
		}
		close(fd);
	}
	return (nb_lines);
}

void	memset_range_line(int range, int col, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->map_set.fd);
	while (line)
	{
		data->map_set.map[range] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map_set.map[range])
			return (free_tab((void *)data->map_set.map));
		while (line[i])
		{
			data->map_set.map[range][col] = line[i];
			i++;
			col++;
		}
		data->map_set.map[range++][col] = '\0';
		col = 0;
		i = 0;
		free(line);
		line = get_next_line(data->map_set.fd);
	}
	data->map_set.map[range] = NULL;
}

void	parse_map(char *map_fd, t_data *data)
{
	size_t	col;
	int		range;
	int		i;

	col = 0;
	range = 0;
	i = 0;
	data->map_set.nb_lines = get_nbr_lines(map_fd);
	data->map_set.map_fd = map_fd;
	data->map_set.map = ft_calloc(data->map_set.nb_lines + 1, sizeof(char *));
	if (!data->map_set.map)
		err_msg("Malloc allocation failed", 1);
	data->map_set.fd = open(map_fd, O_RDONLY);
	if (data->map_set.fd == -1)
		p_err("File copy access failed");
	memset_range_line(range, col, i, data);
	close(data->map_set.fd);
}
