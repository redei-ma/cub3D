/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:04:29 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:03:22 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MIN_DIST 1.5f	// Minimum distance for door interaction
#define MAX_DIST 3.0f	// Maximum distance for door interaction
#define STEP 0.1f		// Step size for scanning positions

/**
 * Checks if a position is within the valid map boundaries
 * 
 * @param data: main game structure containing the map
 * @param check_x: X coordinate to validate
 * @param check_y: Y coordinate to validate
 * @return: 1 if position is valid, 0 if out of bounds
 * 
 * This function performs boundary checks to ensure the coordinates
 * are within the map limits before accessing the map array.
 */
static int	is_position_valid(t_data *data, int check_x, int check_y)
{
	if (check_x < 0 || check_y < 0)
		return (0);
	if (check_y >= ft_countlines((const char **)data->map))
		return (0);
	if (check_x >= (int)ft_strlen(data->map[check_y]))
		return (0);
	return (1);
}

/**
 * Calculates the position in front of the player at a given distance
 * 
 * @param data: main game structure containing player data
 * @param distance: distance from player to calculate position
 * @param check_x: pointer to store the calculated X coordinate
 * @param check_y: pointer to store the calculated Y coordinate
 * 
 * This function uses the player's current position and viewing angle
 * to calculate a point at the specified distance in front of them.
 * Uses trigonometry: x = player_x + cos(angle) * distance
 *                    y = player_y + sin(angle) * distance
 */
static void	calculate_position(t_data *data, float distance,
		int *check_x, int *check_y)
{
	*check_x = (int)(data->player->x + (cos(data->player->angle) * distance));
	*check_y = (int)(data->player->y + (sin(data->player->angle) * distance));
}

/**
 * Searches for doors in front of the player and toggles their state
 * 
 * @param data: main game structure
 * 
 * This function implements door interaction by:
 * 1. Scanning positions in front of the player from MIN_DIST to MAX_DIST
 * 2. Checking each position for doors ('D' = closed, 'O' = open)
 * 3. Toggling the door state when found:
 *    - 'D' (closed) becomes 'O' (open)
 *    - 'O' (open) becomes 'D' (closed)
 * 4. Returning immediately after the first door interaction
 * 
 * The scanning uses small steps (STEP) to ensure doors aren't missed
 * even if they're positioned between grid points.
 */
void	interact_with_door(t_data *data)
{
	float	current_distance;
	int		check_x;
	int		check_y;
	char	cell;

	current_distance = MIN_DIST;
	while (current_distance <= MAX_DIST)
	{
		calculate_position(data, current_distance, &check_x, &check_y);
		if (is_position_valid(data, check_x, check_y))
		{
			cell = data->map[check_y][check_x];
			if (cell == 'D' || cell == 'O')
			{
				if (cell == 'D')
					data->map[check_y][check_x] = 'O';
				else
					data->map[check_y][check_x] = 'D';
				return ;
			}
		}
		current_distance += STEP;
	}
}
