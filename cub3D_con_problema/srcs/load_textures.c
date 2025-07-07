/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:43:41 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/07 17:40:37 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
}

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
	data->elements->north_curr = data->elements->north1;
	return (1);
}
