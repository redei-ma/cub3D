/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:35:42 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/28 03:36:54 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newst;
	int		i;

	i = 0;
	newst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newst)
		return (NULL);
	while (s1 && *s1 != '\0')
	{
		newst[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2 != '\0')
	{
		newst[i] = *s2;
		i++;
		s2++;
	}
	newst[i] = '\0';
	return (newst);
}
/*
int main()
{
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";

	char	*st = ft_strjoin(s1, s2);
	printf("%s\n", st);
} */
