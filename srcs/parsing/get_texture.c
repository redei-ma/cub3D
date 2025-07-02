/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:45:14 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/02 15:12:45 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_initial_spaces_for_texture(char *new_line, int *i)
{
	while (new_line[*i] == ' ')
		(*i)++;
	if (new_line[*i] == '\n' || new_line[*i] == '\0')
		return (error("incorrect syntax", NULL), 0);
	return (1);
}

int	check_theres_nothing_after_texture(char *new_line, int len)
{
	while (new_line[len] == ' ')
		len++;
	if (new_line[len] != '\n')
		return (0);
	return (1);
}

int	check_texture_is_valid(char *texture)
{
	if (access(texture, R_OK) == -1)
	{
		free(texture);
		error("texture path is invalid", NULL);
		return (0);
	}
	return (1);
}

void	put_texture(t_basic_elements *str, char *new_line, char *texture)
{
	if (new_line[0] == 'N')
		str->north_texture = texture;
	if (new_line[0] == 'S')
		str->south_texture = texture;
	if (new_line[0] == 'W')
		str->west_texture = texture;
	if (new_line[0] == 'E')
		str->east_texture = texture;
}

int load_texture(t_data *data, char *path)
{
	t_texture	*text;

    texture->img = mlx_xpm_file_to_image(data->game->mlx, path, 
                                        &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    
    texture->addr = mlx_get_data_addr(texture->img, 
                                     &texture->bits_per_pixel,
                                     &texture->line_length, 
                                     &texture->endian);
    return (1);
}

int	get_texture(t_data *data, char *new_line)
{
	int		i;
	int		len;
	char	*texture;
	
	i = 2;
	if (skip_initial_spaces_for_texture(new_line, &i) == 0)
		return (0);
	len = i;
	while (new_line[len] != '\0' && new_line[len] != ' ' && \
		!(new_line[len] >= 9 && new_line[len] <= 13))
		len++;
	if (check_theres_nothing_after_texture(new_line, len) == 0)
		return (error("incorrect syntax", NULL), 0);
	texture = malloc(sizeof(char) * (len - i + 1));
	if (!texture)
		return (error("malloc failed", NULL), 0);
	load_texture(data, texture);
	ft_strlcpy(texture, &new_line[i], len - i + 1);
	if (check_texture_is_valid(texture) == 0)
		return (0);
	put_texture(data, new_line, texture);
	return (1);
}
