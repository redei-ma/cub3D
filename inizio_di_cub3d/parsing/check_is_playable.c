/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_playable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:01:34 by ale               #+#    #+#             */
/*   Updated: 2025/06/25 21:39:30 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_target(char c, char *target)
{
	while (*target)
	{
		if (c == *target)
			return (true);
		target++;
	}
	return (false);
}

void	fill(char **map, t_x_and_y size, t_x_and_y current, char *target)
{
	if ((current.y < 0) || (current.x < 0) || (current.y >= size.y)
		|| (current.x >= size.x)
		|| !is_target(map[current.y][current.x], target))
		return ;
	map[current.y][current.x] = '1';
	fill(map, size, (t_x_and_y){current.x - 1, current.y}, target);
	fill(map, size, (t_x_and_y){current.x + 1, current.y}, target);
	fill(map, size, (t_x_and_y){current.x, current.y - 1}, target);
	fill(map, size, (t_x_and_y){current.x, current.y + 1}, target);
}

void	check_map_is_playable(char **map2, char *map_line, char **map1)
{
	int	x;
	int	y;

	y = 0;
	while (map2[y] != NULL)
	{
		x = 0;
		while (map2[y][x] != '\0')
		{
			if (map2[y][x] == 'C' || map2[y][x] == 'E' || map2[y][x] == 'P')
			{
				free_map(map1);
				error ("map is not playble", map2, map_line);
			}
			x++;
		}
		y++;
	}
}

void	find_start(char **map, t_x_and_y *start)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'P')
			{
				start->x = x;
				start->y = y;
			}
			x++;
		}
		y++;
	}
}

void	check_is_playable(char *map_l, t_x_and_y *sz, t_mlx_data *d, char **m1)
{
	char		**map2;
	t_x_and_y	start;

	map2 = create_map(map_l);
	if (!map2)
		error("malloc failed", m1, map_l);
	find_start(map2, &start);
	d->ps = start;
	fill (map2, *sz, start, "PEC0");
	check_map_is_playable(map2, map_l, m1);
	free_map(map2);
}
