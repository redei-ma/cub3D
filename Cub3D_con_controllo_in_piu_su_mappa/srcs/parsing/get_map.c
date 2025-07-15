/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:06:45 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/15 05:52:33 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		while (map_line[i] != '\0' && map_line[i] != '\n')
		{
			i++;
			j++;
		}
		if (j > max)
			max = j;
		if (map_line[i] != '\0' && map_line[i] == '\n')
			i++;
	}
	return (max);
}

int	get_map(t_basic_elements *str, int fd, t_player *start)
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
	if (str->map == NULL)
		return (free_basic_elements(str), 0);
	if (check_surrounded_by_wall(str->map, ft_countlines(((const char **)str->map))) == 0)
		return (free_basic_elements(str), free(map_line), 0);//capire perche qua serve freeare mapline ma sotto su validate map no
	if (validate_map(map_line, start) == 0)
		return (free_basic_elements(str), 0);
	return (1);
}
