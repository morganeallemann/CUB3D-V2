#include"../includes/cub3d.h"

void    init_north_south(t_data *data)
{
    if (data->player.dir == 'S')
    {
        data->player.dir_x = 0;
        data->player.dir_y = 1;
        data->player.plan_x = -0.66;
        data->player.plan_y = 0;
    }
    if (data->player.dir == 'N')
    {
        data->player.dir_x = 0;
        data->player.dir_y = -1;
        data->player.plan_x = 0.66;
        data->player.plan_y = 0;
    }
    return ;
}

void    init_east_west(t_data *data)
{
    if (data->player.dir == 'E')
    {
        data->player.dir_x = 1;
        data->player.dir_y = 0;
        data->player.plan_x = 0;
        data->player.plan_y = 0.66;
    }
    if (data->player.dir == 'W')
    {
        data->player.dir_x = -1;
        data->player.dir_y = 0;
        data->player.plan_x = 0;
        data->player.plan_y = -0.66;
    }
    return ;
}
void    init_player_dir(t_data *data)
{
    init_north_south(data);
    init_east_west(data);
    return ;
}
