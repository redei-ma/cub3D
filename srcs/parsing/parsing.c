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

void	error(char *s, char *line_to_free)
{
	if (line_to_free != NULL)
		free(line_to_free);
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
		error("map is not .cub", NULL);
	return (is_valid);
}

static void	init_basic_elements(t_basic_elements *str)
{
	str->north_texture1 = NULL;
	str->south_texture = NULL;
	str->west_texture = NULL;
	str->east_texture = NULL;
	str->north1.img = NULL;
	str->north2.img = NULL;
	str->north_curr.img = NULL;
	str->south.img = NULL;
	str->west.img = NULL;
	str->east.img = NULL;
	str->door.img = NULL;
	str->map = NULL;
}

/**
 * Reads and validates the whole scene file
 *
 * @param argc: argument count, exactly two are expected
 * @param argv: argv[1] is the path to the .cub file
 * @param elements_struct: receives textures, colors and the map
 * @param start: receives the player position and starting angle
 * @return 1 if the scene is usable, 0 on the first failure
 *
 * Nothing is opened before argc is checked, which is what lets every
 * function downstream take argv[1] for granted.
 *
 * The order is imposed by the format: the six elements come first and in
 * any order among themselves, the map always last, so the file is read once
 * from top to bottom and the descriptor is handed to get_map still open,
 * positioned exactly where the elements ended.
 */
int	handle_parsing(int argc, char **argv, t_basic_elements *elements_struct, \
	t_player *start)
{
	int	fd;

	if (argc < 2)
	{
		error("usage: ./cub3D <map.cub>", NULL);
		return (0);
	}
	if (!check_cub(argv[1]))
		return (0);
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		error("map file not readable or not present", NULL);
		return (0);
	}
	init_basic_elements(elements_struct);
	if (get_basic_elements(elements_struct, fd) == 0)
	{
		free_basic_elements(elements_struct);
		return (0);
	}
	if (get_map(elements_struct, fd, start) == 0)
		return (close(fd), 0);
	close(fd);
	return (1);
}
