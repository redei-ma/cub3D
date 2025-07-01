/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:13:26 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/01 19:15:17 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel_to_image(t_image img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	draw_fov_to_image(t_data *data)
{
	float			start_angle;
	float			angle_step;
	int				i;

	angle_step = FOV_ANGLE / FOV_RAYS;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	i = 0;
	while (i < FOV_RAYS)
	{
		draw_single_ray(data, start_angle + i * angle_step, data->mini);
		i++;
	}
}

static void	draw_player_to_image(t_data *data, int center_x, int center_y, int color)
{
	int				radius;
	int				i;
	int				j;

	radius = data->mini.tile_size_x / PLAYER_SIZE_RATIO;
	j = -radius;
	while (j <= radius)
	{
		i = -radius;
		while (i <= radius)
		{
			if (i * i + j * j <= radius * radius)
				put_pixel_to_image(data->game->img, center_x + i, center_y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_tile_to_image(t_data *data, int start_x, int start_y, int color)
{
	int				i;
	int				j;

	j = 0;
	while (j < data->mini.tile_size_y)
	{
		i = 0;
		while (i < data->mini.tile_size_x)
		{
			put_pixel_to_image(data->game->img, start_x + i, start_y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_to_image(t_data *data)
{
	int				x;
	int				y;

	y = 0;
	while (y < data->mini.map_height)
	{
		x = 0;
		while (x < data->mini.map_width)
		{
			if (data->map[y][x] == '1')
				draw_tile_to_image(data, x * data->mini.tile_size_x, y * data->mini.tile_size_y, 0xFFFFFF);
			else if (data->map[y][x] == ' ')
				;
			else
				draw_tile_to_image(data, x * data->mini.tile_size_x, y * data->mini.tile_size_y, 0xC0C0C0);
			x++;
		}
		y++;
	}
	draw_player_to_image(data, data->player->x * data->mini.tile_size_x, data->player->y * data->mini.tile_size_y, 0x00FF00);
	// vorrei spostarlo in draw_image
}

void	draw_image(t_data *data)
{
	put_window_black(data);
	draw_3d_to_image(data);
	draw_minimap_to_image(data);
	draw_fov_to_image(data);
	mlx_put_image_to_window(data->game->mlx, data->game->win, data->game->img.img, 0, 0);
}
