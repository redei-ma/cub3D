/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:55:11 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/07 12:01:34 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Calcola l'altezza della parete sullo schermo
 * Formula: altezza = WIN_HEIGHT / distanza
 */
int	calculate_wall_height(float wall_distance)
{
	return ((int)(WIN_HEIGHT / wall_distance));
}

/**
 * Calcola i punti di inizio e fine per disegnare la parete
 * Centra la parete verticalmente sullo schermo
 */
void	calculate_draw_limits(int wall_height, int *draw_start,
		int *draw_end)
{
	*draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	*draw_end = wall_height / 2 + WIN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

/**
 * Applica la correzione fish-eye
 * Senza questa correzione, i muri ai lati sembrano curvati
 */
float	apply_fisheye_correction(float wall_distance,
		float ray_angle, float player_angle)
{
	return (wall_distance * cos(ray_angle - player_angle));
}

/**
 * Calcola l'angolo per una specifica colonna X
 * Distribuisce il FOV su tutta la larghezza dello schermo
 */
float	calculate_ray_angle(t_data *data, int column_x)
{
	float	angle_step;
	float	start_angle;

	angle_step = FOV_ANGLE / WIN_WIDTH;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	return (start_angle + column_x * angle_step);
}
