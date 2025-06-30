/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:46:30 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/30 19:12:35 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_initial_spaces_and_initial_checks(char **new_line, int *i)
{
	while (new_line[0][*i] == ' ')
		(*i)++;
	if (new_line[0][*i] == '\0' || new_line[0][*i] == '\n')
		return (error("incorrect syntax", NULL), 0);
	*new_line = *new_line + *i;
	*i = 0;
	if (new_line[0][*i] == '+')
		(*i)++;
	while (new_line[0][*i] >= '0' && new_line[0][*i] <= '9')
		(*i)++;
	return (1);
}

void	put_colors(t_basic_elements *str, char first_letter, int j, int num)
{
	if (first_letter == 'F')
		str->floor_colours[j] = num;
	if (first_letter == 'C')
		str->ceiling_colours[j] = num;
}

int	check_theres_nothing_after_colors(char *new_line, int len, int j)
{
	if (j == 2)
	{
		if (new_line[len] == ',')
			len++;
		while (new_line[len] == ' ')
			len++;
		if (new_line[len] != '\n')
			return (error("incorrect syntax", NULL), 0);
	}
	return (1);
}

int	get_colors(t_basic_elements *str, char *new_line, char first_letter)
{
	int	i;
	int	j;
	int	num;

	i = 1;
	j = -1;
	while (++j < 3)
	{
		if (j != 0)
			i = 0;
		if (skip_initial_spaces_and_initial_checks(&new_line, &i) == 0)
			return (0);
		if (i == 0 || (new_line[0] == '+' && i > 4) || \
			(new_line[0] != '+' && i > 3) || (j != 2 && new_line[i] != ','))
			return (error("incorrect syntax", NULL), 0);
		num = ft_atoi(new_line);
		if (!(num >= 0 && num <= 255))
			return (error("RGB colors must be between 0 and 255", NULL), 0);
		put_colors(str, first_letter, j, num);
		if (j != 2)
			new_line = new_line + i + 1;
		if (check_theres_nothing_after_colors(new_line, i, j) == 0)
			return (0);
	}
	return (1);
}
