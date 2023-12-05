#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    // if (x < 0 || x >= data->img.minimap_w || y < 0 || y >= data->img.minimap_h)
    // {
    //     //printf("je suis en dehors de la map");
    //     return ;
    // }
    
    char	*dst;

    dst = data->img.minimap_addr+ (y * data->img.minimap_line_length + x * (data->img.minimap_bpp / 8));
    *(unsigned int*)dst = color;
}