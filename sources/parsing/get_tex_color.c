#include"../includes/cub3d.h"

int	no_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	*convert_colors(char **c_to_convert, int *colors)
{
	int	i;

	i = 0;
	while (c_to_convert[i])
	{
		colors[i] = ft_atoi(c_to_convert[i]);
		if (colors[i] == -1 || no_num(c_to_convert[i]) == 0)
		{
			free_tab((void *)c_to_convert);
			free(colors);
			return (0);
		}
		i++;
	}
	free_tab((void *)c_to_convert);
	return (colors);
}

int	*get_colors(char *str)
{
	int		i;
	int		*colors;
	char	**c_to_convert;

	i = 0;
	c_to_convert = ft_split(str, ',');
	while (c_to_convert[i])
		i++;
	if (i != 3)
	{
		free_tab((void *)c_to_convert);
		return (0);
	}
	colors = malloc(sizeof(int *) * 3);
	if (!colors)
	{
		err_msg("Malloc allocation failed", 0);
		return (0);
	}
	return (convert_colors(c_to_convert, colors));
}

int get_tex_color(t_textures *textures, char *line, int j)
{
	if (line[j] == 'C' && !ft_isprint(line[j + 1]) && !textures->ceiling)
	{
		textures->ceiling = get_colors(line + j + 1);
		if (textures->ceiling == 0)
			return (err_msg("Invalid ceiling texture color", 1));
	}
	else if (line[j] == 'F' && !ft_isprint(line[j + 1]) && !textures->floor)
	{
		textures->floor = get_colors(line + j + 1);
		if (textures->floor == 0)
			return (err_msg("Invalid floor textures color", 1));
	}
	else
		return (err_msg("Invalid colors textures floor and/or ceiling", 1));
	return (0);
}