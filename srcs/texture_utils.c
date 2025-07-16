/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:52:56 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:14:27 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Calculates the exact X coordinate on the wall where the ray hit
 * 
 * @param data: main game structure containing DDA results and player position
 * @return: fractional position along the wall (0.0 to 1.0)
 * 
 * This function determines where exactly along a wall the ray intersected.
 * The calculation depends on which side of the wall was hit:
 * 
 * - side = 0 (vertical wall): Uses Y position calculation
 *   wall_x = player_y + (distance * ray_direction_y)
 * - side = 1 (horizontal wall): Uses X position calculation
 *   wall_x = player_x + (distance * ray_direction_x)
 * 
 * The result is the fractional part (0.0 to 1.0) representing the position
 * along the wall, which is used for texture mapping.
 */
float	calculate_wall_x(t_data *data)
{
	float	wall_x;

	if (data->last_dda.side == 0)
		wall_x = data->player->y
			+ (data->last_dda.perp_wall_dist * data->last_dda.ray_dir_y);
	else
		wall_x = data->player->x
			+ (data->last_dda.perp_wall_dist * data->last_dda.ray_dir_x);
	wall_x -= floor(wall_x);
	return (wall_x);
}

/**
 * Retrieves the color of a specific pixel from a texture
 * 
 * @param texture: texture structure containing image data
 * @param tex_x: X coordinate of the pixel in the texture
 * @param tex_y: Y coordinate of the pixel in the texture
 * @return: color value of the pixel, or 0 if coordinates are invalid
 * 
 * This function performs safe pixel access from texture memory:
 * 1. Validates that coordinates are within texture bounds
 * 2. Calculates the memory address of the pixel
 * 3. Reads the color value from memory
 * 
 * The memory address calculation uses the texture's line length and
 * bits per pixel to correctly locate the pixel in the linear memory buffer.
 */
int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0);
	pixel = texture->addr + (tex_y * texture->line_length
			+ tex_x * (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

/**
 * Determines which texture to use based on wall type and ray direction
 * 
 * @param data: main game structure containing DDA results and map data
 * @return: pointer to the appropriate texture structure
 * 
 * This function selects the correct texture for rendering based on:
 * 1. Wall type (door vs regular wall)
 * 2. Wall orientation (vertical vs horizontal)
 * 3. Ray direction (determines which side of the wall was hit)
 * 
 * Texture selection logic:
 * - DOOR_CLOSED ('D'): Always uses door texture
 * - Horizontal walls (side = 1):
 *   - Ray going down (ray_dir_y > 0): North texture (animated)
 *   - Ray going up (ray_dir_y < 0): South texture
 * - Vertical walls (side = 0):
 *   - Ray going right (ray_dir_x > 0): West texture
 *   - Ray going left (ray_dir_x < 0): East texture
 * 
 * The north texture uses north_curr which alternates between north1 and north2
 * for animation effects.
 */
t_texture	*get_texture_index(t_data *data)
{
	const int	map_x = data->last_dda.map_x;
	const int	map_y = data->last_dda.map_y;

	if (data->map[map_y][map_x] == DOOR_CLOSED)
		return (&data->elements->door);
	if (data->last_dda.side == 1)
	{
		if (data->last_dda.ray_dir_y > 0)
			return (&data->elements->north_curr);
		else
			return (&data->elements->south);
	}
	else
	{
		if (data->last_dda.ray_dir_x > 0)
			return (&data->elements->west);
		else
			return (&data->elements->east);
	}
}
