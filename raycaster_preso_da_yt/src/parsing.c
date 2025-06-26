/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:57:24 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/18 19:04:07 by ade-ross         ###   ########.fr       */
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

void	check_cub(char *s)
{
	if (ft_strlen_m(s) >= 4)
	{
		if (ft_strncmp(s + (ft_strlen_m(s) - 4), ".cub", 4) == 0)
			return ;
	}
	error("map is not .cub", NULL, NULL);
}