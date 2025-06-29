/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_play.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:16:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/06/27 16:51:28 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**create_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);

	map[0] = ft_strdup("1111111111");
	map[1] = ft_strdup("1000000001");
	map[2] = ft_strdup("1011001101");
	map[3] = ft_strdup("1010000101");
	map[4] = ft_strdup("1000110001");
	map[5] = ft_strdup("1000110001");
	map[6] = ft_strdup("1010000101");
	map[7] = ft_strdup("1111N01101");
	map[8] = ft_strdup("1  1000001");
	map[9] = ft_strdup("1111111111");
	map[10] = NULL;

	return (map);
}

t_minimap	minimap_init(char **map)
{
	t_minimap	mini;

	mini.map_width = ft_strlen(map[0]);
	mini.map_height = ft_countlines((const char **)map);
	mini.minimap_width = WIN_WIDTH * 0.2;
	mini.minimap_height = WIN_HEIGHT * 0.2;
	mini.tile_size_x = mini.minimap_width / mini.map_width;
	mini.tile_size_y = mini.minimap_height / mini.map_height;
	return (mini);
	// capire se le variabile posso definirel nel .h dato che in teoria il DDA si basa sulla tile_size della minimappa
}

void	put_pixel_to_image(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	draw_single_ray(t_data *data, float angle, t_minimap mini)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;

	ray_x = data->player->x;
	ray_y = data->player->y;
	step_x = cos(angle) * 0.02f;
	step_y = sin(angle) * 0.02f;
	while (ray_x >= 0 && ray_x < mini.map_width && 
		ray_y >= 0 && ray_y < mini.map_height &&
		data->map[(int)ray_y][(int)ray_x] != '1')
	{
		put_pixel_to_image(&data->game->img, 
			ray_x * mini.tile_size_x, 
			ray_y * mini.tile_size_y, 
			0xFF0000);
		ray_x += step_x;
		ray_y += step_y;
	}
}

void	draw_fov_to_image(t_data *data)
{
	const t_minimap	mini = minimap_init(data->map);
	float			start_angle;
	float			angle_step;
	int				i;

	angle_step = FOV_ANGLE / 60;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	i = 0;
	while (i < FOV_RAYS)
	{
		draw_single_ray(data, start_angle + i * angle_step, mini);
		i++;
	}
}

void	draw_player_to_image(t_data *data, int center_x, int center_y, int color)
{
	const t_minimap	mini = minimap_init(data->map);
	int				radius;
	int				i;
	int				j;

	radius = mini.tile_size_x / 4;
	j = -radius;
	while (j <= radius)
	{
		i = -radius;
		while (i <= radius)
		{
			if (i * i + j * j <= radius * radius)
				put_pixel_to_image(&data->game->img, center_x + i, center_y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_tile_to_image(t_data *data, int start_x, int start_y, int color)
{
	const t_minimap	mini = minimap_init(data->map);
	int				i;
	int				j;

	j = 0;
	while (j < mini.tile_size_y)
	{
		i = 0;
		while (i < mini.tile_size_x)
		{
			put_pixel_to_image(&data->game->img, start_x + i, start_y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_minimap_to_image(t_data *data)
{
	const t_minimap	mini = minimap_init(data->map);
	int				x;
	int				y;

	y = 0;
	while (y < mini.map_height)
	{
		x = 0;
		while (x < mini.map_width)
		{
			if (data->map[y][x] == '1')
				draw_tile_to_image(data, x * mini.tile_size_x, y * mini.tile_size_y, 0xFFFFFF); // walll
			else if (data->map[y][x] == ' ')
				; // space
			else
				draw_tile_to_image(data, x * mini.tile_size_x, y * mini.tile_size_y, 0xC0C0C0); // floor or player
			x++;
		}
		y++;
	}
	draw_player_to_image(data, data->player->x * mini.tile_size_x, data->player->y * mini.tile_size_y, 0x00FF00);
	// vorrei spostarlo in draw_image
}

void	draw_image(t_data *data)
{
	draw_minimap_to_image(data);
	draw_fov_to_image(data);
	mlx_put_image_to_window(data->game->mlx, data->game->win, data->game->img.img, 0, 0);
}

t_player	*set_player(void)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->x = 1.5;
	player->y = 1.5;
	player->angle = M_PI;
	return (player);
}

int	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
		&game->img.line_length, &game->img.endian);
	// game->img.width = WIN_WIDTH;
	// game->img.height = WIN_HEIGHT;
	return (1);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (NULL);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!game->win)
		return (NULL);
	if (!init_image(game))
		return (NULL);
	return (game);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->game->mlx, data->game->win);
	//manca il resto
	exit(0);
	return (0);
}

void move_player(t_data *data, t_player *player, int direction)
{
	// decidere se fare un funzione diversa per ogni direzione
	float	new_x;
	float	new_y;
	
	new_x = 0;
	new_y = 0;
	if (direction == FORWARD)
	{
		new_x = player->x + cos(player->angle) * SPEED;
		new_y = player->y + sin(player->angle) * SPEED;
	}
	else if (direction == BACKWARD)
	{
		new_x = player->x - cos(player->angle) * SPEED;
		new_y = player->y - sin(player->angle) * SPEED;
	}
	else if (direction == STRAFE_LEFT)
	{
		new_x = player->x + cos(player->angle - M_PI/2) * SPEED;
		new_y = player->y + sin(player->angle - M_PI/2) * SPEED;
	}
	else if (direction == STRAFE_RIGHT)
	{
		new_x = player->x + cos(player->angle + M_PI/2) * SPEED;
		new_y = player->y + sin(player->angle + M_PI/2) * SPEED;
	}
	
	// TODO: Collision detection
	
	player->x = new_x;
	player->y = new_y;
	draw_image(data);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC key
		close_window(data);
	else if (keycode == 'w')
		move_player(data, data->player, FORWARD);
	else if (keycode == 's')
		move_player(data, data->player, BACKWARD);
	else if (keycode == 'a')
		move_player(data, data->player, STRAFE_LEFT);
	else if (keycode == 'd')
		move_player(data, data->player, STRAFE_RIGHT);
	else if (keycode == 65361) // Freccia sinistra
	{
		data->player->angle -= R_SPEED;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
		draw_image(data);
	}
	else if (keycode == 65363) // Freccia destra
	{
		data->player->angle += R_SPEED;
		if (data->player->angle >= 2 * M_PI)
			data->player->angle -= 2 * M_PI;
		draw_image(data);
	}
	return (0);
}

int	main(void)
{
	t_data	data;

	data.game = init_game();
	if (!data.game)
		return (1); // handle error
	data.player = set_player(); // in teoria dovrebbe venire settato nel parsing
	if (!data.player)
		return (1); // handle error
	data.map = create_map(); // have to take parsing map adress
	draw_image(&data);

	mlx_hook(data.game->win, 17, 0, close_window, &data);
	mlx_hook(data.game->win, 2, 1L << 0, key_press, &data);
	

	mlx_loop(data.game->mlx);
}
