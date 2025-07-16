/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:43:18 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/16 11:13:30 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Calculates the X coordinate on the texture for the current wall hit
 * 
 * @param data: main game structure containing DDA results
 * @param texture: texture structure containing width information
 * @return: X coordinate on texture (0 to texture_width-1)
 * 
 * This function determines which column of the texture to use based on
 * where exactly the ray hit the wall. It uses the wall_x value (fractional
 * position along the wall) and scales it to the texture width.
 * 
 * The wall_x value represents the position along the wall where the ray
 * intersected, ranging from 0.0 to 1.0, which is then mapped to the
 * texture's pixel coordinates.
 */
static int	calculate_texture_x(t_data *data, t_texture *texture)
{
	float	wall_x;

	wall_x = calculate_wall_x(data);
	return ((int)(wall_x * texture->width));
}

/**
 * Calculates the step size for texture Y coordinate sampling
 * 
 * @param texture: texture structure containing height information
 * @param wall_height: height of the wall on screen in pixels
 * @return: step size for advancing through texture Y coordinates
 * 
 * This function determines how much to advance in the texture's Y coordinate
 * for each screen pixel. When the wall is tall (close), we advance slowly
 * through the texture. When the wall is short (far), we advance quickly.
 * 
 * The formula ensures the entire texture height is mapped to the wall height,
 * creating proper scaling regardless of distance.
 */
static float	calculate_texture_step(t_texture *texture, int wall_height)
{
	return ((float)texture->height / wall_height);
}

/**
 * Calculates the initial Y position on the texture for rendering
 * 
 * @param wall_start: Y coordinate where wall drawing begins on screen
 * @param wall_height: height of the wall on screen in pixels
 * @param step: step size for texture Y coordinate advancement
 * @return: initial texture Y position
 * 
 * This function calculates the starting Y position in the texture for walls
 * that may be partially off-screen. When a wall is very close (tall), its
 * top and bottom may extend beyond the screen boundaries. This function
 * determines which part of the texture corresponds to the visible portion.
 * 
 * The calculation accounts for the wall being centered on screen and
 * adjusts for cases where the wall extends beyond screen boundaries.
 */
static float	calculate_initial_tex_pos(int wall_start, int wall_height,
	float step)
{
	return ((wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step);
}

/**
 * Draws a textured wall column by mapping texture pixels to screen pixels
 * 
 * @param data: main game structure
 * @param x: X coordinate of the screen column to draw
 * @param wall_bounds: array containing [start_y, end_y] for wall drawing
 * @param wall_height: height of the wall on screen in pixels
 * 
 * This function renders a single vertical column of a textured wall:
 * 1. Determines which texture to use based on wall type and direction
 * 2. Calculates the X coordinate on the texture
 * 3. Calculates the step size for Y coordinate advancement
 * 4. Determines the starting Y position on the texture
 * 5. Iterates through each screen pixel and samples the texture
 * 
 * The texture mapping ensures that the texture is properly scaled and
 * positioned on the wall, creating realistic 3D appearance.
 */
void	draw_textured_wall_column(t_data *data, int x, int wall_bounds[2],
	int wall_height)
{
	t_texture	*texture;
	int			tex_x;
	float		step;
	float		tex_pos;
	int			y;

	texture = get_texture_index(data);
	tex_x = calculate_texture_x(data, texture);
	step = calculate_texture_step(texture, wall_height);
	tex_pos = calculate_initial_tex_pos(wall_bounds[0], wall_height, step);
	y = wall_bounds[0];
	while (y < wall_bounds[1])
	{
		put_pixel_to_image(data->game->img, x, y,
			get_texture_color(texture, tex_x, (int)tex_pos % texture->height));
		tex_pos += step;
		y++;
	}
}
