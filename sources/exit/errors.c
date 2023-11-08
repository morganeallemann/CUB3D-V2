#include "../includes/cub3d.h"

int	err_msg(char *str, int error)
{
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("\n", 2);
    return (error);
}

void	p_err(char *str)
{
	ft_putstr_fd("Error: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void print_lvl(t_data *data)
{
    int i = 0;
    while (i < data->map_set.height)
    {
        printf("%s\n", data->lvl[i]);
        i++;
    }
}
