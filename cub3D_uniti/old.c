/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:16:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/06/30 10:08:56 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**create_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 21);
	if (!map)
		return (NULL);

	map[0] = ft_strdup("11111111111111111111");
	map[1] = ft_strdup("10000000000000000001");
	map[2] = ft_strdup("10010000000000010001");
	map[3] = ft_strdup("10000000000000000001");
	map[4] = ft_strdup("10000110000110000001");
	map[5] = ft_strdup("10000000000000000001");
	map[6] = ft_strdup("10001000000000100001");
	map[7] = ft_strdup("10000000000000000001");
	map[8] = ft_strdup("10000001100000000001");
	map[9] = ft_strdup("10000000000000000001");
	map[10] = ft_strdup("10001000000000100001");
	map[11] = ft_strdup("10000000000000000001");
	map[12] = ft_strdup("10000000110000000001");
	map[13] = ft_strdup("10000000000000000001");
	map[14] = ft_strdup("10000000N00000000001");
	map[15] = ft_strdup("10000000000000000001");
	map[16] = ft_strdup("10000100000010000001");
	map[17] = ft_strdup("10000000000000000001");
	map[18] = ft_strdup("1  0000000000000  1");
	map[19] = ft_strdup("11111111111111111111");
	map[20] = NULL;

	return (map);
}

t_minimap	minimap_init(char **map)
{
	t_minimap	mini;

	mini.map_width = ft_strlen(map[0]);
	mini.map_height = ft_countlines((const char **)map);
	mini.minimap_width = WIN_WIDTH * 0.2;
	mini.minimap_height = WIN_HEIGHT * 0.2
	;
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

// void	draw_fov_to_image(t_data *data)
// {
// 	const t_minimap	mini = minimap_init(data->map);
// 	float			start_angle;
// 	float			angle_step;
// 	int				i;

// 	angle_step = FOV_ANGLE / 60;
// 	start_angle = data->player->angle - FOV_ANGLE / 2;
// 	i = 0;
// 	while (i < FOV_RAYS)
// 	{
// 		draw_single_ray(data, start_angle + i * angle_step, mini);
// 		i++;
// 	}
// }

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
	// draw_fov_to_image(data);
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

// Controlla se una cella è libera
int	is_free_cell(t_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (y >= ft_countlines((const char **)data->map))
		return (0);
	if (x >= (int)ft_strlen(data->map[y]))
		return (0);
	if (data->map[y][x] == '1')
		return (0);
	return (1);
}

// Controlla se può muoversi in una posizione
int	can_move_to(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	return (is_free_cell(data, map_x, map_y));
}

// Controlla movimento con margine di sicurezza
int	can_move_safe(t_data *data, float x, float y)
{
	float	margin;

	margin = 0.2f;
	if (!can_move_to(data, x - margin, y - margin))
		return (0);
	if (!can_move_to(data, x + margin, y - margin))
		return (0);
	if (!can_move_to(data, x - margin, y + margin))
		return (0);
	if (!can_move_to(data, x + margin, y + margin))
		return (0);
	return (1);
}

// Calcola nuova posizione X
float	calc_new_x(t_player *player, int direction)
{
	if (direction == FORWARD)
		return (player->x + cos(player->angle) * SPEED);
	if (direction == BACKWARD)
		return (player->x - cos(player->angle) * SPEED);
	if (direction == STRAFE_LEFT)
		return (player->x + cos(player->angle - M_PI / 2) * SPEED);
	if (direction == STRAFE_RIGHT)
		return (player->x + cos(player->angle + M_PI / 2) * SPEED);
	return (player->x);
}

// Calcola nuova posizione Y
float	calc_new_y(t_player *player, int direction)
{
	if (direction == FORWARD)
		return (player->y + sin(player->angle) * SPEED);
	if (direction == BACKWARD)
		return (player->y - sin(player->angle) * SPEED);
	if (direction == STRAFE_LEFT)
		return (player->y + sin(player->angle - M_PI / 2) * SPEED);
	if (direction == STRAFE_RIGHT)
		return (player->y + sin(player->angle + M_PI / 2) * SPEED);
	return (player->y);
}

// Applica movimento se possibile
void	apply_movement(t_data *data, float new_x, float new_y)
{
	if (can_move_safe(data, new_x, new_y))
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
	else if (can_move_safe(data, new_x, data->player->y))
		data->player->x = new_x;
	else if (can_move_safe(data, data->player->x, new_y))
		data->player->y = new_y;
}

// Movimento principale del giocatore
void	move_player(t_data *data, t_player *player, int direction)
{
	float	new_x;
	float	new_y;

	new_x = calc_new_x(player, direction);
	new_y = calc_new_y(player, direction);
	apply_movement(data, new_x, new_y);
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
