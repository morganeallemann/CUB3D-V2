#include"../includes/cub3d.h"

static void	render_raycast(t_data *data)
{
	init_ray(&data->ray);
	init_tex_pxl(data);
	raycasting(data, &data->player);
	draw_map(data);
}

void	render_images(t_data *data)
{
	render_raycast(data);
	//if (BONUS)
	//	render_minimap(data);
}

int	render(t_data *data)
{
	data->player.move_on += event_player(data);
	printf("MOVE: %d\n", data->player.move_on);
	if (data->player.move_on == 0)
		return (0);
	render_images(data);
	return (0);
}
