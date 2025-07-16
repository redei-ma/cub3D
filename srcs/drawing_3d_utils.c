/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:55:11 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:06:22 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Calculates the height of a wall on screen based on its distance
 * 
 * @param wall_distance: perpendicular distance from player to wall
 * @return: height of wall in screen pixels
 * 
 * This function implements the perspective projection formula where
 * wall height is inversely proportional to distance. Closer walls
 * appear taller, distant walls appear shorter. The formula used is:
 * wall_height = WIN_HEIGHT / wall_distance
 * 
 * This creates the realistic perspective effect in the 3D view.
 */
int	calculate_wall_height(float wall_distance)
{
	return ((int)(WIN_HEIGHT / wall_distance));
}

/**
 * Calculates the start and end Y coordinates for drawing a wall
 * 
 * @param wall_height: height of the wall in screen pixels
 * @param draw_start: pointer to store the starting Y coordinate
 * @param draw_end: pointer to store the ending Y coordinate
 * 
 * This function centers the wall vertically on the screen by:
 * 1. Calculating the wall's center at screen height / 2
 * 2. Extending half the wall height above and below the center
 * 3. Clamping the coordinates to screen boundaries (0 to WIN_HEIGHT-1)
 * 
 * The clamping prevents drawing outside the screen buffer and handles
 * cases where walls are very close (height > screen height).
 */
void	calculate_draw_limits(int wall_height, int *draw_start,
		int *draw_end)
{
	*draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	*draw_end = wall_height / 2 + WIN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

/**
 * Applies fisheye correction to prevent wall distortion
 * 
 * @param wall_distance: original distance from ray to wall
 * @param ray_angle: angle of the current ray
 * @param player_angle: player's viewing angle
 * @return: corrected distance for rendering
 * 
 * Without this correction, walls would appear curved because rays
 * at the edges of the screen travel longer distances to reach
 * the projection plane. The correction multiplies the distance
 * by cos(angle_difference) to project it onto the perpendicular
 * plane in front of the player.
 * 
 * This is essential for creating straight walls in the 3D view.
 */
float	apply_fisheye_correction(float wall_distance,
		float ray_angle, float player_angle)
{
	return (wall_distance * cos(ray_angle - player_angle));
}

/**
 * Calculates the ray angle for a specific screen column
 * 
 * @param data: main game structure containing player data
 * @param column_x: X coordinate of the screen column (0 to WIN_WIDTH-1)
 * @return: angle of the ray for this column in radians
 * 
 * This function distributes the field of view evenly across all screen columns:
 * 1. Calculates the angle step between adjacent columns
 * 2. Finds the leftmost ray angle (player_angle - FOV_ANGLE/2)
 * 3. Adds the appropriate step offset for the current column
 * 
 * The result is that column 0 gets the leftmost ray, column WIN_WIDTH-1
 * gets the rightmost ray, and all columns in between get evenly spaced
 * angles spanning the full field of view.
 */
float	calculate_ray_angle(t_data *data, int column_x)
{
	float	angle_step;
	float	start_angle;

	angle_step = FOV_ANGLE / WIN_WIDTH;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	return (start_angle + column_x * angle_step);
}
