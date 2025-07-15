/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_surrounded_by_wall.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:32:02 by ale               #+#    #+#             */
/*   Updated: 2025/07/15 05:45:56 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_surrounded_by_wall(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_target(map[i][j], "0NSWED"))
			{
				if (i == 0 || j == 0 || i == height || \
!is_target(map[i - 1][j], "10NSWED") || !is_target(map[i][j - 1], "10NSWED") || \
!is_target(map[i + 1][j], "10NSWED") || !is_target(map[i][j + 1], "10NSWED"))
				{
					error("invalid map", NULL);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
