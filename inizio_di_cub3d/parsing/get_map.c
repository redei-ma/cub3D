/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:06:45 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/28 04:02:46 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//helper of check_all_characters_are_present
int	check_characters_array(int *characters_arr, char *map_line)
{
	if (characters_arr[2] > 1)
		return(error("too many starting points", map_line), 0);
	if (characters_arr[0] == 0)
		return(error("no walls in map", map_line), 0);
	if (characters_arr[2] == 0)
		return(error("no starting point in map", map_line), 0);
	return (1);
}

//function checks that all the 5 parts of the map are present
//and that there isn't more tha one starting point
int	check_all_characters_are_present(char *map_line)
{
	int	characters_arr[3];
	int	i;

	i = -1;
	while (++i < 3)
		characters_arr[i] = 0;
	i = 0;
	while (map_line[i] != '\0')
	{
		if (map_line[i] == '1')
			characters_arr[0] = 1;
		else if (map_line[i] == '0')
			characters_arr[1] = 1;
		else if (map_line[i] == 'N')
			characters_arr[2]++;
		else if (map_line[i] == 'S')
			characters_arr[2]++;
		else if (map_line[i] == 'E')
			characters_arr[2]++;
		else if (map_line[i] == 'W')
			characters_arr[2]++;
		else if (map_line[i] == ' ')
			;
		else if (map_line[i] != '\n')
			return (error("wrong character in map", map_line), 0);
		i++;
	}
	return (check_characters_array(characters_arr, map_line));
}

char	*create_map_line(int fd)
{
	char	*str;
	char	*temp;
	char	*new_line;

	str = NULL;/* malloc(1);
	if (!str)
		return(error("malloc failed", NULL), NULL);
	str[0] = '\0'; */
	new_line = get_next_line(fd);
	while (new_line && new_line[0] == '\n' && new_line[1] == '\0')
	{
		free(new_line);
		new_line = get_next_line(fd);
	}
	if (!new_line)
	{
		//free(str);
		return (error("no map present in file", NULL), NULL);
	}
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
	if (new_line)
	{
		while (new_line)
		{
			free(new_line);
			new_line = get_next_line(fd);
		}
	}
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

	map_line = create_map_line(fd);
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
