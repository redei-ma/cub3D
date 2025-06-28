/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:25:56 by redei-ma          #+#    #+#             */
/*   Updated: 2025/06/26 10:28:06 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_countlines(char **mat)
{
	int	count;

	if (!mat)
		return (0);
	count = 0;
	while (mat[count])
		count++;
	return (count);
}
