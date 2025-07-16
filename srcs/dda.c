/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:47 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:01:03 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Initializes the basic parameters for the DDA ray casting algorithm
 * 
 * @param dda: DDA structure to initialize
 * @param start_x: starting X coordinate of the ray (player position)
 * @param start_y: starting Y coordinate of the ray (player position)
 * @param angle: direction angle of the ray in radians
 * 
 * This function sets up the initial ray parameters:
 * - map_x, map_y: current grid cell coordinates (integer parts of position)
 * - ray_dir_x, ray_dir_y: normalized direction vector components
 */
static void	init_dda_ray(t_dda *dda, float start_x, float start_y, float angle)
{
	dda->map_x = (int)start_x;
	dda->map_y = (int)start_y;
	dda->ray_dir_x = cos(angle);
	dda->ray_dir_y = sin(angle);
}

/**
 * Calculates the distance the ray travels for each unit step in X and Y directions
 * 
 * @param dda: DDA structure containing ray direction
 * 
 * This function computes delta_dist_x and delta_dist_y, which represent
 * how far the ray travels along its direction when moving exactly one grid unit.
 * 
 * For perfectly horizontal/vertical rays (direction = 0), uses a very large
 * value (1e30) to effectively represent infinity and avoid division by zero.
 */
static void	calc_delta_dist(t_dda *dda)
{
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir_y);
}

/**
 * Calculates step direction and initial distances to the next grid boundaries
 * 
 * @param dda: DDA structure to populate
 * @param start_x: exact starting X position (with decimals)
 * @param start_y: exact starting Y position (with decimals)
 * 
 * This function determines:
 * - step_x/y: which direction to move in the grid (+1 or -1)
 * - side_dist_x/y: distance from current position to next grid boundary
 * 
 * The side distances are calculated differently based on ray direction:
 * - For negative directions: distance to the "near" edge of current cell
 * - For positive directions: distance to the "far" edge of current cell
 */
static void	calc_step_and_side_dist(t_dda *dda, float start_x, float start_y)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (start_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - start_x) * dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (start_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - start_y) * dda->delta_dist_y;
	}
}

/**
 * Performs one step of the DDA algorithm
 * 
 * @param dda: DDA structure to update
 * 
 * This function implements the core DDA stepping logic:
 * 1. Compare distances to next vertical and horizontal grid boundaries
 * 2. Choose the closest boundary (smallest distance)
 * 3. Move to that boundary and update position
 * 4. Update the side flag to track which type of boundary was crossed
 * 
 * The side flag is crucial for texture mapping:
 * - side = 0: hit a vertical wall (NS wall)
 * - side = 1: hit a horizontal wall (EW wall)
 */
static void	perform_dda_step(t_dda *dda)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

/**
 * Main DDA raycasting function that finds the distance to the nearest wall
 * 
 * @param data: main game structure containing the map
 * @param start_x: ray starting X coordinate
 * @param start_y: ray starting Y coordinate
 * @param angle: ray direction angle in radians
 * @return: perpendicular distance from ray origin to the hit wall
 * 
 * This function implements the complete DDA algorithm:
 * 1. Initialize ray parameters
 * 2. Calculate delta distances and step directions
 * 3. Perform DDA steps until hitting a wall
 * 4. Calculate the perpendicular wall distance (prevents fisheye effect)
 * 5. Store DDA results for texture mapping
 * 
 * The perpendicular distance calculation ensures that walls appear straight
 * rather than curved, which would happen if we used the actual ray length.
 */
float	cast_ray_dda(t_data *data, float start_x, float start_y, float angle)
{
	t_dda	dda;
	int		hit;
	float	distance;

	init_dda_ray(&dda, start_x, start_y, angle);
	calc_delta_dist(&dda);
	calc_step_and_side_dist(&dda, start_x, start_y);
	hit = 0;
	while (!hit)
	{
		perform_dda_step(&dda);
		hit = is_wall_hit(data, dda.map_x, dda.map_y);
	}
	if (dda.side == 0)
		dda.perp_wall_dist = (dda.map_x - start_x + (1 - dda.step_x) / 2)
			/ dda.ray_dir_x;
	else
		dda.perp_wall_dist = (dda.map_y - start_y + (1 - dda.step_y) / 2)
			/ dda.ray_dir_y;
	distance = dda.perp_wall_dist;
	data->last_dda = dda;
	return (distance);
}
