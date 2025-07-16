/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:11:50 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/30 20:22:39 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_init_lines(char **new_line, int fd)
{
	while (new_line[0] && new_line[0][0] == '\n' && new_line[0][1] == '\0')
	{
		free(*new_line);
		*new_line = get_next_line(fd);
	}
}

int	check_theres_nothing_after_map(int fd, char *new_line)
{
	int	map_is_valid;

	map_is_valid = 1;
	while (new_line)
	{
		if (new_line[0] != '\n' && new_line[1] != '\0')
			map_is_valid = 0;
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (map_is_valid);
}

char	*create_map_line(int fd, char *str)
{
	char	*temp;
	char	*new_line;

	str = NULL;
	new_line = get_next_line(fd);
	skip_init_lines(&new_line, fd);
	if (!new_line)
		return (error("no map present in file", NULL), NULL);
	while (new_line && new_line[0] != '\n')
	{
		temp = ft_strjoin_m(str, new_line);
		free(str);
		if (!temp)
		{
			finish_get_next_line(new_line, fd);
			return (error("malloc failed in map_line creation", NULL), NULL);
		}
		free(new_line);
		str = temp;
		new_line = get_next_line(fd);
	}
	if (check_theres_nothing_after_map(fd, new_line) == 0)
		return (error("there should be nothing after the map", str), NULL);
	return (str);
}
