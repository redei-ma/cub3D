/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:13:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:07:00 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Draws the ceiling portion of a vertical screen column
 * 
 * @param data: main game structure containing image and color data
 * @param x: X coordinate of the column to draw
 * @param ceiling_end: Y coordinate where ceiling ends (wall starts)
 * 
 * This function fills the upper portion of a screen column with the ceiling color.
 * It draws from the top of the screen (y=0) down to where the wall begins.
 * The ceiling color is stored in data->elements->ceiling_colour.
 */
static void	draw_ceiling_column(t_data *data, int x, int ceiling_end)
{
	int	y;

	y = 0;
	while (y < ceiling_end)
	{
		put_pixel_to_image(data->game->img, x, y,
			data->elements->ceiling_colour);
		y++;
	}
}

/**
 * Draws the floor portion of a vertical screen column
 * 
 * @param data: main game structure containing image and color data
 * @param x: X coordinate of the column to draw
 * @param floor_start: Y coordinate where floor starts (wall ends)
 * 
 * This function fills the lower portion of a screen column with the floor color.
 * It draws from where the wall ends down to the bottom of the screen.
 * The floor color is stored in data->elements->floor_colour.
 */
static void	draw_floor_column(t_data *data, int x, int floor_start)
{
	int	y;

	y = floor_start;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(data->game->img, x, y, data->elements->floor_colour);
		y++;
	}
}

/**
 * Renders a single vertical column with textured walls
 * 
 * @param data: main game structure
 * @param x: X coordinate of the column to render
 * @param wall_dist: distance from player to wall (corrected for fisheye)
 * 
 * This function renders a complete vertical slice of the 3D view:
 * 1. Calculates wall height based on distance (closer = taller)
 * 2. Determines drawing boundaries (start and end Y coordinates)
 * 3. Draws ceiling from top to wall start
 * 4. Draws textured wall section
 * 5. Draws floor from wall end to bottom
 * 
 * The wall height is inversely proportional to distance, creating
 * the perspective effect where distant walls appear smaller.
 */
static void	render_single_column_textured(t_data *data, int x, float wall_dist)
{
	int	wall_height;
	int	draw_start;
	int	draw_end;
	int	draw_bounds[2];

	wall_height = calculate_wall_height(wall_dist);
	calculate_draw_limits(wall_height, &draw_start, &draw_end);
	draw_ceiling_column(data, x, draw_start);
	draw_bounds[0] = draw_start;
	draw_bounds[1] = draw_end;
	draw_textured_wall_column(data, x, draw_bounds, wall_height);
	draw_floor_column(data, x, draw_end);
}

/**
 * Main 3D rendering function that creates the first-person view
 * 
 * @param data: main game structure
 * 
 * This function implements the core 3D rendering pipeline:
 * 1. Iterates through each horizontal pixel column on the screen
 * 2. Calculates the ray angle for each column within the FOV
 * 3. Casts a ray using DDA to find wall distance
 * 4. Applies fisheye correction to prevent distortion
 * 5. Renders the column with proper wall height and textures
 * 
 * The fisheye correction is crucial because without it, walls would
 * appear curved, especially at the edges of the screen. The correction
 * multiplies the distance by cos(ray_angle - player_angle).
 */
void	draw_3d_to_image(t_data *data)
{
	int		x;
	float	ray_angle;
	float	wall_distance;
	float	corrected_distance;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_angle = calculate_ray_angle(data, x);
		wall_distance = cast_ray_dda(data,
				data->player->x, data->player->y, ray_angle);
		corrected_distance = apply_fisheye_correction(wall_distance,
				ray_angle, data->player->angle);
		render_single_column_textured(data, x, corrected_distance);
		x++;
	}
}
