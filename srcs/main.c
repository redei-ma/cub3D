/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:17:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:11:14 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Handles window closing and cleanup of all game resources
 * 
 * @param data: main game structure containing all resources
 * @return: always returns 0
 * 
 * This function performs complete cleanup when the game is closed:
 * 1. Frees all loaded textures
 * 2. Destroys the main image buffer
 * 3. Destroys the game window
 * 4. Destroys the MLX display connection
 * 5. Frees the MLX and game structures
 * 6. Frees the basic elements (map, colors, etc.)
 * 7. Exits the program
 * 
 * The order of cleanup is important to prevent memory leaks and crashes.
 * This function can be called by the window close button or ESC key.
 */
int	close_window(t_data *data)
{
	free_all_textures(data);
	mlx_destroy_image(data->game->mlx, data->game->img.img);
	mlx_destroy_window(data->game->mlx, data->game->win);
	mlx_destroy_display(data->game->mlx);
	free(data->game->mlx);
	free(data->game);
	free_basic_elements(data->elements);
	exit(0);
	return (0);
}

/**
 * Main function - entry point of the cub3D program
 * 
 * @param argc: number of command line arguments
 * @param argv: array of command line arguments
 * @return: 0 on success, 1 on error
 * 
 * This function orchestrates the complete game initialization and execution:
 * 
 * 1. **Parsing Phase**: Validates arguments and parses the .cub file
 *    - Checks command line arguments
 *    - Parses map file and extracts textures, colors, and map layout
 *    - Finds player starting position and orientation
 * 
 * 2. **Initialization Phase**: Sets up the game environment
 *    - Initializes MLX library and creates window
 *    - Sets up game data structures
 *    - Loads all texture files
 * 
 * 3. **Event Setup**: Registers event handlers
 *    - Window close handler (X button)
 *    - Key press/release handlers (movement, actions)
 *    - Mouse movement handler (optional mouse look)
 * 
 * 4. **Game Loop**: Starts the main game loop
 *    - Registers continuous update function
 *    - Enters MLX event loop (blocks until program exit)
 * 
 * Error handling is implemented at each step with appropriate cleanup.
 */
int	main(int argc, char *argv[])
{
	t_data				data;
	t_basic_elements	elements_struct;
	t_player			player;

	if (handle_parsing(argc, argv, &elements_struct, &player) == 0)
		return (1);
	data.game = init_game();
	if (!data.game)
		return (1);
	init_data(&data, &player, &elements_struct);
	if (!init_all_texture_files(&data))
	{
		error("can't load textures", NULL);
		close_window(&data);
		return (1);
	}
	mlx_hook(data.game->win, 17, 0, close_window, &data);
	mlx_hook(data.game->win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.game->win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.game->win, 6, 1L << 6, mouse_hook, &data);
	mlx_loop_hook(data.game->mlx, game_loop, &data);
	mlx_loop(data.game->mlx);
}
