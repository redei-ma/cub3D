#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "parsing.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

#define PLAYER_SIZE_RATIO 3

# define SPEED 0.035f
# define R_SPEED 0.02f

# define FOV_ANGLE (M_PI / 3) // 60 degrees
# define FOV_RAYS 500 // Number of rays in the field of view

enum opcode
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
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct	s_minimap
{
	int		map_width;
	int		map_height;
	float	minimap_width;
	float	minimap_height;
	float	tile_size_x;
	float	tile_size_y;
}	t_minimap;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_image	img;
	int		keys_pressed[6];
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


// ========== INIT.C ==========
t_minimap	init_minimap(char **map);
t_player	*set_player(void);
t_game		*init_game(void);

// ========== DRAWING.C ==========
void		put_pixel_to_image(t_image img, int x, int y, int color);
void		draw_fov_to_image(t_data *data);
void		draw_image(t_data *data);

// ========== MOVEMENT.C ==========
void		move_player(t_data *data, t_player *player, int direction);
void		rotate_player(t_data *data, int direction);

// ========== EVENTS.C ==========
int			key_release(int keycode, t_data *data);
int			key_press(int keycode, t_data *data);
int 		game_loop(t_data *data);
int			close_window(t_data *data);

// ========== DDA.C ==========

float	cast_ray_dda(t_data *data, float start_x, float start_y, float angle);
int		check_player_collision(t_data *data, float x, float y);
void	draw_single_ray(t_data *data, float angle, t_minimap mini);

// ========== DRAWING_3D.C ==========

// void	draw_single_line_of_wall_h(t_data *data, int j, float wall_dist);
// void	draw_single_line_of_wall(t_data *data, float angle, int j);
void	draw_3d_to_image(t_data *data);
//void	put_window_black(t_data *data);

// ========== LOAD_TEXTURES.C ==========

void	free_all_textures(t_data *data);
int		load_single_texture_file(t_data *data, t_texture *tex, char *path);
int		init_all_texture_files(t_data *data);

#endif
