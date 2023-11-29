/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c			                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_colors(t_textures *textures)
{
	if (textures->floor)
	{
		free(textures->floor);
		textures->floor = NULL;
	}
	if (textures->ceiling)
	{
		free(textures->ceiling);
		textures->ceiling = NULL;
	}
}

static void	free_textures(t_textures *textures)
{
	if (textures->no)
	{
		free(textures->no);
		textures->no = NULL;
	}
	if (textures->so)
	{
		free(textures->so);
		textures->so = NULL;
	}
	if (textures->we)
	{
		free(textures->we);
		textures->we = NULL;
	}
	if (textures->ea)
	{
		free(textures->ea);
		textures->ea = NULL;
	}
}

static void	free_map(t_data *data)
{
	if (data->map_set.fd > 0)
		close(data->map_set.fd);
	if (data->map_set.map)
		free_tab((void **)data->map_set.map);
	if (data->lvl)
		free_tab((void **)data->lvl);
}

int	free_data(t_data *data)
{
	if (data->tex)
		free_tab((void **)data->tex);
	if (data->tex_pxl)
		free_tab((void **)data->tex_pxl);
	free_textures(&data->textures);
	free_colors(&data->textures);
	free_map(data);
	return (1);
}
