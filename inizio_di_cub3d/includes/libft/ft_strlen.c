/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:31:45 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/28 03:36:02 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return(0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
/*
#include <string.h>
#include <stdio.h>
int	main()
{
	const char *st = "ciaoo";

	size_t l = ft_strlen(st);
	size_t n = strlen(st);
	printf("%zu", l);
	printf("%zu", n);
	return 0;
}*/
