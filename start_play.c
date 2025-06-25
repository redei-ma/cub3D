/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_play.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:16:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/06/25 16:54:01 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int map[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,1,1,0,1},
	{1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,1},
	{1,0,1,0,0,0,0,1,0,1},
	{1,0,1,1,0,0,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

t_window	*init_window(void)
{
	t_window	*window;

	window = ft_calloc(1, sizeof(t_window));
	if (!window)
		return (NULL); //handle error
	window->mlx = mlx_init();
	if (!window->mlx)
		return (NULL);
	window->win = mlx_new_window(window->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!window->win)
		return (NULL);
	return (window);
}

t_player	*set_player(void)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->x = 1.5;
	player->y = 1.5;
	player->angle = 0.0;
	return (player);
}

int main(void)
{
	t_window	*window;
	t_player	*player;

	window = init_window();
	if (!window)
		return (1); // handle error

	player = set_player(); //
	if (!player)
		return (1); // handle error
	
}