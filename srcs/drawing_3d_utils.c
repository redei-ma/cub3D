/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:55:11 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/09 12:17:25 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Calculates wall height on screen inversely proportional to distance
// Closer walls appear taller, distant walls appear shorter
int	calculate_wall_height(float wall_distance)
{
	return ((int)(WIN_HEIGHT / wall_distance));
}

// Calculates start and end points for drawing the wall vertically centered
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

// Applies fisheye correction to prevent curved wall distortion at screen edges
// Multiplies distance by cosine of angle difference to correct perspective
float	apply_fisheye_correction(float wall_distance,
		float ray_angle, float player_angle)
{
	return (wall_distance * cos(ray_angle - player_angle));
}

// Calculates ray angle for a specific screen column within the field of view
// Distributes the FOV evenly across all screen columns
float	calculate_ray_angle(t_data *data, int column_x)
{
	float	angle_step;
	float	start_angle;

	angle_step = FOV_ANGLE / WIN_WIDTH;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	return (start_angle + column_x * angle_step);
}
