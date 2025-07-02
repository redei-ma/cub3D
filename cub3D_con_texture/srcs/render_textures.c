/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:43:18 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/02 17:10:13 by ade-ross         ###   ########.fr       */
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

// ========== RENDERING CON TEXTURE ==========

/**
 * Disegna una colonna di muro con texture
 */
void draw_textured_wall_column(t_data *data, int x, int wall_start, 
									 int wall_end, int wall_height)
{
	t_texture   *texture;
	// int         tex_index;
	float       wall_x;
	int         tex_x;
	int         tex_y;
	float       step;
	float       tex_pos;
	int         y;
	int         color;
	
	// 1. Determina quale texture usare
	texture = get_texture_index(data);
	
	// 2. Calcola coordinata X sulla texture
	wall_x = calculate_wall_x(data);
	tex_x = (int)(wall_x * texture->width);
	
	// 3. Calcola step per la coordinata Y
	step = (float)texture->height / wall_height;
	tex_pos = (wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
	
	// 4. Disegna ogni pixel della colonna
	y = wall_start;
	while (y < wall_end)
	{
		tex_y = (int)tex_pos % texture->height;
		tex_pos += step;
		
		color = get_texture_color(texture, tex_x, tex_y);
		put_pixel_to_image(data->game->img, x, y, color);
		y++;
	}
}
