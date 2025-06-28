/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vari.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:59 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/28 01:48:38 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_map(char **map)
{
	int i;

	if (map == NULL)
		return ;
	i = 0;
		while(map[i])
	{
		free(map[i]);
		i++;
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
