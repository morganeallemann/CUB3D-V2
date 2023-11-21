#include"../includes/cub3d.h"

int	move_up(t_data *data, double speed)
{
	double	new_pos_x;
	double	new_pos_y;
	int		check_move;

	new_pos_x = data->player.pos_x + data->player.dir_x * speed;
	new_pos_y = data->player.pos_y + data->player.dir_y * speed;
	check_move = checker_move(data, new_pos_x, new_pos_y);
	return (check_move);	
}

int	move_down(t_data *data, double speed)
{
	double	new_pos_x;
	double	new_pos_y;
	int		check_move;

	new_pos_x = data->player.pos_x - data->player.dir_x * speed;
	new_pos_y = data->player.pos_y - data->player.dir_y * speed;
	check_move = checker_move(data, new_pos_x, new_pos_y);
	return (check_move);	
}

int	move_left(t_data *data, double speed)
{
	double	new_pos_x;
	double	new_pos_y;
	int		check_move;

	new_pos_x = data->player.pos_x + data->player.dir_y * speed;
	new_pos_y = data->player.pos_y - data->player.dir_x * speed;
	check_move = checker_move(data, new_pos_x, new_pos_y);
	return (check_move);	
}

int move_right(t_data *data, double speed)
{
	double	new_pos_x;
	double	new_pos_y;
	int		check_move;

	new_pos_x = data->player.pos_x - data->player.dir_y * speed;
	new_pos_y = data->player.pos_y + data->player.dir_x * speed;
	check_move = checker_move(data, new_pos_x, new_pos_y);
	return (check_move);
}

int	event_player(t_data *data)
{
	int		step;
	double	speed;

	step = 0;
	speed = 0.15;
	if (data->player.move_x == 1)
		step += move_right(data, speed);
	if (data->player.move_x == -1)
		step += move_left(data, speed);
	if (data->player.move_y == 1)
		step += move_up(data, speed);
	if (data->player.move_y == -1)
		step += move_down(data, speed);
	if (data->player.rotation != 0)
		step += player_rot(data, data->player.rotation);
	return (step);
}
