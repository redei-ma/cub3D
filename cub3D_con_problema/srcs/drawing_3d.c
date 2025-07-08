/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:13:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/08 10:51:56 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Disegna il soffitto per una colonna
 * Dal top dello schermo fino all'inizio della parete
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
 * Disegna il pavimento per una colonna  
 * Dalla fine della parete al bottom dello schermo
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
 * Versione aggiornata della render_single_column con texture
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
 * Funzione principale che renderizza l'intera vista 3D
 * Lancia un raggio per ogni colonna dello schermo
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
