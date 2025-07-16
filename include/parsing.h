/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:58:00 by ade-ross          #+#    #+#             */
/*   Updated: 2025/07/16 11:00:42 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

# define M_PI 3.14159265358979323846	// Pi constant for angle calculations

/**
 * Texture structure for image data and MLX parameters
 * Contains all necessary information for texture mapping
 */
typedef struct s_texture
{
	void	*img;			// MLX image pointer
	char	*addr;			// Memory address of image data
	int		width;			// Texture width in pixels
	int		height;			// Texture height in pixels
	int		bits_per_pixel;	// Color depth information
	int		line_length;	// Bytes per image line
	int		endian;			// Byte order information
}			t_texture;

/**
 * Player structure containing position and orientation
 */
typedef struct s_player
{
	float	x;		// X coordinate in world space
	float	y;		// Y coordinate in world space
	float	angle;	// Viewing angle in radians
}				t_player;

/**
 * Basic game elements structure containing all textures and colors
 * Loaded from the .cub configuration file
 */
typedef struct s_basic_elements
{
	char		*north_texture1;	// Path to north wall texture 1
	t_texture	north1;				// North wall texture 1 data
	t_texture	north2;				// North wall texture 2 data (animation)
	t_texture	north_curr;			// Current north texture (alternates)
	char		*south_texture;		// Path to south wall texture
	t_texture	south;				// South wall texture data
	char		*west_texture;		// Path to west wall texture
	t_texture	west;				// West wall texture data
	char		*east_texture;		// Path to east wall texture
	t_texture	east;				// East wall texture data
	int			floor_colour;		// Floor color (RGB)
	int			ceiling_colour;		// Ceiling color (RGB)
	t_texture	door;				// Door texture data
	char		**map;				// 2D map array
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
bool	is_target(char c, char *target);
int		fill(char **map, int *size, t_player current, char *target);
int		validate_map(char *map_line, t_player *start);

//check_surrounded_by_wall
int		check_surrounded_by_wall(char **map, int height);

//strjoin_m
char	*ft_strjoin_m(char const *s1, char const *s2);

//check_all_characters_are_present
int		check_characters_array(int *characters_arr, char *map_line);
int		check_all_characters_are_present(char *map_line);

#endif
