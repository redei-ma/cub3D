/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:13:01 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/01 19:29:23 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_single_line_of_wall_h(t_data *data, int j, float wall_dist)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;

	line_height = (int)(WIN_HEIGHT / wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;

	color = 0xAAAAAA;
	y = draw_start;
	while (y < draw_end)
	{
		put_pixel_to_image(data->game->img, j, y, color);
		y++;
	}
}

void	draw_single_line_of_wall(t_data *data, float angle, int j)
{
	float	wall_dist;
	float	current_x;
	float	current_y;
	float	step_size;
	int		max_j;

	wall_dist = cast_ray_dda_limited(data, data->player->x, data->player->y, angle);
	step_size = 0.02f;
	current_x = data->player->x;
	current_y = data->player->y;
	max_j = j + (WIN_WIDTH / FOV_RAYS);
	while (j < max_j)
	{
		draw_single_line_of_wall_h(data, j, wall_dist);
		j++;
	}
}

void	draw_3d_to_image(t_data *data)
{
	float			start_angle;
	float			angle_step;
	int				i;

	angle_step = FOV_ANGLE / FOV_RAYS;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	i = 0;
	while (i < FOV_RAYS)
	{
		draw_single_line_of_wall(data, start_angle + i * angle_step, i * (WIN_WIDTH / FOV_RAYS));
		i++;
	}
}

void	put_window_black(t_data *data)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	color = 0x000000;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			put_pixel_to_image(data->game->img, i, j, color);
			j++;
		}
		i++;
	}
}
