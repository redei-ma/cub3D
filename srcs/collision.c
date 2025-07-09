/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:50:23 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/09 12:27:55 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Checks if a map position contains a wall or closed door
int	is_wall_hit(t_data *data, int map_x, int map_y)
{
	char	cell;

	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= ft_countlines((const char **)data->map))
		return (1);
	if (map_x >= (int)ft_strlen(data->map[map_y]))
		return (1);
	cell = data->map[map_y][map_x];
	if (cell == '1' || cell == DOOR_CLOSED)
		return (1);
	return (0);
}

// Checks if player can move to a specific position by testing 
// collision at four corners
// Uses player radius to test collision at all edges of the player's 
// bounding box
int	check_player_collision(t_data *data, float x, float y)
{
	float	radius;
	int		check_x;
	int		check_y;

	radius = 1.0f / PLAYER_SIZE_RATIO;
	check_x = (int)(x - radius);
	check_y = (int)(y - radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	check_x = (int)(x + radius);
	check_y = (int)(y - radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	check_x = (int)(x - radius);
	check_y = (int)(y + radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	check_x = (int)(x + radius);
	check_y = (int)(y + radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	return (1);
}
