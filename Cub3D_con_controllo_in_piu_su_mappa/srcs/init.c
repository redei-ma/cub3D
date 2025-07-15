/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:15:44 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/08 09:44:28 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_data(t_data *data, t_player *player, t_basic_elements *elements)
{
	data->player = player;
	data->player->x += 0.5;
	data->player->y += 0.5;
	data->map = elements->map;
	data->elements = elements;
	data->mini = init_minimap(data->map);
}

t_minimap	init_minimap(char **map)
{
	t_minimap	mini;

	mini.map_width = ft_strlen(map[0]);
	mini.map_height = ft_countlines((const char **)map);
	mini.minimap_width = WIN_WIDTH * 0.2;
	mini.minimap_height = WIN_HEIGHT * 0.2;
	mini.tile_size_x = mini.minimap_width / mini.map_width;
	mini.tile_size_y = mini.minimap_height / mini.map_height;
	return (mini);
}

static int	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
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
		return (free(game), NULL);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!game->win)
	{
		free(game->mlx);
		free(game);
		return (NULL);
	}
	if (!init_image(game))
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
		free(game);
		return (NULL);
	}
	ft_memset(game->keys_pressed, 0, sizeof(game->keys_pressed));
	game->animation_frame = 0;
	return (game);
}
