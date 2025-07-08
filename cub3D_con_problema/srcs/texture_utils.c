/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:52:56 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/08 14:26:06 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * Calcola la coordinata X sulla texture (0.0 - 1.0)
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

/*
 * Ottiene il colore di un pixel dalla texture
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

/*
 * Calcola quale texture usare basandosi sulla direzione del muro
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
