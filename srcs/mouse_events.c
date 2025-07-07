/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:47:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/07 12:33:20 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player_mouse(t_data *data, int delta_x)
{
	const double	mouse_sensitivity = R_SPEED / 10.0;

	data->game->mouse_accumulator += delta_x * mouse_sensitivity;
	if (fabs(data->game->mouse_accumulator) > 0.005)
	{
		data->player->angle += data->game->mouse_accumulator;
		data->game->mouse_accumulator = 0;
		if (data->player->angle >= 2 * M_PI)
			data->player->angle -= 2 * M_PI;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
}

int	mouse_hook(int x, int y, t_data *data)
{
	const int	center_x = WIN_WIDTH / 2;
	const int	center_y = WIN_HEIGHT / 2;
	int			delta_x;

	(void)y;
	delta_x = x - center_x;
	if (abs(delta_x) > 1)
	{
		rotate_player_mouse(data, delta_x);
		mlx_mouse_move(data->game->mlx, data->game->win, center_x, center_y);
	}
	return (0);
}
