/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:59:11 by ale               #+#    #+#             */
/*   Updated: 2025/06/28 02:35:00 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"

#include <stdio.h>

int	main(int argc, char** argv)
{
	t_basic_elements	elements_struct;

	if (handle_parsing(argc, argv, &elements_struct) == 0)
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
	free_basic_elements(&elements_struct);
}
