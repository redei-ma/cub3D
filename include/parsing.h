/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:58:00 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/08 09:56:22 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../minilibx-linux/mlx.h"

#define M_PI 3.14159265358979323846

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_texture;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}				t_player;

typedef struct s_basic_elements
{
	char		*north_texture1;
	t_texture	north1;
	char		*north_texture2;
	t_texture	north2;
	t_texture	north_curr;
	char		*south_texture;
	t_texture	south;
	char		*west_texture;
	t_texture	west;
	char		*east_texture;
	t_texture	east;
	int			floor_colour;
	int			ceiling_colour;
	t_texture	door;
	char		**map;
}				t_basic_elements;

//parsing
int		ft_strlen_m(const char *s);
void	error(char *s, char *line_to_free);
int		check_cub(char *s);
int		handle_parsing(int argc, char **argv, \
		t_basic_elements *elements_struct, t_player *start);

//get_colors
int		skip_initial_spaces_and_initial_checks(char **new_line, int *i);
int		get_colors(t_basic_elements *str, char *new_line, char first_letter);

//get_texture
int		check_theres_nothing_after_texture(char *new_line, int len);
int		check_texture_is_valid(char *texture);
int		get_texture(t_basic_elements *str, char *new_line);

//get_elements
void	finish_get_next_line(char *new_line, int fd);
int		get_texture(t_basic_elements *str, char *new_line);
int		get_element(t_basic_elements *str, char *new_line);
int		get_basic_elements(t_basic_elements *str, int fd);

//free_vari
void	free_map(char **map);
void	free_basic_elements(t_basic_elements *str);

//check_all_characters_are_present
int		check_characters_array(int *characters_arr, char *map_line);
int		check_all_characters_are_present(char *map_line);

//create_map_line
int		check_theres_nothing_after_map(int fd, char *new_line);
char	*create_map_line(int fd, char *str);

//get_map

char	**create_map(char *map_line, int len);
int		get_longest_line(char *map_line);
int		get_map(t_basic_elements *str, int fd, t_player *start);

//ft_split_leb
char	**ft_split_len(char const *s, char c, int len, int i);

//validate_map
int		fill(char **map, int *size, t_player current, char *target);
int		validate_map(char *map_line, t_player *start);

//strjoin_m
char	*ft_strjoin_m(char const *s1, char const *s2);

//check_all_characters_are_present
int		check_characters_array(int *characters_arr, char *map_line);
int		check_all_characters_are_present(char *map_line);
