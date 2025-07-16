/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:43:41 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/16 11:10:52 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Frees all loaded texture resources from memory
 * 
 * @param data: main game structure containing texture data
 * 
 * This function safely destroys all texture images that were loaded
 * by the MLX library. It performs null checks before attempting to
 * destroy each texture to prevent crashes from accessing freed memory.
 * 
 * This function should be called during cleanup to prevent memory leaks.
 */
void	free_all_textures(t_data *data)
{
	if (data->elements->north1.img)
		mlx_destroy_image(data->game->mlx, data->elements->north1.img);
	if (data->elements->north2.img)
		mlx_destroy_image(data->game->mlx, data->elements->north2.img);
	if (data->elements->south.img)
		mlx_destroy_image(data->game->mlx, data->elements->south.img);
	if (data->elements->west.img)
		mlx_destroy_image(data->game->mlx, data->elements->west.img);
	if (data->elements->east.img)
		mlx_destroy_image(data->game->mlx, data->elements->east.img);
	if (data->elements->door.img)
		mlx_destroy_image(data->game->mlx, data->elements->door.img);
}

/**
 * Loads a single texture file into a texture structure
 * 
 * @param data: main game structure containing MLX context
 * @param tex: texture structure to populate with loaded data
 * @param path: file path to the XPM texture image
 * @return: 1 on success, 0 on failure
 * 
 * This function loads an XPM texture file and sets up all necessary
 * parameters for efficient texture mapping during rendering.
 * 
 * The addr pointer is crucial for fast pixel access during rendering,
 * allowing direct memory reads instead of slower MLX pixel functions.
 * 
 * If any step fails, the function cleans up partial resources and returns 0.
 */
int	load_single_texture_file(t_data *data, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(data->game->mlx, tex->img);
		tex->img = NULL;
		return (0);
	}
	return (1);
}

/**
 * Initializes all texture files required for the game
 * 
 * @param data: main game structure containing elements and MLX context
 * @return: 1 on success, 0 if any texture fails to load
 * 
 * This function loads all textures used in the game rendering system.
 * It sets north_curr to north1 as the default starting texture for animation.
 * 
 * The animation system will alternate between north1 and north2 to create
 * dynamic effects like flickering torches.
 * 
 * If any texture fails to load, the function immediately returns 0.
 */
int	init_all_texture_files(t_data *data)
{
	if (!load_single_texture_file(data, &data->elements->north1,
			data->elements->north_texture1))
		return (0);
	if (!load_single_texture_file(data, &data->elements->north2,
			"./images/torch_2.xpm"))
		return (0);
	if (!load_single_texture_file(data, &data->elements->south,
			data->elements->south_texture))
		return (0);
	if (!load_single_texture_file(data, &data->elements->west,
			data->elements->west_texture))
		return (0);
	if (!load_single_texture_file(data, &data->elements->east,
			data->elements->east_texture))
		return (0);
	if (!load_single_texture_file(data, &data->elements->door,
			"./images/door.xpm"))
		return (0);
	data->elements->north_curr = data->elements->north1;
	return (1);
}
