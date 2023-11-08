#include "../includes/cub3d.h"

void	init_tex_data(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->ea = NULL;
	textures->we = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
	textures->size = TXT_SIZE;
	textures->x = 0;
	textures->y = 0;
	textures->type = 0;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->conv_ceiling = 0;
	textures->conv_floor = 0;
}

t_img	*load_xpm(t_data *data, char *path)
{
	t_img	*img;

	printf("PATH:%s", path);
	printf("\n");
	printf("coucou");
	img = malloc(sizeof(t_img));
	if (!img)
	{
		err_msg("Malloc allocation failed", 1);
		close_window(data, 1);
	}
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->img_w, &img->img_h);
	if (!img->img)
	{
		free(img);
		p_err("MLX init ptr failed");
	}
	img->address = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	return (img);
}
void	init_tex(t_data *data)
{
	data->tex = malloc(sizeof(t_img *) * 5);
	data->tex[NO] = load_xpm(data, data->textures.no);
	data->tex[SO] = load_xpm(data, data->textures.so);
	data->tex[WE] = load_xpm(data, data->textures.we);
	data->tex[EA] = load_xpm(data, data->textures.ea);
	data->tex[EOF_MAP] = NULL;
}