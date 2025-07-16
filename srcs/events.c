/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:16:20 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/16 11:09:23 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Handles texture animation for dynamic elements
 * 
 * @param data: main game structure
 * @return: always returns 0
 * 
 * This function manages texture animation by cycling between different
 * texture frames. Currently animates the north wall texture by alternating
 * between north1 and north2 textures every 10 frames, creating a flickering
 * torch effect or similar dynamic visual element.
 */
static int	animate(t_data *data)
{
	data->game->animation_frame++;
	if (data->game->animation_frame >= 10)
	{
		if (data->elements->north_curr.img == data->elements->north1.img)
			data->elements->north_curr = data->elements->north2;
		else
			data->elements->north_curr = data->elements->north1;
		data->game->animation_frame = 0;
	}
	return (0);
}

/**
 * Updates player movement based on currently pressed keys
 * 
 * @param data: main game structure containing key states
 * 
 * This function checks the key state array and calls the appropriate
 * movement functions for each pressed key. The key mapping is:
 * - keys_pressed[0]: W key (move forward)
 * - keys_pressed[1]: S key (move backward)
 * - keys_pressed[2]: A key (strafe left)
 * - keys_pressed[3]: D key (strafe right)
 * - keys_pressed[4]: Left arrow (rotate left)
 * - keys_pressed[5]: Right arrow (rotate right)
 * 
 * This allows for smooth movement when multiple keys are held down.
 */
static void	update_movement(t_data *data)
{
	if (data->game->keys_pressed[0])
		move_player(data, data->player, FORWARD);
	if (data->game->keys_pressed[1])
		move_player(data, data->player, BACKWARD);
	if (data->game->keys_pressed[2])
		move_player(data, data->player, STRAFE_LEFT);
	if (data->game->keys_pressed[3])
		move_player(data, data->player, STRAFE_RIGHT);
	if (data->game->keys_pressed[4])
		rotate_player(data, ROTATE_LEFT);
	if (data->game->keys_pressed[5])
		rotate_player(data, ROTATE_RIGHT);
}

/**
 * Main game loop function called every frame
 * 
 * @param data: main game structure
 * @return: always returns 0
 * 
 * This function is called continuously by the MLX library and handles:
 * 1. Animation updates (texture cycling)
 * 2. Movement updates (based on pressed keys)
 * 3. Screen rendering (drawing the complete frame)
 * 
 * The order is important: animate first, then update movement,
 * then render the results to screen.
 */
int	game_loop(t_data *data)
{
	animate(data);
	update_movement(data);
	draw_image(data);
	return (0);
}

/**
 * Handles key release events
 * 
 * @param keycode: code of the released key
 * @param data: main game structure
 * @return: always returns 0
 * 
 * This function updates the key state array when keys are released,
 * setting the corresponding flag to 0. This allows for smooth movement
 * control where keys can be pressed and released independently.
 * 
 * Supports both regular ASCII codes and special key codes.
 */
int	key_release(int keycode, t_data *data)
{
	if (keycode == 'w' || keycode == 119)
		data->game->keys_pressed[0] = 0;
	else if (keycode == 's' || keycode == 115)
		data->game->keys_pressed[1] = 0;
	else if (keycode == 'a' || keycode == 97)
		data->game->keys_pressed[2] = 0;
	else if (keycode == 'd' || keycode == 100)
		data->game->keys_pressed[3] = 0;
	else if (keycode == 65361)
		data->game->keys_pressed[4] = 0;
	else if (keycode == 65363)
		data->game->keys_pressed[5] = 0;
	return (0);
}

/**
 * Handles key press events
 * 
 * @param keycode: code of the pressed key
 * @param data: main game structure
 * @return: always returns 0
 * 
 * This function handles both immediate actions (like door interaction)
 * and continuous actions (like movement). Immediate actions are executed
 * once per key press, while movement keys set flags in the keys_pressed
 * array for continuous processing in the game loop.
 * 
 * Key mappings:
 * - ESC (65307): Exit game
 * - SPACE (32): Interact with doors
 * - M (109): Toggle mouse control
 * - WASD: Movement (sets flags for continuous movement)
 * - Arrow keys: Rotation (sets flags for continuous rotation)
 */
int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == ' ' || keycode == 32)
		interact_with_door(data);
	else if (keycode == 'm' || keycode == 109)
	{
		data->game->mouse_enabled = !data->game->mouse_enabled;
		if (data->game->mouse_enabled)
			mlx_mouse_move(data->game->mlx, data->game->win,
				WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	else if (keycode == 'w' || keycode == 119)
		data->game->keys_pressed[0] = 1;
	else if (keycode == 's' || keycode == 115)
		data->game->keys_pressed[1] = 1;
	else if (keycode == 'a' || keycode == 97)
		data->game->keys_pressed[2] = 1;
	else if (keycode == 'd' || keycode == 100)
		data->game->keys_pressed[3] = 1;
	else if (keycode == 65361)
		data->game->keys_pressed[4] = 1;
	else if (keycode == 65363)
		data->game->keys_pressed[5] = 1;
	return (0);
}
