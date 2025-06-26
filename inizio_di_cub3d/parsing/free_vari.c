/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vari.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:59 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/25 16:31:28 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_map(char **map)
{
	int i;
	int j;

	if (map == NULL)
		return ;
	i = 0;
	j = 0;
	while(map[i])
	{
		free(map[i]);
	}
	free(map);
}

void	free_basic_elements(t_basic_elements *str)
{
	if (str->north_texture != NULL)
		free(str->north_texture);
	if (str->south_texture != NULL)
		free(str->south_texture);
	if (str->west_texture != NULL)
		free(str->west_texture);
	if (str->east_texture != NULL)
		free(str->east_texture);
	if (str->map != NULL)
		free_map(str->map);
}