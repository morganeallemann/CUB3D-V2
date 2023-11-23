/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	check_extension(char *av)
{
	int	i;

	i = ft_strlen(av);
	if ((av[i - 3] != 'c' || av[i - 2] != 'u'
			|| av[i - 1] != 'b'
			|| av[i - 4] != '.'))
		return (1);
	else
		return (0);
}

void	check_fd(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		p_err("File access failed");
	close(fd);
	if (check_extension(av) != 0)
		p_err("Map extension is wrong.");
	return ;
}

int	parse(t_data *data, char **av)
{
	check_fd(av[1]);
	parse_map(av[1], data);
	if (get_map_info(data, data->map_set.map) != 0)
		return (1);
	if (checker_map(data, data->lvl) != 0)
		return (1);
	if (checker_textures(&data->textures) != 0)
		return (1);
	init_player_dir(data);
	return (0);
}
