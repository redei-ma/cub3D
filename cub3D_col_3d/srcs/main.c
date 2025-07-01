/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:17:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/01 16:59:51 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_data				data;
	t_basic_elements	elements_struct;
	t_player			player;

	if (handle_parsing(argc, argv, &elements_struct, &player) == 0)
		return (0);
	data.game = init_game();
	if (!data.game)
		return (1);
	data.player = &player;
	data.map = elements_struct.map;
	data.elements = &elements_struct;
	data.mini = init_minimap(data.map);
	draw_image(&data);

	mlx_hook(data.game->win, 17, 0, close_window, &data);
	mlx_hook(data.game->win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.game->win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.game->mlx, game_loop, &data);

	mlx_loop(data.game->mlx);
}
