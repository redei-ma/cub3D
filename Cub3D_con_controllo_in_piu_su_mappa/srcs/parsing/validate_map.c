/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:01:34 by ale               #+#    #+#             */
/*   Updated: 2025/07/15 04:39:03 by ale              ###   ########.fr       */
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

int	fill(char **map, int *size, t_player current, char *target)
{
	if (map[(int) current.y][(int) current.x] == '1')
	{
		return (0);
	}
	else if ((current.y <= 0) || (current.x <= 0) || (current.y >= size[1]) \
			|| (current.x >= size[0]) \
			|| !is_target(map[(int) current.y][(int) current.x], target))
	{
		return (-1);
	}
	map[(int) current.y][(int) current.x] = '1';
	if (fill(map, size, (t_player){current.x - 1, current.y, 0}, target) == -1)
		return (-1);
	if (fill(map, size, (t_player){current.x + 1, current.y, 0}, target) == -1)
		return (-1);
	if (fill(map, size, (t_player){current.x, current.y - 1, 0}, target) == -1)
		return (-1);
	if (fill(map, size, (t_player){current.x, current.y + 1, 0}, target) == -1)
		return (-1);
	return (1);
}

float	get_starting_angle(char starting_position)
{
	float	starting_angle;

	if (starting_position == 'N')
		starting_angle = (M_PI * 3) / 2;
	if (starting_position == 'E')
		starting_angle = 0;
	if (starting_position == 'S')
		starting_angle = M_PI / 2;
	if (starting_position == 'W')
		starting_angle = M_PI;
	return (starting_angle);
}

void	find_start(char **map, t_player *start)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || \
				map[y][x] == 'W' || map[y][x] == 'E')
			{
				start->x = x;
				start->y = y;
				start->angle = get_starting_angle(map[y][x]);
			}
			x++;
		}
		y++;
	}
}

int	validate_map(char *map_line, t_player *start)
{
	char		**map2;
	int			map_size[2];

	map2 = create_map(map_line, get_longest_line(map_line));
	if (!map2)
		return (0);
	find_start(map2, start);
	map_size[0] = get_longest_line(map_line) - 1;
	map_size[1] = ft_countlines((const char **) map2) - 1;
	free(map_line);
	if (fill (map2, map_size, *start, "NSWE0D") == -1)
	{
		free_map(map2);
		error("invalid map", NULL);
		return (0);
	}
	free_map(map2);
	return (1);
}
