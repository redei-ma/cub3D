/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:08:40 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:12:34 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Applies movement with collision detection and wall sliding
 * 
 * @param data: main game structure
 * @param delta_x: desired change in X position
 * @param delta_y: desired change in Y position
 * 
 * This function implements smart movement with collision detection:
 * 1. First tries to move to the desired position (delta_x, delta_y)
 * 2. If that fails, tries to move only in X direction (wall sliding)
 * 3. If that fails, tries to move only in Y direction (wall sliding)
 * 4. If all fail, no movement occurs
 * 
 * Wall sliding allows the player to move along walls smoothly instead
 * of getting stuck when pressing forward while touching a wall at an angle.
 */
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

/**
 * Calculates Y movement component based on player angle and direction
 * 
 * @param player: player structure containing current angle
 * @param direction: movement direction (FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT)
 * @return: Y movement delta
 * 
 * This function uses trigonometry to calculate the Y component of movement:
 * - FORWARD: move in direction player is facing (sin(angle))
 * - BACKWARD: move opposite to player direction (-sin(angle))
 * - STRAFE_LEFT: move perpendicular left (sin(angle - π/2))
 * - STRAFE_RIGHT: move perpendicular right (sin(angle + π/2))
 * 
 * The sine function gives the Y component of the unit vector in the
 * coordinate system where positive Y is down.
 */
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

/**
 * Calculates X movement component based on player angle and direction
 * 
 * @param player: player structure containing current angle
 * @param direction: movement direction (FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT)
 * @return: X movement delta
 * 
 * This function uses trigonometry to calculate the X component of movement:
 * - FORWARD: move in direction player is facing (cos(angle))
 * - BACKWARD: move opposite to player direction (-cos(angle))
 * - STRAFE_LEFT: move perpendicular left (cos(angle - π/2))
 * - STRAFE_RIGHT: move perpendicular right (cos(angle + π/2))
 * 
 * The cosine function gives the X component of the unit vector in the
 * coordinate system where positive X is right.
 */
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

/**
 * Handles player movement with collision detection
 * 
 * @param data: main game structure
 * @param player: player structure to move
 * @param direction: direction to move (FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT)
 * 
 * This function implements player movement by:
 * 1. Calculating movement deltas based on player angle and direction
 * 2. Applying the movement with collision detection and wall sliding
 * 
 * The movement is relative to the player's current viewing angle,
 * so forward always means "in the direction the player is looking"
 * regardless of the actual angle value.
 */
void	move_player(t_data *data, t_player *player, int direction)
{
	float	delta_x;
	float	delta_y;

	delta_x = calc_movement_x(player, direction);
	delta_y = calc_movement_y(player, direction);
	apply_safe_movement(data, delta_x, delta_y);
}

/**
 * Rotates the player left or right with angle wrapping
 * 
 * @param data: main game structure
 * @param direction: rotation direction (ROTATE_LEFT or ROTATE_RIGHT)
 * 
 * This function handles player rotation by:
 * 1. Adjusting the player angle by R_SPEED radians
 * 2. Wrapping the angle to keep it within [0, 2π] range
 * 
 * Angle wrapping is important to prevent angle values from growing
 * infinitely large, which could cause precision issues or overflow.
 * The angle is kept in the standard mathematical range [0, 2π].
 */
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
