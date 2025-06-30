/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:59:11 by ale               #+#    #+#             */
/*   Updated: 2025/06/30 20:38:28 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"

#include <stdio.h>

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
}
