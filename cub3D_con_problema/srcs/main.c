/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:17:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/07 17:08:37 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_data *data)
{
	free_all_textures(data);
	mlx_destroy_image(data->game->mlx, data->game->img.img);
	mlx_destroy_window(data->game->mlx, data->game->win);
	mlx_destroy_display(data->game->mlx);
	free(data->game->mlx);
	free(data->game);
	free_basic_elements(data->elements);
	exit(0);
	return (0);
}

int	animate(t_data *data)
{
	data->game->animation_frame++;
	if (data->game->animation_frame >= 10)
	{
		if (data->elements->north_curr.img == data->elements->north1.img)
			data->elements->north_curr = data->elements->north2;
		else
			data->elements->north_curr = data->elements->north1;
		data->game->animation_frame = 0;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data				data;
	t_basic_elements	elements_struct;
	t_player			player;

	if (handle_parsing(argc, argv, &elements_struct, &player) == 0)
		return (1);
	data.game = init_game();
	if (!data.game)
		return (1);
	data.player = &player;
	data.map = elements_struct.map;
	data.elements = &elements_struct;
	if (!init_all_texture_files(&data))
	{
		error("can't load textures", NULL);
		close_window(&data);
		return (1);
	}
	data.mini = init_minimap(data.map);
	mlx_hook(data.game->win, 17, 0, close_window, &data);
	mlx_hook(data.game->win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.game->win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.game->win, 6, 1L << 6, mouse_hook, &data);
	mlx_loop_hook(data.game->mlx, game_loop, &data);
	mlx_loop(data.game->mlx);
}
