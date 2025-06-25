/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:57:24 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/25 02:59:50 by ale              ###   ########.fr       */
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

void	error(char *s)
{
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
		error("map is not .cub");
	return (is_valid);
}

int	handle_map(int argc, char **argv, t_basic_elements *elements_struct)
{
	int	fd;

	if (argc < 2)
	{
		error("no arguments dummy");
		return (0);
	}
	if (!check_cub(argv[1]))
		return (0);
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		error("map file not readable or not present");
		return (0);
	}
	if (get_basic_elements(fd, elements_struct) == 0)
		return (0);
	return (1);
}
