/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vari.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:59 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/07 15:09:20 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_map(char **map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_basic_elements(t_basic_elements *str)
{
	if (str->north_texture1 != NULL)
	{
		free(str->north_texture1);
		str->north_texture1 = NULL;
	}
	if (str->south_texture != NULL)
	{
		free(str->south_texture);
		str->south_texture = NULL;
	}
	if (str->west_texture != NULL)
	{
		free(str->west_texture);
		str->west_texture = NULL;
	}
	if (str->east_texture != NULL)
	{
		free(str->east_texture);
		str->east_texture = NULL;
	}
	if (str->map != NULL)
	{
		free_map(str->map);
		str->map = NULL;
	}
}
