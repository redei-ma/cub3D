/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:50:23 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 10:58:43 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Checks if a specific position in the map contains a wall or closed door
 * 
 * @param data: main game structure containing the map
 * @param map_x: X coordinate in the grid to check
 * @param map_y: Y coordinate in the grid to check
 * @return: 1 if position contains a wall/closed door or is out of bounds, 0 otherwise
 * 
 * This function performs boundary checks to prevent illegal memory access
 * and then checks if the cell contains:
 * - '1': wall
 * - DOOR_CLOSED: closed door (both considered solid obstacles)
 */
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

/**
 * Checks if the player can move to a specific position without colliding
 * 
 * @param data: main game structure containing the map
 * @param x: new X coordinate where player wants to move
 * @param y: new Y coordinate where player wants to move
 * @return: 1 if movement is valid (no collision), 0 if collision detected
 * 
 * The player is treated as a square with a specific radius defined by
 * PLAYER_SIZE_RATIO. This function checks all four corners of the player's
 * bounding box to ensure none of them would intersect with walls or doors.
 * 
 * Corner positions checked:
 * - Top-left: (x-radius, y-radius)
 * - Top-right: (x+radius, y-radius)
 * - Bottom-left: (x-radius, y+radius)  
 * - Bottom-right: (x+radius, y+radius)
 */
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
