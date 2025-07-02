/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:57:24 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/02 16:17:05 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen_m(const char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	error(char *s, char *line_to_free)
{
	if (line_to_free != NULL)
		free(line_to_free);
	write(2, "Error\n", 6);
	write(2, s, ft_strlen_m(s));
	write(2, "\n", 1);
}

int	check_cub(char *s)
{
	int	is_valid;

	is_valid = 0;
	if (ft_strlen_m(s) >= 4)
	{
		if (ft_strncmp(s + (ft_strlen_m(s) - 4), ".cub", 4) == 0)
			is_valid = 1;
	}
	if (!is_valid)
		error("map is not .cub", NULL);
	return (is_valid);
}

void	init_basic_elements(t_basic_elements *str)
{
	str->north_texture = NULL;
	str->south_texture = NULL;
	str->west_texture = NULL;
	str->east_texture = NULL;
	str->north.img = NULL;
	str->south.img = NULL;
	str->west.img = NULL;
	str->east.img = NULL;
	str->map = NULL;
}

int	handle_parsing(int argc, char **argv, t_basic_elements *elements_struct, \
	t_player *start)
{
	int	fd;

	if (argc < 2)
	{
		error("no arguments dummy", NULL);
		return (0);
	}
	if (!check_cub(argv[1]))
		return (0);
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		error("map file not readable or not present", NULL);
		return (0);
	}
	init_basic_elements(elements_struct);
	if (get_basic_elements(elements_struct, fd) == 0)
	{
		free_basic_elements(elements_struct);
		return (0);
	}
	if (get_map(elements_struct, fd, start) == 0)
		return (close(fd), 0);
	close(fd);
	return (1);
}
