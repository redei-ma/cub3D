/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:35:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:00:11 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include <math.h>

# define WIN_WIDTH 1920			// Window width in pixels
# define WIN_HEIGHT 994			// Window height in pixels

# define PLAYER_SIZE_RATIO 4	// Player collision radius divisor

# define SPEED 0.05f			// Player movement speed
# define R_SPEED 0.02f			// Player rotation speed

# define FOV_ANGLE 1.04719755119659774615	// Field of view (M_PI/3) 60 degrees

# define DOOR_CLOSED 'D'		// Character representing closed door

/**
 * Movement and rotation opcodes for player actions
 */
enum e_opcode
{
	FORWARD,		// Move forward in view direction
	BACKWARD,		// Move backward from view direction
	STRAFE_LEFT,	// Strafe left perpendicular to view
	STRAFE_RIGHT,	// Strafe right perpendicular to view
	ROTATE_LEFT,	// Rotate player left
	ROTATE_RIGHT	// Rotate player right
};

/**
 * DDA (Digital Differential Analyzer) algorithm data structure
 * Contains all parameters needed for ray casting calculations
 */
typedef struct s_dda
{
	int		map_x;			// Current X position in map grid
	int		map_y;			// Current Y position in map grid
	float	ray_dir_x;		// X component of ray direction vector
	float	ray_dir_y;		// Y component of ray direction vector
	float	delta_dist_x;	// Distance ray travels for X-direction unit step
	float	delta_dist_y;	// Distance ray travels for Y-direction unit step
	float	side_dist_x;	// Distance from ray position to next X grid line
	float	side_dist_y;	// Distance from ray position to next Y grid line
	float	perp_wall_dist	// Perpendicular distance to wall (fisheye corrected)
	int		step_x;			// X-direction step (+1 or -1)
	int		step_y;			// Y-direction step (+1 or -1)
	int		side;			// Which side was hit (0=vertical, 1=horizontal)
}	t_dda;

/**
 * Image structure for MLX image handling
 * Contains image data and parameters for pixel manipulation
 */
typedef struct s_image
{
	void	*img;			// MLX image pointer
	char	*addr;			// Memory address of image data
	int		bits_per_pixel	// Color depth information
	int		line_length;	// Bytes per image line
	int		endian;			// Byte order information
}	t_image;

/**
 * Minimap display configuration structure
 * Defines how the minimap is scaled and positioned
 */
typedef struct s_minimap
{
	int		map_width;		// Width of map in grid cells
	int		map_height;		// Height of map in grid cells
	float	minimap_width;	// Minimap width in pixels
	float	minimap_height	// Minimap height in pixels
	float	tile_size_x;	// X size of each tile in pixels
	float	tile_size_y;	// Y size of each tile in pixels
}	t_minimap;

/**
 * Game state and MLX management structure
 * Contains window, input, and animation state
 */
typedef struct s_game
{
	void	*mlx;				// MLX library instance
	void	*win;				// MLX window pointer
	t_image	img;				// Main rendering image
	int		keys_pressed[6];	// Array of pressed key states
	double	mouse_accumulator;	// Mouse movement accumulator for smooth rotation
	int		mouse_enabled;		// Mouse look enabled flag
	int		animation_frame;	// Current animation frame counter
}	t_game;

/**
 * Main game data structure
 * Contains all game state and references to subsystems
 */
typedef struct s_data
{
	t_game				*game;		// Game state and MLX data
	t_player			*player;	// Player position and orientation
	char				**map;		// 2D map array
	t_minimap			mini;		// Minimap configuration
	t_basic_elements	*elements;	// Textures and colors
	t_dda				last_dda;	// Last DDA calculation results
}	t_data;

/* ===== MAIN ===== */
int			close_window(t_data *data);

/* ===== INIT ===== */
void		init_data(t_data *data, t_player *player,
				t_basic_elements *elements);
t_game		*init_game(void);

/* ===== EVENTS ===== */
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
