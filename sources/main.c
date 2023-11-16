#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		init_struct(&data);
		if (parse(&data, av) != 0)
			return (free_data(&data));
		init_mlx(&data);
		init_tex(&data);
        render_images(&data);
		events_key(&data);
        mlx_loop_hook(data.mlx, render, &data);
		mlx_loop(data.mlx);
	}
	else
		return (err_msg("Args number is wrong.", 1));
	return (0);
}