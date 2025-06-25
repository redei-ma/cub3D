#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

typedef struct	s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

typedef struct	s_window
{
	void	*mlx;
	void	*win;
}	t_window;

#endif