/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:10:02 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/08 14:50:07 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_tile_to_image(t_data *data, int start_x,
		int start_y, int color)
{
	int				i;
	int				j;

	j = 0;
	while (j < data->mini.tile_size_y)
	{
		i = 0;
		while (i < data->mini.tile_size_x)
		{
			put_pixel_to_image(data->game->img, start_x + i,
				start_y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_minimap_to_image(t_data *data)
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
				draw_tile_to_image(data, x * data->mini.tile_size_x,
					y * data->mini.tile_size_y, 0xFFFFFF);
			else if (data->map[y][x] == 'D')
				draw_tile_to_image(data, x * data->mini.tile_size_x,
					y * data->mini.tile_size_y, 0x485121);
			else if (data->map[y][x] == ' ')
				;
			else
				draw_tile_to_image(data, x * data->mini.tile_size_x,
					y * data->mini.tile_size_y, 0xC0C0C0);
			x++;
		}
		y++;
	}
}
