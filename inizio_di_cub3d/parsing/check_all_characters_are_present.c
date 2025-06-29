/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_characters_are_present.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:10:14 by ale               #+#    #+#             */
/*   Updated: 2025/06/29 16:36:31 by ale              ###   ########.fr       */
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

void	init_characters_array(int *i, int characters_arr[3])
{
	*i = 0;
	while (*i < 3)
	{
		characters_arr[*i] = 0;
		(*i)++;
	}
}

//function checks that all the 5 parts of the map are present
//and that there isn't more tha one starting point
int	check_all_characters_are_present(char *map_line)
{
	int	characters_arr[3];
	int	i;

	init_characters_array(&i, characters_arr);
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
