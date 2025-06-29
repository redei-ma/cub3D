/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:06:45 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/29 16:19:04 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_theres_nothing_after_map(int fd, char *new_line)
{
	int	map_is_valid;

	map_is_valid = 1;
	while (new_line)
	{
		if(new_line[0] != '\n' && new_line[1] != '\0')
			map_is_valid = 0;
		free(new_line);
		new_line = get_next_line(fd);
	}
	return(map_is_valid);
}

char	*create_map_line(int fd, char *str)
{
	char	*temp;
	char	*new_line;

	str = NULL;
	new_line = get_next_line(fd);
	while (new_line && new_line[0] == '\n' && new_line[1] == '\0')
	{
		free(new_line);
		new_line = get_next_line(fd);
	}
	if (!new_line)
		return (error("no map present in file", NULL), NULL);
	while (new_line && new_line[0] != '\n')//capire cosa fare se ci sono linee vuote o linee con solo spazi nella mappa
	{
		temp = ft_strjoin(str, new_line);
		free(new_line);
		free(str);
		if (!temp)
			return (error("malloc failed in map_line creation", NULL), NULL);
		str = temp;
		new_line = get_next_line(fd);
	}
	if (check_theres_nothing_after_map(fd, new_line) == 0)
		return (error("there should be nothing after the map", str), NULL);
	return (str);
}

char	**create_map(char *map_line, int len)
{
	char	**map;

	map = ft_split_len(map_line, '\n', len, 0);
	if (!map)
		return (error("malloc failed in map creation", map_line), NULL);
	return (map);
}

int	get_longest_line(char *map_line)
{
	int	i;
	int	j;
	int	max;

	max = 0;
	i = 0;
	while (map_line[i] != '\0')
	{
		j = 0;
		while (map_line[i] != '\n' && map_line[i] != '\0')
		{
			i++;
			j++;
		}
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int	get_map(t_basic_elements *str, int fd)
{
	int		len;
	char	*map_line;

	map_line = create_map_line(fd, NULL);
	if (map_line == NULL)
		return (free_basic_elements(str), 0);
	if (check_all_characters_are_present(map_line) == 0)
		return (free_basic_elements(str), 0);
	len = get_longest_line(map_line);
	str->map = create_map(map_line, len);
	if(str->map == NULL)
		return (free_basic_elements(str), 0);
	if (validate_map(map_line, str) == 0)
		return (free_basic_elements(str), 0);
	return (1);
}
