/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:47 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/08 10:32:35 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_dda_ray(t_dda *dda, float start_x, float start_y, float angle)
{
	dda->map_x = (int)start_x;
	dda->map_y = (int)start_y;
	dda->ray_dir_x = cos(angle);
	dda->ray_dir_y = sin(angle);
}

static void	calc_delta_dist(t_dda *dda)
{
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir_y);
}

static void	calc_step_and_side_dist(t_dda *dda, float start_x, float start_y)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (start_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - start_x) * dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (start_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - start_y) * dda->delta_dist_y;
	}
}

static void	perform_dda_step(t_dda *dda)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

float	cast_ray_dda(t_data *data, float start_x, float start_y, float angle)
{
	t_dda	dda;
	int		hit;
	float	distance;

	init_dda_ray(&dda, start_x, start_y, angle);
	calc_delta_dist(&dda);
	calc_step_and_side_dist(&dda, start_x, start_y);
	hit = 0;
	while (!hit)
	{
		perform_dda_step(&dda);
		hit = is_wall_hit(data, dda.map_x, dda.map_y);
	}
	if (dda.side == 0)
		dda.perp_wall_dist = (dda.map_x - start_x + (1 - dda.step_x) / 2)
			/ dda.ray_dir_x;
	else
		dda.perp_wall_dist = (dda.map_y - start_y + (1 - dda.step_y) / 2)
			/ dda.ray_dir_y;
	distance = dda.perp_wall_dist;
	data->last_dda = dda;
	return (distance);
}
