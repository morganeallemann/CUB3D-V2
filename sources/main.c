/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by inaranjo          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	(void) av;

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
