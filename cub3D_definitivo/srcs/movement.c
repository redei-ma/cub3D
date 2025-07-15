/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:08:40 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/09 12:15:39 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Applies movement if collision check passes, with wall sliding
static void	apply_safe_movement(t_data *data, float delta_x, float delta_y)
{
	float	new_x;
	float	new_y;

	new_x = data->player->x + delta_x;
	new_y = data->player->y + delta_y;
	if (check_player_collision(data, new_x, new_y))
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
	else if (check_player_collision(data, new_x, data->player->y))
		data->player->x = new_x;
	else if (check_player_collision(data, data->player->x, new_y))
		data->player->y = new_y;
}

// Calculates Y movement component based on player angle and direction
// Uses sine for Y-axis movement in the coordinate system
static float	calc_movement_y(t_player *player, int direction)
{
	if (direction == FORWARD)
		return (sin(player->angle) * SPEED);
	if (direction == BACKWARD)
		return (-sin(player->angle) * SPEED);
	if (direction == STRAFE_LEFT)
		return (sin(player->angle - M_PI / 2) * SPEED);
	if (direction == STRAFE_RIGHT)
		return (sin(player->angle + M_PI / 2) * SPEED);
	return (0);
}

// Calculates X movement component based on player angle and direction
// Uses cosine for X-axis movement in the coordinate system
static float	calc_movement_x(t_player *player, int direction)
{
	if (direction == FORWARD)
		return (cos(player->angle) * SPEED);
	if (direction == BACKWARD)
		return (-cos(player->angle) * SPEED);
	if (direction == STRAFE_LEFT)
		return (cos(player->angle - M_PI / 2) * SPEED);
	if (direction == STRAFE_RIGHT)
		return (cos(player->angle + M_PI / 2) * SPEED);
	return (0);
}

// Handles player movement with collision detection in specified direction
void	move_player(t_data *data, t_player *player, int direction)
{
	float	delta_x;
	float	delta_y;

	delta_x = calc_movement_x(player, direction);
	delta_y = calc_movement_y(player, direction);
	apply_safe_movement(data, delta_x, delta_y);
}

// Rotates player left or right and handles angle wrapping
void	rotate_player(t_data *data, int direction)
{
	if (direction == ROTATE_LEFT)
	{
		data->player->angle -= R_SPEED;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
	else if (direction == ROTATE_RIGHT)
	{
		data->player->angle += R_SPEED;
		if (data->player->angle >= 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
}
