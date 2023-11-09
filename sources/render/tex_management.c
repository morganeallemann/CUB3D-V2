#include "../includes/cub3d.h"

void	tex_type(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->textures.type = WE;
		else
			data->textures.type = EA;
	}
	else
	{
		if (ray->dir_y > 0)
			data->textures.type = SO;
		else
			data->textures.type = NO;
	}
	return ;
}

int	get_color_pxl(t_data *data, t_img *img, int x, int y)
{
	int	pos;
	int	color;

	if (x < 0 || x >= data->textures.size || y < 0 || y >= data->textures.size)
		return (0);
	pos = (y * data->textures.size + x * (img->bpp / 8));
	color = *(unsigned int *)(img->address + pos);
	return (color);
}

void	update_tex_pxl(t_ray *ray, t_data *data, t_textures *tex, int i)
{ 
	int	j;
	int	color;

	j = 0;
	color = 0;
	tex_type(ray, data);
	tex->x = (int)tex->size * ray->wall;
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_h;
	tex->pos = (ray->start_draw - data->w_height / 2 + ray->line_h / 2) * tex->step;
	j = ray->start_draw;
	while (j < ray->end_draw)
	{
		tex->y = (int)tex->pos;
		tex->pos += tex->step;
		color = get_color_pxl(data, data->tex[tex->type], tex->x, tex->y);
		if (tex->type == NO || tex->type == EA)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->tex_pxl[j][i] = color;
		j++;
	}
	return ;
}
