#include "../includes/cub3d.h"

int	rotation(t_data *data, double speed_r)
{
	t_player	*p;
	double		tmp;

	p = &data->player;
	tmp = p->dir_x;
	p->dir_x = p->dir_x * cos(speed_r) - p->dir_y * sin(speed_r);
	p->dir_y = tmp * sin(speed_r) + p->dir_y * cos(speed_r);
	tmp = p->plan_x;
	p->plan_x = p->plan_x * cos(speed_r) - p->plan_y * sin(speed_r);
	p->plan_y = tmp * sin(speed_r) + p->plan_y * cos(speed_r);
	return (1);
}

int	player_rot(t_data *data, double rot)
{
	int		move;
	double	speed_r;

	move = 0;
	speed_r = 0.1 * rot;
	move += rotation(data, speed_r);
	return (move);
}
