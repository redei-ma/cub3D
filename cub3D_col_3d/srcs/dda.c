/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:47 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/02 11:19:40 by redei-ma         ###   ########.fr       */
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

static int	is_wall_hit(t_data *data, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= ft_countlines((const char **)data->map))
		return (1);
	if (map_x >= (int)ft_strlen(data->map[map_y]))
		return (1);
	return (data->map[map_y][map_x] == '1');
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
		
		// Calcola distanza corrente
		if (dda.side == 0)
			distance = (dda.map_x - start_x + (1 - dda.step_x) / 2) / dda.ray_dir_x;
		else
			distance = (dda.map_y - start_y + (1 - dda.step_y) / 2) / dda.ray_dir_y;
	}
	data->last_dda = dda;
	return (distance);
}

int	check_player_collision(t_data *data, float x, float y)
{
	float	radius;
	int		check_x;
	int		check_y;

	radius = 1.0f / PLAYER_SIZE_RATIO;  // Stesso rapporto del disegno
	
	// Controlla 4 angoli del giocatore
	check_x = (int)(x - radius);
	check_y = (int)(y - radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	check_x = (int)(x + radius);
	check_y = (int)(y - radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	check_x = (int)(x - radius);
	check_y = (int)(y + radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	check_x = (int)(x + radius);
	check_y = (int)(y + radius);
	if (is_wall_hit(data, check_x, check_y))
		return (0);
	return (1);
}

void	draw_single_ray(t_data *data, float angle, t_minimap mini)
{
	float	wall_dist;
	float	current_x;
	float	current_y;
	float	step_size;
	int		i;

	wall_dist = cast_ray_dda(data, data->player->x, data->player->y, angle);
	step_size = 0.02f;
	current_x = data->player->x;
	current_y = data->player->y;
	i = 0;
	/* static int j;
	int max_j = j + (WIN_WIDTH / 90);
	while (j < max_j)
	{
		int line_height = (int)(WIN_HEIGHT / wall_dist);
		int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		int draw_end = line_height / 2 + WIN_HEIGHT / 2;

		if (draw_start < 0) draw_start = 0;
		if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

		int color = 0xAAAAAA;

		for (int y = draw_start; y < draw_end; y++)
			put_pixel_to_image(data->game->img, j, y, color);
		j++;
	} */
	while (i < (int)(wall_dist / step_size))
	{
		
		put_pixel_to_image(data->game->img,
			(int)(current_x * mini.tile_size_x),
			(int)(current_y * mini.tile_size_y),
			0xFF0000);
		current_x += cos(angle) * step_size;
		current_y += sin(angle) * step_size;
		i++;
	}
}
