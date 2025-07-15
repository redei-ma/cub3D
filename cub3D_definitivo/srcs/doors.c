/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:04:29 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/09 12:27:44 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MIN_DIST 1.5f
#define MAX_DIST 3.0f
#define STEP 0.1f

// Checks if a position is within map boundaries
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

// Calculates position in front of player at given distance
static void	calculate_position(t_data *data, float distance,
		int *check_x, int *check_y)
{
	*check_x = (int)(data->player->x + (cos(data->player->angle) * distance));
	*check_y = (int)(data->player->y + (sin(data->player->angle) * distance));
}

// Searches for doors in front of the player within interaction range 
// and toggles their state
// Scans from MIN_DIST to MAX_DIST in small steps, checking each
// position for doors
// Converts 'D' (closed) to 'O' (open) and vice versa when found
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
