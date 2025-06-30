/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:16:20 by redei-ma          #+#    #+#             */
/*   Updated: 2025/06/30 15:39:33 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC key
		close_window(data);
	else if (keycode == 'w')
		move_player(data, data->player, FORWARD);
	else if (keycode == 's')
		move_player(data, data->player, BACKWARD);
	else if (keycode == 'a')
		move_player(data, data->player, STRAFE_LEFT);
	else if (keycode == 'd')
		move_player(data, data->player, STRAFE_RIGHT);
	else if (keycode == 65361) // Freccia sinistra
		rotate_player(data, ROTATE_LEFT);
	else if (keycode == 65363) // Freccia destra
		rotate_player(data, ROTATE_RIGHT);
	draw_image(data);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->game->mlx, data->game->win);
	//manca il resto
	exit(0);
	return (0);
}
