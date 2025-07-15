/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:35:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/08 15:26:42 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "parsing.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 994

# define PLAYER_SIZE_RATIO 4

# define SPEED 0.05f
# define R_SPEED 0.02f

# define FOV_ANGLE 1.04719755119659774615 // (M_PI/3) 60 degrees

# define DOOR_CLOSED 'D'

enum e_opcode
{
	FORWARD,
	BACKWARD,
	STRAFE_LEFT,
	STRAFE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT
};

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_minimap
{
	int		map_width;
	int		map_height;
	float	minimap_width;
	float	minimap_height;
	float	tile_size_x;
	float	tile_size_y;
}	t_minimap;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_image	img;
	int		keys_pressed[6];
	double	mouse_accumulator;
	int		animation_frame;
}	t_game;

typedef struct s_data
{
	t_game				*game;
	t_player			*player;
	char				**map;
	t_minimap			mini;
	t_basic_elements	*elements;
	t_dda				last_dda;
}	t_data;

/* ===== MAIN ===== */
int			close_window(t_data *data);

/* ===== INIT ===== */
void		set_data(t_data *data, t_player *player,
				t_basic_elements *elements);
t_minimap	init_minimap(char **map);
t_game		*init_game(void);

/* ===== EVENTS ===== */
int			animate(t_data *data);
int			game_loop(t_data *data);
int			key_release(int keycode, t_data *data);
int			key_press(int keycode, t_data *data);

/* ===== MOUSE EVENTS ===== */
void		rotate_player_mouse(t_data *data, int delta_x);
int			mouse_hook(int x, int y, t_data *data);

/* ===== DDA ===== */
float		cast_ray_dda(t_data *data, float start_x, float start_y,
				float angle);

/* ===== COLLISION ===== */
int			is_wall_hit(t_data *data, int map_x, int map_y);
int			check_player_collision(t_data *data, float x, float y);

/* ===== MOVEMENT ===== */
void		move_player(t_data *data, t_player *player, int direction);
void		rotate_player(t_data *data, int direction);

/* ===== TEXTURES ===== */
void		free_all_textures(t_data *data);
int			load_single_texture_file(t_data *data, t_texture *tex, char *path);
int			init_all_texture_files(t_data *data);

/* ===== TEXTURE UTILS ===== */
float		calculate_wall_x(t_data *data);
int			get_texture_color(t_texture *texture, int tex_x, int tex_y);
t_texture	*get_texture_index(t_data *data);

/* ===== RENDER TEXTURES ===== */
void		draw_textured_wall_column(t_data *data, int x, int wall_bounds[2],
				int wall_height);

/* ===== 3D UTILS ===== */
int			calculate_wall_height(float wall_distance);
void		calculate_draw_limits(int wall_height, int *draw_start,
				int *draw_end);
float		apply_fisheye_correction(float wall_distance,
				float ray_angle, float player_angle);
float		calculate_ray_angle(t_data *data, int column_x);

/* ===== 3D DRAWING ===== */
void		draw_3d_to_image(t_data *data);

/* ===== MINIMAP ===== */
void		draw_minimap_to_image(t_data *data);

/* ===== DRAWING ===== */
void		put_pixel_to_image(t_image img, int x, int y, int color);
void		draw_image(t_data *data);

/* ===== DRAWING ===== */
void		interact_with_door(t_data *data);

#endif
