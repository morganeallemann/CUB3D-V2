#include"../includes/cub3d.h"

int	check_key(int key, t_data *data)
{
	if (key == KEY_ESC)
		close_window(data, 0);
	if (key == KEY_W)
		data->player.move_y = 1;
	if (key == KEY_S)
		data->player.move_y = -1;
	if (key == KEY_A)
		data->player.move_x = -1;
	if (key == KEY_D)
		data->player.move_x = 1;
	if (key == L_KEY)
		data->player.rotation -= 1;
	if (key == R_KEY)
		data->player.rotation += 1;
	return (0);
}

int	init_move(int key, t_data *data)
{
	if (key == KEY_ESC)
		close_window(data, 0);
	if (key == KEY_W && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == KEY_S && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == KEY_A && data->player.move_x == -1)
		data->player.move_x = 0;
	if (key == KEY_D && data->player.move_x == 1)
		data->player.move_x = 0;
	if (key == L_KEY && data->player.rotation <= 1)
		data->player.rotation = 0;
	if (key == R_KEY && data->player.rotation >= -1)
		data->player.rotation = 0;
	return (0);
}

void	events_key(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, check_key, data);
	mlx_hook(data->win, 2, 1L << 0, init_move, data);
	//mlx_hook(data->win, 17, 1L << 0, close_window, cube);
}
