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

int	checker_start_end(char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t'
	|| map[i][j] == '\r' || map[i][j] == '\v'
	|| map[i][j] == '\f')
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	checker_side(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (checker_start_end(map, 0, 0) != 0)
		return (1);
	while (i < data->map_set.height - 1)
	{
		if (map[i][0] != '1')
			return (1);
		j = ft_strlen(map[i]) - 1;
		if (map[i][j] != '1')
			return (1);
		i++;
	}
	if (checker_start_end(map, i, 0) != 0)
		return (1);
	return (0);
}
