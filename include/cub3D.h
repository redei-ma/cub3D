#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define M_PI 3.14159265358979323846

# define SPEED 0.2f
# define R_SPEED 0.5f
# define FOV_ANGLE (M_PI / 3) // 60 degrees
# define FOV_RAYS 60 // Number of rays in the field of view

enum opcode
{
	FORWARD,
	BACKWARD,
	STRAFE_LEFT,
	STRAFE_RIGHT
};

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	// int		width;
	// int		height;
}	t_image;

typedef struct	s_minimap
{
	int	map_width;
	int	map_height;
	int	minimap_width;
	int	minimap_height;
	int	tile_size_x;
	int	tile_size_y;
}	t_minimap;

typedef struct	s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_image		img;
	// t_player	*player;
}	t_game;

typedef struct s_data
{
	t_game		*game;
	t_player	*player;
	char		**map;
}	t_data;

#endif