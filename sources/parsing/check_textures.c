/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	check_xpm(char *av)
{
	int	i;

	i = ft_strlen(av);
	if ((av[i - 3] != 'x' || av[i - 2] != 'p'
			|| av[i - 1] != 'm'
			|| av[i - 4] != '.'))
		return (1);
	else
		return (0);
}

int	check_colors(int *colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (colors[i] < 0 || colors[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

unsigned long	conv_colors(int *colors)
{
	unsigned long	convert;
	int				r;
	int				g;
	int				b;

	r = colors[0];
	g = colors[1];
	b = colors[2];
	convert = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (convert);
}

int	checker_textures(t_textures *textures)
{
	if (!textures->no || !textures->so || !textures->we || !textures->ea)
		return (err_msg("Init txt failed", 1));
	if (!textures->ceiling || !textures->floor)
		return (err_msg("Init colors failed", 1));
	if (check_xpm(textures->no) || check_xpm(textures->so)
		|| check_xpm(textures->we) || check_xpm(textures->ea))
		return (err_msg("Textures files is not XPM", 1));
	if (check_colors(textures->floor) || check_colors(textures->ceiling))
		return (err_msg("Colors code is wrong", 1));
	textures->conv_floor = conv_colors(textures->floor);
	textures->conv_ceiling = conv_colors(textures->ceiling);
	return (0);
}
