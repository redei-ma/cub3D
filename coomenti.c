/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coomenti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:47 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/03 14:52:23 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Initializes the basic parameters of the DDA ray
 * 
 * @param dda: structure containing all data for the DDA algorithm
 * @param start_x: starting X coordinate of the ray (player position)
 * @param start_y: starting Y coordinate of the ray (player position)
 * @param angle: direction angle of the ray in radians
 * 
 * This function sets:
 * - map_x, map_y: grid coordinates (cell) where the ray starts
 * - ray_dir_x, ray_dir_y: ray direction vector (x and y components)
 */
static void	init_dda_ray(t_dda *dda, float start_x, float start_y, float angle)
{
	dda->map_x = (int)start_x;          // Starting X cell (integer part)
	dda->map_y = (int)start_y;          // Starting Y cell (integer part)
	dda->ray_dir_x = cos(angle);        // X component of direction vector
	dda->ray_dir_y = sin(angle);        // Y component of direction vector
}

/**
 * Calculates the distance the ray must travel to completely cross
 * one grid cell in both directions
 * 
 * @param dda: DDA structure containing the ray direction
 * 
 * delta_dist_x: distance to cross one cell horizontally
 * delta_dist_y: distance to cross one cell vertically
 * 
 * If the ray is perfectly horizontal/vertical (direction = 0),
 * uses a very large value (1e30) to avoid division by zero
 */
static void	calc_delta_dist(t_dda *dda)
{
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;       // Perfect vertical ray
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir_x);  // |1/direction_x|
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;       // Perfect horizontal ray
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir_y);  // |1/direction_y|
}

/**
 * Calculates the step direction and initial distance to the
 * next grid boundary for both axes
 * 
 * @param dda: DDA structure
 * @param start_x: initial X position (with decimals)
 * @param start_y: initial Y position (with decimals)
 * 
 * step_x/y: movement direction (+1 or -1)
 * side_dist_x/y: distance from current point to next grid boundary
 */
static void	calc_step_and_side_dist(t_dda *dda, float start_x, float start_y)
{
	if (dda->ray_dir_x < 0)             // Ray going left
	{
		dda->step_x = -1;               // Negative step
		// Distance from current point to left edge of cell
		dda->side_dist_x = (start_x - dda->map_x) * dda->delta_dist_x;
	}
	else                                // Ray going right
	{
		dda->step_x = 1;                // Positive step
		// Distance from current point to right edge of cell
		dda->side_dist_x = (dda->map_x + 1.0 - start_x) * dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)             // Ray going up
	{
		dda->step_y = -1;               // Negative step
		// Distance from current point to top edge of cell
		dda->side_dist_y = (start_y - dda->map_y) * dda->delta_dist_y;
	}
	else                                // Ray going down
	{
		dda->step_y = 1;                // Positive step
		// Distance from current point to bottom edge of cell
		dda->side_dist_y = (dda->map_y + 1.0 - start_y) * dda->delta_dist_y;
	}
}

/**
 * Checks if the specified position in the map is a wall
 * 
 * @param data: main structure containing the map
 * @param map_x: X coordinate in the grid
 * @param map_y: Y coordinate in the grid
 * @return: 1 if it's a wall or out of bounds, 0 otherwise
 * 
 * Also checks map boundaries to avoid illegal memory access
 */
static int	is_wall_hit(t_data *data, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)         // Out of bounds (left/top)
		return (1);
	if (map_y >= ft_countlines((const char **)data->map))  // Below map
		return (1);
	if (map_x >= (int)ft_strlen(data->map[map_y]))  // Right of row
		return (1);
	return (data->map[map_y][map_x] == '1');  // Check if it's a wall ('1')
}

/**
 * Performs a single step of the DDA algorithm
 * 
 * @param dda: DDA structure
 * 
 * Compares distances to next horizontal and vertical boundaries,
 * chooses the closest one, advances in that direction and updates values.
 * 
 * side: 0 = hit vertical wall, 1 = hit horizontal wall
 */
static void	perform_dda_step(t_dda *dda)
{
	if (dda->side_dist_x < dda->side_dist_y)  // Vertical boundary is closer
	{
		dda->side_dist_x += dda->delta_dist_x;  // Advance to next vertical line
		dda->map_x += dda->step_x;              // Change X cell
		dda->side = 0;                          // Vertical wall
	}
	else                                        // Horizontal boundary is closer
	{
		dda->side_dist_y += dda->delta_dist_y;  // Advance to next horizontal line
		dda->map_y += dda->step_y;              // Change Y cell
		dda->side = 1;                          // Horizontal wall
	}
}

