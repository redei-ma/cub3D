/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:37:56 by ale               #+#    #+#             */
/*   Updated: 2025/06/25 03:04:37 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_element_h(t_basic_elements *str, char *new_line)
{
	int		i;
	int		len;
	char	*texture;

	i = 2;
	while (new_line[i] == ' ')
		i++;
	if (new_line[i] == '\0')
		return (0);
	len = i;
	while(new_line[len] != ' ' && new_line[len] != '\0' && !(new_line[len] >= 9 && new_line[len] <= 13))
		len++;
	texture = malloc(sizeof(char) * len - i + 1);
	ft_strlcpy(texture, &new_line[i], len - i + 1);
	if (new_line[0] == 'N')
		str->north_texture = texture;
	if (new_line[0] == 'S')
		str->south_texture = texture;
	if (new_line[0] == 'W')
		str->west_texture = texture;
	if (new_line[0] == 'E')
		str->east_texture = texture;
	return (1);
}

int	get_element(t_basic_elements *str, char *new_line)
{
	if (ft_strncmp(new_line, "NO", 2) == 0 && new_line[2] == ' ')
		return (get_element_h(str, new_line));
	else if (ft_strncmp(new_line, "SO", 2) == 0 && new_line[2] == ' ')
		return (get_element_h(str, new_line));
	else if (ft_strncmp(new_line, "WE", 2) == 0 && new_line[2] == ' ')
		return (get_element_h(str, new_line));
	else if (ft_strncmp(new_line, "EA", 2) == 0 && new_line[2] == ' ')
		return (get_element_h(str, new_line));
	else
	{
		error("incorrect syntax");//non molto bello come errore magari cambiarlo
		return (0);
	}
}

int	get_basic_elements(int fd, t_basic_elements *str)
{
	char				*new_line;
	bool				skip_line;
	int					elements_found;

	elements_found = 0;
	while(elements_found < 4)
	{
		skip_line = true;
		while(skip_line)
		{
			new_line = get_next_line(fd);//non la sto mai freeando
			if (!new_line)
			{
				//skip_line = true;//qua da scrivere che non ho trovato quello che volevo credo
				error("empty file or element missing");
				return (0);
			}
			while(new_line[0] == ' ' || new_line[0] == '\n')
				new_line++;
			if (new_line[0] == '\0')
				skip_line = true;
			else
				skip_line = false;
		}
		if (!get_element(str, new_line))
			return (0);
		elements_found++;
	/* 	write(2, ft_itoa(elements_found), ft_strlen_m(ft_itoa(elements_found)));
		write(2, new_line, ft_strlen_m(new_line)); */
	}
	return (1);
}
