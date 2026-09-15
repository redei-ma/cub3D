#include "parsing.h"

/**
 * Turns the character census into the matching error
 *
 * @param characters_arr: the counters filled while scanning the map
 * @param map_line: freed by error() before the message is printed
 * @return 1 if the census is acceptable, 0 otherwise
 *
 * Split out of check_all_characters_are_present because the Norm caps a
 * function at 25 lines, not because the two do different things.
 */
static int	check_characters_array(int *characters_arr, char *map_line)
{
	if (characters_arr[1] > 1)
		return (error("too many starting points", map_line), 0);
	if (characters_arr[0] == 0)
		return (error("no walls in map", map_line), 0);
	if (characters_arr[1] == 0)
		return (error("no starting point in map", map_line), 0);
	return (1);
}

static void	init_characters_array(int *i, int characters_arr[2])
{
	*i = 0;
	while (*i < 2)
	{
		characters_arr[*i] = 0;
		(*i)++;
	}
	*i = 0;
}

/**
 * Census of the map characters, run before the grid is even built
 *
 * @param map_line: the raw map as one string
 * @return 1 if the map holds only legal characters and exactly one spawn
 *         point, 0 otherwise
 *
 * Only three things can be wrong here and all three are fatal: an unknown
 * character, no wall at all, or a number of spawn points other than one.
 * Spaces and 'D', the bonus door, are legal and deliberately ignored.
 *
 * The two counters are kept in an array rather than in two variables so
 * that the check can be split into its own function without passing them
 * one by one: [0] records that a wall was seen, [1] counts spawn points.
 *
 * This runs first because everything downstream assumes its result: the
 * flood fill starts from the spawn point, and with two of them it would
 * start from whichever comes last.
 */
int	check_all_characters_are_present(char *map_line)
{
	int	characters_arr[2];
	int	i;

	init_characters_array(&i, characters_arr);
	while (map_line[i] != '\0')
	{
		if (map_line[i] == '1')
			characters_arr[0] = 1;
		else if (map_line[i] == '0' || map_line[i] == ' ' || map_line[i] == 'D')
			;
		else if (map_line[i] == 'N')
			characters_arr[1]++;
		else if (map_line[i] == 'S')
			characters_arr[1]++;
		else if (map_line[i] == 'E')
			characters_arr[1]++;
		else if (map_line[i] == 'W')
			characters_arr[1]++;
		else if (map_line[i] != '\n')
			return (error("wrong character in map", map_line), 0);
		i++;
	}
	return (check_characters_array(characters_arr, map_line));
}