/**
 * Main function to cast a ray using the DDA algorithm
 * 
 * @param data: main game structure
 * @param start_x: starting X coordinate
 * @param start_y: starting Y coordinate
 * @param angle: ray angle in radians
 * @return: distance from starting point to first wall hit
 * 
 * Implements the complete DDA algorithm:
 * 1. Initialize the ray
 * 2. Calculate DDA parameters
 * 3. Perform steps until hitting a wall
 * 4. Calculate final distance
 */
float	cast_ray_dda(t_data *data, float start_x, float start_y, float angle)
{
	t_dda	dda;
	int		hit;
	float	distance;

	// Phase 1: Initialization
	init_dda_ray(&dda, start_x, start_y, angle);
	calc_delta_dist(&dda);
	calc_step_and_side_dist(&dda, start_x, start_y);
	
	// Phase 2: Main DDA loop
	hit = 0;
	while (!hit)
	{
		perform_dda_step(&dda);                           // Advance one step
		hit = is_wall_hit(data, dda.map_x, dda.map_y);   // Check if hit a wall
		
		// Phase 3: Calculate current distance
		if (dda.side == 0)  // Vertical wall
			distance = (dda.map_x - start_x + (1 - dda.step_x) / 2) / dda.ray_dir_x;
		else                // Horizontal wall
			distance = (dda.map_y - start_y + (1 - dda.step_y) / 2) / dda.ray_dir_y;
	}
	
	// Save DDA data for later use (e.g., texturing)
	data->last_dda = dda;
	return (distance);
}

/**
 * Checks if the player can move to a specific position
 * without colliding with walls
 * 
 * @param data: main game structure
 * @param x: new X coordinate of the player
 * @param y: new Y coordinate of the player
 * @return: 1 if can move, 0 if there's collision
 * 
 * Simulates the player as a square with a certain radius and checks
 * all 4 corners to verify they don't cross through walls
 */
int	check_player_collision(t_data *data, float x, float y)
{
	float	radius;
	int		check_x;
	int		check_y;

	radius = 1.0f / PLAYER_SIZE_RATIO;  // Radius of the player "square"
	
	// Check the 4 corners of the player (simulated as a square)
	
	// Top-left corner
	check_x = (int)(x - radius);
	check_y = (int)(y - radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);  // Collision!
	
	// Top-right corner
	check_x = (int)(x + radius);
	check_y = (int)(y - radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);  // Collision!
	
	// Bottom-left corner
	check_x = (int)(x - radius);
	check_y = (int)(y + radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);  // Collision!
	
	// Bottom-right corner
	check_x = (int)(x + radius);
	check_y = (int)(y + radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);  // Collision!
	
	return (1);  // No collision, valid movement
}

/**
 * Draws a single ray on the minimap for debugging/visualization
 * 
 * @param data: main game structure
 * @param angle: angle of the ray to draw
 * @param mini: minimap parameters (scale, dimensions)
 * 
 * Casts a ray, calculates distance to wall and draws a red line
 * on the minimap to visualize the ray's path.
 * 
 * Note: There's commented code for 3D wall rendering
 */
void	draw_single_ray(t_data *data, float angle, t_minimap mini)
{
	float	wall_dist;
	float	current_x;
	float	current_y;
	float	step_size;
	int		i;

	// Cast ray to get distance to wall
	wall_dist = cast_ray_dda(data, data->player->x, data->player->y, angle);
	
	// Parameters for drawing the ray on minimap
	step_size = 0.02f;                    // Step size for drawing
	current_x = data->player->x;          // Start from player position
	current_y = data->player->y;
	i = 0;
	
	/* COMMENTED CODE: 3D Wall Rendering
	static int j;
	int max_j = j + (WIN_WIDTH / 90);
	while (j < max_j)
	{
		int line_height = (int)(WIN_HEIGHT / wall_dist);        // Wall height
		int draw_start = -line_height / 2 + WIN_HEIGHT / 2;     // Start drawing
		int draw_end = line_height / 2 + WIN_HEIGHT / 2;        // End drawing

		if (draw_start < 0) draw_start = 0;                     // Clamp to limits
		if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

		int color = 0xAAAAAA;                                   // Gray color

		for (int y = draw_start; y < draw_end; y++)
			put_pixel_to_image(data->game->img, j, y, color);   // Draw column
		j++;
	} */
	
	// Draw the ray on the minimap
	while (i < (int)(wall_dist / step_size))
	{
		// Put a red pixel for each step of the ray
		put_pixel_to_image(data->game->img,
			(int)(current_x * mini.tile_size_x),    // Scale X for minimap
			(int)(current_y * mini.tile_size_y),    // Scale Y for minimap
			0xFF0000);                              // Red color
		
		// Advance along the ray
		current_x += cos(angle) * step_size;
		current_y += sin(angle) * step_size;
		i++;
	}
}