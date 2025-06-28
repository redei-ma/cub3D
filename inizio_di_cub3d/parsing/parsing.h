/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:58:00 by ade-ross          #+#    #+#             */
/*   Updated: 2025/06/28 03:10:05 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/mlx/mlx.h"
#include "./includes/libft/libft.h"
//#include <X11/keysym.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

# define M_PI 3.14159265358979323846

typedef struct	s_player
{
	float	x;
	float	y;
	float	angle;
}				t_player;

typedef struct	s_basic_elements
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_colours[3];
	int			ceiling_colours[3];
	char		**map;
	t_player	*start_pos;
}				t_basic_elements;

//parsing
int		ft_strlen_m(const char *s);
void	error(char *s, char *line_to_free);
int		check_cub(char *s);
int		handle_parsing(int argc, char **argv, t_basic_elements *elements_struct);

//get_elements
int		get_colors(t_basic_elements *str, char *new_line, char first_letter);
int		get_texture(t_basic_elements *str, char *new_line);
int		get_element(t_basic_elements *str, char *new_line);
int		get_basic_elements(t_basic_elements *str, int fd);

//free_vari
void	free_map(char **map);
void	free_basic_elements(t_basic_elements *str);

//get_map
int		check_characters_array(int *characters_arr, char *map_line);
int		check_all_characters_are_present(char *map_line);
char	*create_map_line(int fd);
char	**create_map(char *map_line, int len);
int		get_longest_line(char *map_line);
int		get_map(t_basic_elements *str, int fd);

//ft_countlines
int		ft_countlines(char **mat);

//ft_split_leb
char	**ft_split_len(char const *s, char c, int len, int i);

//validate_map
int		fill(char **map, int *size, t_player current, char *target);
int		validate_map(char *map_line, t_basic_elements *data);
