#include "parsing.h"

char	**create_map(char *map_line, int len)
{
	char	**map;

	map = ft_split_len(map_line, '\n', len, 0);
	if (!map)
		return (error("malloc failed in map creation", map_line), NULL);
	return (map);
}

/**
 * Measures the longest row of the map
 *
 * @param map_line: the raw map as one string, rows separated by newlines
 * @return the length of the longest row
 *
 * Maps are written ragged, with rows of different lengths, but the grid the
 * game walks on has to be rectangular: this length is what every row is
 * padded to, so that map[y][x] is valid for the whole rectangle instead of
 * reading past the end of a short row.
 */
int	get_longest_line(char *map_line)
{
	int	i;
	int	j;
	int	max;

	max = 0;
	i = 0;
	while (map_line[i] != '\0')
	{
		j = 0;
		while (map_line[i] != '\0' && map_line[i] != '\n')
		{
			i++;
			j++;
		}
		if (j > max)
			max = j;
		if (map_line[i] != '\0' && map_line[i] == '\n')
			i++;
	}
	return (max);
}

/**
 * Reads the map from the file and runs every check on it
 *
 * @param str: receives the map grid
 * @param fd: the scene file, positioned after the six elements
 * @param start: receives the player position and angle
 * @return 1 if the map is usable, 0 on the first failure
 *
 * The three checks run in this order because each needs what the previous
 * one guarantees: the character census first, since a map with two spawn
 * points or none would make the rest meaningless; then the border test,
 * which needs the rectangular grid; then the flood fill, which needs a
 * single spawn point to start from.
 */
int	get_map(t_basic_elements *str, int fd, t_player *start)
{
	int		len;
	char	*map_line;

	map_line = create_map_line(fd, NULL);
	if (map_line == NULL)
		return (free_basic_elements(str), 0);
	if (check_all_characters_are_present(map_line) == 0)
		return (free_basic_elements(str), 0);
	len = get_longest_line(map_line);
	str->map = create_map(map_line, len);
	if (str->map == NULL)
		return (free_basic_elements(str), 0);
	if (check_surrounded_by_wall(str->map, ft_matlen(str->map)) == 0)
		return (free_basic_elements(str), free(map_line), 0);
	if (validate_map(map_line, start) == 0)
		return (free_basic_elements(str), 0);
	return (1);
}
