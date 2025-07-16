/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:37:56 by ale               #+#    #+#             */
/*   Updated: 2025/07/02 12:23:31 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		error("incorrect syntax", NULL);
		return (0);
	}
}

bool	skip_empty_line_and_initial_spaces(int *i, char *new_line)
{
	bool	skip_line;

	*i = 0;
	while (new_line[*i] == ' ' || new_line[*i] == '\n')
		(*i)++;
	if (new_line[*i] == '\0')
		skip_line = true;
	else
		skip_line = false;
	return (skip_line);
}

void	finish_get_next_line(char *new_line, int fd)
{
	while (new_line)
	{
		free(new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
}

int	get_basic_elements(t_basic_elements *str, int fd)
{
	char	*new_line;
	bool	skip_line;
	int		elements_found;
	int		i;

	elements_found = 0;
	new_line = NULL;
	while (elements_found < 6)
	{
		skip_line = true;
		while (skip_line)
		{
			if (new_line != NULL)
				free(new_line);
			new_line = get_next_line(fd);
			if (!new_line)
				return (error("incorrect syntax", 0), close(fd), 0);
			skip_line = skip_empty_line_and_initial_spaces(&i, new_line);
		}
		if (!get_element(str, &new_line[i]))
			return (finish_get_next_line(new_line, fd), 0);
		elements_found++;
	}
	free(new_line);
	return (1);
}
