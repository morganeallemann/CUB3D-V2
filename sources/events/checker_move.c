#include "../includes/cub3d.h"

int	check_wall(t_data *data, double x, double y)
{
	if (data->lvl[(int)x][(int)y] == '1')
		return (1);
	return (0);
}

/*FONCTION A CORRIGER ELLE LE SECOND IF NE FONCTIONNE PAS !*/
int	check_map_pos(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= data->map_set.width - 1.25)
	{
		printf("FALSE\n");
		return (1);
	}
	if (y < 0.25 || y >= data->map_set.height - 0.25)
	{
		printf("FALS\n");
		return (1);
	}
	return (0);
}

int	check_pos(t_data *data, double x, double y)
{
	if (check_wall(data, x, y))
		return (1);
	return (0);
}

int	checker_move(t_data *data, double x, double y)
{
	int	checker;

	checker = 0;
	if (check_pos(data, x, data->player.pos_y) == 0)
	{
		checker++;
		data->player.pos_x = x;
	}
	if (check_pos(data, data->player.pos_x, y) == 0)
	{
		checker++;
		data->player.pos_y = y;
	}
	return (checker);
}
