/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:16:20 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/01 16:59:42 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void update_movement(t_data *data)
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

int game_loop(t_data *data)
{
	update_movement(data);
	draw_image(data);
	return (0);
}

int key_release(int keycode, t_data *data)
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

int key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
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

int	close_window(t_data *data)
{
	mlx_destroy_window(data->game->mlx, data->game->win);
	mlx_destroy_image(data->game->mlx, data->game->img.img);
    mlx_destroy_display(data->game->mlx);
    free(data->game->mlx);
    free(data->game);
	free_basic_elements(data->elements);
	exit(0);
	return (0);
}
