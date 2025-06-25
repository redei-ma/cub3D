/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:59:11 by ale               #+#    #+#             */
/*   Updated: 2025/06/25 02:59:35 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"

#include <stdio.h>

int	main(int argc, char** argv)
{
	t_basic_elements	elements_struct;

	if (!handle_map(argc, argv, &elements_struct))
		return (0);
	printf("NO: %s\n", elements_struct.north_texture);
	printf("SO: %s\n", elements_struct.south_texture);
	printf("WE: %s\n", elements_struct.west_texture);
	printf("EA: %s\n", elements_struct.east_texture);
}
