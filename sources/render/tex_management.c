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

int	get_color_pxl(t_img *img, int x, int y)
{
	int	pos;
	int	color;

	if (x < 0 || x >= img->img_w || y < 0 || y >= img->img_h)
		return (0);
	pos = (y * img->line_length + x * (img->bpp / 8));
	color = *(unsigned int *)(img->address + pos);
	return (color);
}

void	update_tex_pxl(t_ray *ray, t_data *data, t_textures *tex, int x)
{ 
	int	y;
	int	color;

	y = 0;
	color = 0;
	tex_type(ray, data);
	tex->x = (int)((double)tex->size * ray->wall);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_h;
	tex->pos = (ray->start_draw - data->w_height / 2 + ray->line_h / 2) * tex->step;
	y = ray->start_draw;
	while (y < ray->end_draw)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = get_color_pxl(data->tex[tex->type], tex->x, tex->y);
		//color = 0xFF;
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->tex_pxl[y][x] = color;
		y++;
	}
	return ;
}
