/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:13:26 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:08:38 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define FOV_RAY 500		// Number of rays to cast for field of view visualization

/**
 * Puts a pixel with the specified color at the given coordinates
 * 
 * @param img: image structure containing the pixel buffer
 * @param x: X coordinate of the pixel
 * @param y: Y coordinate of the pixel
 * @param color: color value to set (RGB format)
 * 
 * This function safely writes a pixel to the image buffer with bounds checking.
 * It calculates the exact memory address based on the image's line length
 * and bits per pixel, then writes the color value to that location.
 */
void	put_pixel_to_image(t_image img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/**
 * Draws the player as a filled circle on the minimap
 * 
 * @param data: main game structure
 * @param center_x: X coordinate of player center on minimap
 * @param center_y: Y coordinate of player center on minimap
 * @param color: color to draw the player with
 * 
 * This function renders the player as a circular representation on the minimap.
 * It calculates the world radius based on PLAYER_SIZE_RATIO and scales it
 * to the minimap dimensions. Uses a circle drawing algorithm to fill all
 * pixels within the circular radius.
 */
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

/**
 * Draws a single ray on the minimap for visualization
 * 
 * @param data: main game structure
 * @param angle: angle of the ray to draw
 * @param mini: minimap parameters for scaling
 * 
 * This function visualizes a single ray by:
 * 1. Casting the ray using DDA to find wall distance
 * 2. Drawing red pixels along the ray's path from player to wall
 * 3. Using small steps to ensure continuous line appearance
 * 
 * The ray is drawn in minimap coordinates by scaling world coordinates
 * with the minimap tile sizes.
 */
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

/**
 * Draws the player's field of view on the minimap
 * 
 * @param data: main game structure
 * 
 * This function visualizes the player's field of view by drawing multiple rays
 * spanning the entire FOV_ANGLE. It divides the FOV into FOV_RAY segments
 * and draws a ray for each segment, creating a fan-like visualization
 * that shows what the player can see.
 */
static void	draw_fov_to_image(t_data *data)
{
	float			start_angle;
	float			angle_step;
	int				i;

	angle_step = FOV_ANGLE / FOV_RAY;
	start_angle = data->player->angle - FOV_ANGLE / 2;
	i = 0;
	while (i < FOV_RAY)
	{
		draw_single_ray(data, start_angle + i * angle_step, data->mini);
		i++;
	}
}

/**
 * Main drawing function that renders the complete game frame
 * 
 * @param data: main game structure
 * 
 * This function orchestrates the rendering of the entire game frame:
 * 1. Draws the 3D view (walls, ceiling, floor)
 * 2. Draws the minimap overlay
 * 3. Draws the player representation on the minimap
 * 4. Draws the field of view visualization
 * 5. Presents the final image to the screen
 * 
 * The order of drawing is important as later elements will overlay
 * earlier ones (e.g., player appears on top of minimap).
 */
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
