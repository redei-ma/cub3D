/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:37:56 by ale               #+#    #+#             */
/*   Updated: 2025/06/25 20:38:40 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_colors(t_basic_elements *str, char *new_line, char first_letter)
{
	int	i;
	int	j;
	int	num;

	i = 2;
	j = 0;
	while(j < 3)
	{
		if(j != 0)
			i = 0;
		while (new_line[i] == ' ')
			i++;
		if (new_line[i] == '\0')
			return (error("incorrect syntax", NULL), 0);
		new_line = new_line + i;
		i = 0;
		if (new_line[i] == '+')
			i++;
		while(new_line[i] >= '0' && new_line[i] <= '9')
			i++;
		if (i == 0 || (new_line[0] == '+' && i > 4) || (new_line[0] != '+' && i > 3) || (j != 2 && new_line[i] != ','))
			return (error("incorrect syntax", NULL), 0);
		num = ft_atoi(new_line);
		if (!(num >= 0 && num <= 255))
			return (error("numbers for colors must be between 0 and 255", NULL), 0);
		if (first_letter == 'F')
			str->floor_colours[j] = num;
		if (first_letter == 'C')
			str->ceiling_colours[j] = num;
		if (j != 2)
			new_line = new_line + i + 1;
		j++;
	}
	return (1);
}

int	get_texture(t_basic_elements *str, char *new_line)
{
	int		i;
	int		len;
	char	*texture;

	i = 2;
	while (new_line[i] == ' ')
		i++;
	if (new_line[i] == '\0')
		return (error("incorrect syntax", NULL), 0);
	len = i;
	while(new_line[len] != ' ' && new_line[len] != '\0' && !(new_line[len] >= 9 && new_line[len] <= 13))
		len++;
	texture = malloc(sizeof(char) * len - i + 1);
	if (!texture)	
		return(error("malloc failed", NULL), 0);
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
		return (get_texture(str, new_line));
	else if (ft_strncmp(new_line, "SO", 2) == 0 && new_line[2] == ' ')
		return (get_texture(str, new_line));
	else if (ft_strncmp(new_line, "WE", 2) == 0 && new_line[2] == ' ')
		return (get_texture(str, new_line));
	else if (ft_strncmp(new_line, "EA", 2) == 0 && new_line[2] == ' ')
		return (get_texture(str, new_line));
	else if (new_line[0] == 'F' && new_line[1] == ' ')
		return (get_colors(str, new_line, new_line[0]));
	else if (new_line[0] == 'C' && new_line[1] == ' ')
		return (get_colors(str, new_line, new_line[0]));
	else
	{
		error("incorrect syntax", NULL);//non molto bello come errore magari cambiarlo
		return (0);
	}
}

int	get_basic_elements(t_basic_elements *str, int fd)
{
	char				*new_line;
	bool				skip_line;
	int					elements_found;
	int					i;

	elements_found = 0;
	new_line = malloc(1);
	while(elements_found < 6)
	{
		skip_line = true;
		while(skip_line)
		{
			free(new_line);
			new_line = get_next_line(fd);//non la sto mai freeando
			if (!new_line)
			{
				//skip_line = true;//qua da scrivere che non ho trovato quello che volevo credo
				error("empty file or element missing", NULL);
				return (free_basic_elements(str), 0);
			}
			i = 0;
			while(new_line[i] == ' ' || new_line[i] == '\n')
				i++;
			if (new_line[i] == '\0')
				skip_line = true;
			else
				skip_line = false;
		}
		if (!get_element(str, &new_line[i]))
			return (free_basic_elements(str), free(new_line), 0);
		elements_found++;
	/*	write(2, ft_itoa(elements_found), ft_strlen_m(ft_itoa(elements_found)));
		write(2, new_line, ft_strlen_m(new_line)); */
	}
	free(new_line);
	return (1);
}
