/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:17:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/06/30 21:18:25 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/* 
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
	map[18] = ft_strdup("1  0000000000000  1 ");
	map[19] = ft_strdup("11111111111111111111");
	map[20] = NULL;

	return (map);
} */
int	main(int argc, char **argv)
{
	t_data				data;
	t_basic_elements	elements_struct;
	t_player			player;

	if (handle_parsing(argc, argv, &elements_struct, &player) == 0)
		return (0);
	data.game = init_game();
	if (!data.game)
		return (1); // handle error
	data.player = &player; // in teoria dovrebbe venire settato nel parsing
	if (!data.player)
		return (free_basic_elements(&elements_struct), 1); // non serve sto error credo
	data.map = elements_struct.map; // have to take parsing map adress
	draw_image(&data);

	mlx_hook(data.game->win, 17, 0, close_window, &data);
	mlx_hook(data.game->win, 2, 1L << 0, key_press, &data);
	// mlx_hook(data.game->win, 3, 1L << 1, key_release, &data);
	// mlx_loop_hook(data.game->mlx, game_loop, &data);

	
	mlx_loop(data.game->mlx);
}
/* #include <stdio.h>
int	main(int argc, char** argv)
{
	t_basic_elements	elements_struct;
	t_player			player;

	if (handle_parsing(argc, argv, &elements_struct, &player) == 0)
		return (0);
	printf("NO: %s\n", elements_struct.north_texture);
	printf("SO: %s\n", elements_struct.south_texture);
	printf("WE: %s\n", elements_struct.west_texture);
	printf("EA: %s\n", elements_struct.east_texture);
	printf("F: %d\n", elements_struct.floor_colours[0]);
	printf("F: %d\n", elements_struct.floor_colours[1]);
	printf("F: %d\n", elements_struct.floor_colours[2]);
	printf("C: %d\n", elements_struct.ceiling_colours[0]);
	printf("C: %d\n", elements_struct.ceiling_colours[1]);
	printf("C: %d\n", elements_struct.ceiling_colours[2]);
	int i = 0;
	while(elements_struct.map != NULL && elements_struct.map[i] != NULL)
	{
		printf(" '%s'\n", elements_struct.map[i]);
		i++;
	}
//	elements_struct.start_pos->angle += 1;
//	elements_struct.start_pos->x += 1;
//	elements_struct.start_pos->y += 1;
	printf("angle: %f\2\n", elements_struct.start_pos->angle);
	printf("x: %f\2\n", elements_struct.start_pos->x);
	printf("y: %f\2\n", elements_struct.start_pos->y);
	free_basic_elements(&elements_struct);
} */
