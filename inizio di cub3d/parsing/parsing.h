/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:58:00 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/25 02:44:40 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/mlx/mlx.h"
#include "./includes/libft/libft.h"
//#include <X11/keysym.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

typedef struct	s_basic_elements
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_colours[3];
	int		ceiling_colours[3];
	char	**map;
}				t_basic_elements;

//parsing
int		ft_strlen_m(const char *s);
void	error(char *s);
int		check_cub(char *s);
int		handle_map(int argc, char **argv, t_basic_elements *elements_struct);

int	get_element_h(t_basic_elements *str, char *new_line);
int	get_element(t_basic_elements *str, char *new_line);
int	get_basic_elements(int fd, t_basic_elements *str);
