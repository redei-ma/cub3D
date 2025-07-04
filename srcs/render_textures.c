/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:43:18 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/04 10:49:57 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


// ========== CALCOLO COORDINATE TEXTURE ==========

/**
 * Calcola quale texture usare basandosi sulla direzione del muro
 */
t_texture   *get_texture_index(t_data *data)
{
	if (data->last_dda.side == 1)  // Muro verticale
	{
		if (data->last_dda.ray_dir_y > 0)
			return (&data->elements->north);  // North texture
		else
			return (&data->elements->south);  // South texture
	}
	else  // Muro orizzontale
	{
		if (data->last_dda.ray_dir_x > 0)
			return (&data->elements->west);  // West texture
		else
			return (&data->elements->east);  // East texture
	}
}

/**
 * Calcola la coordinata X sulla texture (0.0 - 1.0)
 */
static float    calculate_wall_x(t_data *data)
{
	float wall_x;
	
	if (data->last_dda.side == 0)  // Muro verticale
		wall_x = data->player->y + data->last_dda.perp_wall_dist * data->last_dda.ray_dir_y;
	else  // Muro orizzontale
		wall_x = data->player->x + data->last_dda.perp_wall_dist * data->last_dda.ray_dir_x;
	
	wall_x -= floor(wall_x);  // Mantieni solo la parte decimale
	return (wall_x);
}

/**
 * Ottiene il colore di un pixel dalla texture
 */
static int  get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char    *pixel;
	
	if (tex_x < 0 || tex_x >= texture->width || 
		tex_y < 0 || tex_y >= texture->height)
		return (0);
	
	pixel = texture->addr + (tex_y * texture->line_length + 
							tex_x * (texture->bits_per_pixel / 8));
	return (*(int*)pixel);
}


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
