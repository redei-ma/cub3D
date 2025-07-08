/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:13:26 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/08 14:49:59 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel_to_image(t_image img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	draw_player_to_image(t_data *data, int center_x,
		int center_y, int color)
{
	float	world_radius;
	int		radius;
	int		i;
	int		j;

	world_radius = 1.0f / PLAYER_SIZE_RATIO;
	radius = (int)(world_radius * data->mini.tile_size_x);
	j = -radius;
	while (j <= radius)
	{
		i = -radius;
		while (i <= radius)
		{
			if (i * i + j * j <= radius * radius)
				put_pixel_to_image(data->game->img, center_x + i,
					center_y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_single_ray(t_data *data, float angle, t_minimap mini)
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

static void	draw_fov_to_image(t_data *data)
{
	float			start_angle;
	float			angle_step;
	int				i;

	angle_step = FOV_ANGLE / WIN_WIDTH;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_single_ray(data, start_angle + i * angle_step, data->mini);
		i++;
	}
}

void	draw_image(t_data *data)
{
	draw_3d_to_image(data);
	draw_minimap_to_image(data);
	draw_player_to_image(data, data->player->x * data->mini.tile_size_x,
		data->player->y * data->mini.tile_size_y, 0x00FF00);
	draw_fov_to_image(data);
	mlx_put_image_to_window(data->game->mlx, data->game->win,
		data->game->img.img, 0, 0);
}
