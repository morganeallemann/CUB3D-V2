/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:45:32 by malleman          #+#    #+#             */
/*   Updated: 2023/11/22 16:07:11 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* -- LIBRARY -- */
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

/* -- MACROS -- */
/* Taille de la window */
# define W_WIDTH  1028
# define W_HEIGHT 500

/* Résolution des textures */
# define TXT_SIZE 64

/* Résolution FOV-mini_map*/
# define FOV_COLOR 0xFFFFFF
# define MAX_RAY_DISTANCE 20.0 
# define FAT_RAY 2
# define NBR_RAYS 30

/* Touches clavier */
# define L_KEY 123
# define R_KEY 124
# define D_KEY 125
# define U_KEY 126
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_M 46
# define KEY_ESC 53

/* -- STRCUTURES -- */
enum e_map_dir
{
	NO,
	SO,
	WE,
	EA,
	EOF_MAP,
};

typedef struct s_img
{
	void	*img;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		img_h;
	int		img_w;
	void	*minimap_img;
    char	*minimap_addr;
    int		minimap_bpp;
    int		minimap_line_length;
    int		minimap_endian;
	int		minimap_w;
	int		minimap_h;
	int		block_size;
}			t_img;

typedef struct s_sprite
{
    void    *img_spr;       // Pointeur vers l'image du sprite
	char	*addr_spr;
	int		bpp_spr;
	int		line_length_spr;
	int		endian_spr;
    int     width;      // Largeur du sprite
    int     height;     // Hauteur du sprite
    char    *path;      // Chemin de l'image du sprite
} t_sprite;


typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	int				*floor;
	int				*ceiling;
	int				size;
	int				x;
	int				y;
	int				type;
	double			step;
	double			pos;
	unsigned long	conv_floor;
	unsigned long	conv_ceiling;
}			t_textures;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plan_x;
	double	plan_y;
	double	fov_angle; // Angle du champ de vision
    double	fov_range; // Portée du champ de vision
	int		move_on;
	int		move_x;
	int		move_y;
	int		rotation;
}			t_player;

typedef struct s_map
{
	int			fd;
	int			nb_lines;
	int			height;
	int			width;
	int			end_of_map;
	char		**map;
	char		*map_fd;
}			t_map;

typedef struct s_ray
{
	double	cam;
	double	dir_x;
	double	dir_y;
	double	wall_dist;
	double	wall;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		line_h;
	int		start_draw;
	int		end_draw;
	int		side;

}			t_ray;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**lvl;
	int				w_height;
	int				w_width;
	int				**tex_pxl;
	t_sprite 		spr;
	t_img			**tex;
	t_map			map_set;
	t_player		player;
	t_textures		textures;
	t_img			img;
	t_ray			ray;
}			t_data;

/* -- FONCTIONS PROJETS -- */
/* Initialisations */
void	init_struct(t_data *data);
void	init_tex_data(t_textures *textures);
void	init_player_dir(t_data *data);
void	init_tex(t_data *data);
void	init_ray(t_ray *ray);
void	init_tex_pxl(t_data *data);
void	init_img(t_img *img);

/* Parsing */
int		parse(t_data *data, char **av);
void	parse_map(char *map_fd, t_data *data);
int		get_map_info(t_data *data, char **map);
int		get_tex_color(t_textures *textures, char *line, int j);
int		checker_map(t_data *data, char **map);
int		checker_side(t_data *data, char **map);
int		create_map(t_data *data, char **map, int i);
int		checker_textures(t_textures *textures);

/* Gestion des mouvements */
void	events_key(t_data *data);
int		event_player(t_data *data);
int		player_rot(t_data *data, double rot);
int		checker_move(t_data *data, double x, double y);
int		init_move(int key, t_data *data);

/* Gestion de la partie graphique */
int		render(t_data *data);
void	render_images(t_data *data);
void	raycasting(t_data *data, t_player *player);
void	update_tex_pxl(t_ray *ray, t_data *data, t_textures *txt, int i);
void	draw_map(t_data *data);
void	mini_player(t_data *data, int *player_x, int *player_y);

/* Gestion de la minimap */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_square(t_data *data, int draw_x, int draw_y, int color);
void	draw_player(t_data *data);
void	resize_block(t_data *data);
void	draw_minimap(t_data *data);

/* Gestion de la FOV (affichage-minimap) */
void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);
void	draw_fov(t_data *data);
void	fat_line(t_data *data, int x0, int y0, int x1, int y1, int color, int fat);
void	cal_sx_sy(int x0, int y0, int x1, int y1, int *sx, int *sy);
void cast_ray(t_data *data, int player_x, int player_y, double ray_angle);

/* Gestion de sprite player
int load_sprite_image(t_data *data, char *file_path);
void draw_player_sprite(t_data *data);*/

/* Gestion d'erreurs */
int		err_msg(char *str, int error);
void	p_err(char *str);
int		free_data(t_data *data);
void	free_tab(void **tab);
void	print_lvl(t_data *data);

/* Gestion de la window */
void	init_mlx(t_data *data);
void	close_window(t_data *data, int code);
int		exit_game(t_data *data);

#endif