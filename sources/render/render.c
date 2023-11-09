#include"../includes/cub3d.h"

void	render(t_data *data)
{
	data->player.move_on += event_player(data);
	if (data->player.move_on == 0)
		return ;
	init_ray(&data->ray);
	init_tex_pxl(data);
	raycasting(data, &data->player);
	draw_map(data);
	return ;
}
