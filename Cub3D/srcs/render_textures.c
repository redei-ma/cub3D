/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:43:18 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/07 14:08:25 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Calcola la coordinata X sulla texture in pixel
 */
static int	calculate_texture_x(t_data *data, t_texture *texture)
{
	float	wall_x;

	wall_x = calculate_wall_x(data);
	return ((int)(wall_x * texture->width));
}

/**
 * Calcola lo step per la coordinata Y della texture
 */
static float	calculate_texture_step(t_texture *texture, int wall_height)
{
	return ((float)texture->height / wall_height);
}

/**
 * Calcola la posizione iniziale Y sulla texture
 */
static float	calculate_initial_tex_pos(int wall_start, int wall_height,
	float step)
{
	return ((wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step);
}

/**
 * Disegna una colonna di muro con texture
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
