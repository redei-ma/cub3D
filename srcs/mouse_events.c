/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:47:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:11:39 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Rotates the player based on mouse movement
 * 
 * @param data: main game structure
 * @param delta_x: horizontal mouse movement (positive = right, negative = left)
 * 
 * This function implements mouse-look functionality with smooth rotation:
 * 1. Scales mouse movement by sensitivity factor (R_SPEED / 10.0)
 * 2. Accumulates small movements to prevent jittery rotation
 * 3. Only applies rotation when accumulated movement exceeds threshold
 * 4. Handles angle wrapping to keep angle within [0, 2π] range
 * 
 * The accumulator system ensures smooth rotation even with small mouse
 * movements and prevents the player from spinning too quickly.
 */
void	rotate_player_mouse(t_data *data, int delta_x)
{
	const double	mouse_sensitivity = R_SPEED / 10.0;

	data->game->mouse_accumulator += delta_x * mouse_sensitivity;
	if (fabs(data->game->mouse_accumulator) > 0.005)
	{
		data->player->angle += data->game->mouse_accumulator;
		data->game->mouse_accumulator = 0;
		if (data->player->angle >= 2 * M_PI)
			data->player->angle -= 2 * M_PI;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

/**
 * Handles mouse movement events for camera control
 * 
 * @param x: current mouse X coordinate
 * @param y: current mouse Y coordinate (unused)
 * @param data: main game structure
 * @return: always returns 0
 * 
 * This function implements mouse-look camera control:
 * 1. Checks if mouse control is enabled
 * 2. Calculates horizontal movement from screen center
 * 3. Applies rotation based on mouse movement
 * 4. Recenters mouse cursor to prevent cursor drift
 * 
 * The mouse is kept at screen center to provide unlimited rotation
 * without the cursor hitting screen edges. Only horizontal movement
 * is used for rotation (vertical movement is ignored).
 */
int	mouse_hook(int x, int y, t_data *data)
{
	const int	center_x = WIN_WIDTH / 2;
	const int	center_y = WIN_HEIGHT / 2;
	int			delta_x;

	(void)y;
	if (!data->game->mouse_enabled)
		return (0);
	delta_x = x - center_x;
	if (abs(delta_x) > 1)
	{
		rotate_player_mouse(data, delta_x);
		mlx_mouse_move(data->game->mlx, data->game->win, center_x, center_y);
	}
	return (0);
}
