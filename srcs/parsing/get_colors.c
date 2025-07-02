/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:46:30 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/02 14:16:50 by ade-ross         ###   ########.fr       */
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

int	convert_color(int r, int g, int b)
{
	int c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

void	put_colors(t_basic_elements *str, int color[3], char first_letter)
{
	int	num;

	num = convert_color(color[0], color[1], color[2]);
	if (first_letter == 'F')
		str->floor_colour = num;
	if (first_letter == 'C')
		str->ceiling_colour = num;
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
	int color[3];

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
		color[j] = ft_atoi(new_line);
		if (!(color[j] >= 0 && color[j] <= 255))
			return (error("RGB colors must be between 0 and 255", NULL), 0);
		if (j != 2)
			new_line = new_line + i + 1;
		if (check_theres_nothing_after_colors(new_line, i, j) == 0)
			return (0);
	}
	put_colors(str, color, first_letter);
	return (1);
}
