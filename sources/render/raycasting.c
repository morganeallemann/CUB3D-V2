#include"../includes/cub3d.h"

void	init_calc(t_ray *ray, int i, t_player *player)
{
	init_ray(ray);
	ray->cam = 2 * i / (double)W_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plan_x * ray->cam; 
	ray->dir_y = player->dir_y + player->plan_y * ray->cam;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1/ ray->dir_y);
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	return ;
}

void	init_step(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
	   ray->step_x = -1;
	   ray->side_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
	return ;
}

void	dda(t_ray *ray, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->lvl[ray->map_x][ray->map_y] > '0')
			hit = 1;
	}
	return ;
}

void	height_ray(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_x - ray->delta_x);
	else
		ray->wall_dist = (ray->side_y - ray->delta_y);
	ray->line_h = (int)(data->w_height / ray->wall_dist);
	ray->start_draw = -(ray->line_h) / 2 + (data->w_height / 2);
	if (ray->start_draw < 0)
		ray->start_draw = 0;
	ray->end_draw = (ray->line_h / 2) + (data->w_height / 2);
	if (ray->end_draw >= data->w_height)
		ray->end_draw = data->w_height - 1;
	if (ray->side == 0)
		ray->wall = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall -= floor(ray->wall);
}

void	raycasting(t_data *data, t_player *player)
{
	t_ray	ray;
	int		i;

	ray = data->ray;
	i = 0;
	while (i < data->w_width)
	{
		init_calc(&ray, i, player);
		init_step(&ray, player);
		dda(&ray, data);
		height_ray(&ray, data, player);
		update_tex_pxl(&ray, data, &data->textures, i);
		i++;
	}
}
