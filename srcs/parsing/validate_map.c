#include "parsing.h"

bool	is_target(char c, char *target)
{
	while (*target)
	{
		if (c == *target)
			return (true);
		target++;
	}
	return (false);
}

/**
 * Flood fill that proves the map is closed, by trying to escape from it
 *
 * @param map: the map, modified in place as cells are visited
 * @param size: width and height, used as the boundary of the walkable area
 * @param current: the cell to visit, starting from the player position
 * @param target: the characters the fill is allowed to walk through
 * @return 1 if the area is closed, -1 as soon as a way out is found
 *
 * The check is stated backwards: instead of looking for holes in the walls,
 * the fill spreads from the player and fails the moment it reaches the edge
 * of the grid or a character that is not walkable. An enclosed area can
 * never do either.
 *
 * Visited cells are overwritten with '1', which is what keeps the recursion
 * from looping forever, and also why this runs on a copy of the map: by the
 * time it returns, that copy is solid wall.
 */
int	fill(char **map, int *size, t_player current, char *target)
{
	if (map[(int) current.y][(int) current.x] == '1')
	{
		return (0);
	}
	else if ((current.y <= 0) || (current.x <= 0) || (current.y >= size[1]) \
			|| (current.x >= size[0]) \
			|| !is_target(map[(int) current.y][(int) current.x], target))
	{
		return (-1);
	}
	map[(int) current.y][(int) current.x] = '1';
	if (fill(map, size, (t_player){current.x - 1, current.y, 0}, target) == -1)
		return (-1);
	if (fill(map, size, (t_player){current.x + 1, current.y, 0}, target) == -1)
		return (-1);
	if (fill(map, size, (t_player){current.x, current.y - 1, 0}, target) == -1)
		return (-1);
	if (fill(map, size, (t_player){current.x, current.y + 1, 0}, target) == -1)
		return (-1);
	return (1);
}

/**
 * Turns the spawn letter into the angle the player starts looking at
 *
 * @param starting_position: one of N, S, E, W
 * @return the angle in radians
 *
 * East is 0 and the angle grows clockwise, because the Y axis points down
 * in image coordinates: that is why South is PI/2 and North is 3*PI/2,
 * which is the opposite of what the unit circle would suggest.
 *
 * The angle is initialized to East rather than left to the four tests: they
 * are exhaustive only because find_start calls this for those letters alone,
 * and that guarantee lives in another file.
 */
static float	get_starting_angle(char starting_position)
{
	float	starting_angle;

	starting_angle = 0;
	if (starting_position == 'N')
		starting_angle = (M_PI * 3) / 2;
	if (starting_position == 'E')
		starting_angle = 0;
	if (starting_position == 'S')
		starting_angle = M_PI / 2;
	if (starting_position == 'W')
		starting_angle = M_PI;
	return (starting_angle);
}

static void	find_start(char **map, t_player *start)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || \
				map[y][x] == 'W' || map[y][x] == 'E')
			{
				start->x = x;
				start->y = y;
				start->angle = get_starting_angle(map[y][x]);
			}
			x++;
		}
		y++;
	}
}

/**
 * Finds the spawn point and proves the map is closed
 *
 * @param map_line: the raw map as one string, freed here
 * @param start: receives the player position and starting angle
 * @return 1 if the map is usable, 0 if it is open or cannot be built
 *
 * The map is rebuilt into a second grid on purpose: fill destroys what it
 * walks on, so the one kept for the game would come back as solid wall.
 *
 * Both sizes are passed decremented by one, so that the boundary test in
 * fill compares against the last valid index rather than the count.
 */
int	validate_map(char *map_line, t_player *start)
{
	char		**map2;
	int			map_size[2];

	map2 = create_map(map_line, get_longest_line(map_line));
	if (!map2)
		return (error("malloc failed\n", map_line), 0);
	find_start(map2, start);
	map_size[0] = get_longest_line(map_line) - 1;
	map_size[1] = ft_matlen(map2) - 1;
	free(map_line);
	if (fill (map2, map_size, *start, "NSWE0D") == -1)
	{
		free_map(map2);
		error("invalid map", NULL);
		return (0);
	}
	free_map(map2);
	return (1);
}
