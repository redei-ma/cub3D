/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:10:02 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:07:19 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Draws a single tile on the minimap with the specified color
 * 
 * @param data: main game structure
 * @param start_x: starting X coordinate of the tile
 * @param start_y: starting Y coordinate of the tile
 * @param color: color to fill the tile with
 * 
 * This function fills a rectangular area representing one map tile
 * on the minimap. The tile size is determined by the minimap's
 * tile_size_x and tile_size_y values, which scale the world map
 * to fit the minimap display area.
 */
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

/**
 * Renders the complete minimap by drawing all map tiles
 * 
 * @param data: main game structure containing map and minimap data
 * 
 * This function creates a top-down view of the game map in the corner
 * of the screen. It iterates through each cell of the game map and
 * draws a colored tile representing that cell type:
 * 
 * - '1': Wall (white - 0xFFFFFF)
 * - 'D': Closed door (dark green - 0x485121)
 * - ' ': Empty space (no drawing - transparent)
 * - Other: Walkable space (light gray - 0xC0C0C0)
 * 
 * The minimap provides spatial awareness and helps with navigation.
 */
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
