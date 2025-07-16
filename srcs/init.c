/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:15:44 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:10:13 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Initializes the minimap structure with calculated dimensions
 * 
 * @param map: 2D array representing the game map
 * @return: initialized minimap structure
 * 
 * This function calculates the minimap parameters based on the map size
 * and screen dimensions. The minimap is sized to be 20% of the screen
 * width and height, positioned in the corner for easy reference.
 * 
 * Calculations:
 * - Map dimensions: determined from the map array
 * - Minimap size: 20% of screen dimensions
 * - Tile size: minimap size divided by map dimensions
 * 
 * The tile size determines how many pixels each map cell occupies
 * on the minimap display.
 */
static t_minimap	init_minimap(char **map)
{
	t_minimap	mini;

	mini.map_width = ft_strlen(map[0]);
	mini.map_height = ft_countlines((const char **)map);
	mini.minimap_width = WIN_WIDTH * 0.2;
	mini.minimap_height = WIN_HEIGHT * 0.2;
	mini.tile_size_x = mini.minimap_width / mini.map_width;
	mini.tile_size_y = mini.minimap_height / mini.map_height;
	return (mini);
}

/**
 * Initializes the main game data structure
 * 
 * @param data: main game structure to initialize
 * @param player: player structure with position and angle
 * @param elements: basic game elements (map, textures, colors)
 * 
 * This function sets up the main game data structure by:
 * 1. Linking the player and elements structures
 * 2. Adjusting player position to center of starting cell
 * 3. Setting up the map reference
 * 4. Initializing the minimap parameters
 * 
 * The +0.5 offset centers the player in their starting grid cell
 * rather than placing them at the corner.
 */
void	init_data(t_data *data, t_player *player, t_basic_elements *elements)
{
	data->player = player;
	data->player->x += 0.5;
	data->player->y += 0.5;
	data->map = elements->map;
	data->elements = elements;
	data->mini = init_minimap(data->map);
}

/**
 * Initializes the MLX image structure
 * 
 * @param game: game structure containing MLX data
 * @return: 1 on success, 0 on failure
 * 
 * This function creates the main image buffer for rendering and
 * obtains the necessary parameters for pixel manipulation:
 * - img: pointer to the image buffer
 * - addr: memory address of the image data
 * - bits_per_pixel: color depth information
 * - line_length: bytes per screen line
 * - endian: byte order information
 * 
 * If image creation fails, it cleans up previously allocated resources.
 */
static int	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
		free(game);
		return (0);
	}
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	return (1);
}

/**
 * Initializes the complete game structure and MLX environment
 * 
 * @return: pointer to initialized game structure, NULL on failure
 * 
 * This function sets up the complete MLX environment:
 * 1. Allocates memory for the game structure
 * 2. Initializes the MLX library
 * 3. Creates the game window
 * 4. Sets up the image buffer
 * 5. Initializes input tracking arrays
 * 6. Sets default values for game state
 * 
 * Each step includes error checking and cleanup on failure.
 * The keys_pressed array tracks which movement keys are held down.
 */
t_game	*init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free(game);
		return (NULL);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!game->win)
	{
		free(game->mlx);
		free(game);
		return (NULL);
	}
	if (!init_image(game))
		return (NULL);
	ft_memset(game->keys_pressed, 0, sizeof(game->keys_pressed));
	game->animation_frame = 0;
	game->mouse_enabled = 0;
	return (game);
}
