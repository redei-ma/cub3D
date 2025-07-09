/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:43:18 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/09 12:32:03 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Calculates the X coordinate on texture in pixels based on wall hit position
static int	calculate_texture_x(t_data *data, t_texture *texture)
{
	float	wall_x;

	wall_x = calculate_wall_x(data);
	return ((int)(wall_x * texture->width));
}

// Calculates the step size for texture Y coordinate based on wall height
// Determines how much to advance in texture for each screen pixel
static float	calculate_texture_step(t_texture *texture, int wall_height)
{
	return ((float)texture->height / wall_height);
}

// Calculates the initial Y position on texture for the top of the wall
// Accounts for walls that extend beyond screen boundaries
static float	calculate_initial_tex_pos(int wall_start, int wall_height,
	float step)
{
	return ((wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step);
}

// Draws a textured wall column by mapping texture pixels to screen pixels
// Iterates through each screen Y coordinate and samples the corresponding
// texture pixel
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
