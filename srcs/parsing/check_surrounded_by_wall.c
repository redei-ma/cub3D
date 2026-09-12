#include "parsing.h"

/**
 * Checks that no walkable cell touches the outside of the map
 *
 * @param map: the map grid
 * @param height: number of rows
 * @return 1 if every walkable cell is enclosed, 0 otherwise
 *
 * Every cell the player could stand on must have the four orthogonal
 * neighbours present and walkable or wall; a cell on the first or last row,
 * or in the first column, is rejected outright because one of its
 * neighbours would be outside the grid.
 *
 * This runs before the flood fill and catches a different mistake: the fill
 * proves the area is closed from the inside, this proves no walkable cell
 * was written on the border to begin with. A map can pass one and fail the
 * other.
 */
int	check_surrounded_by_wall(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_target(map[i][j], "0NSWED"))
			{
				if (i == 0 || j == 0 || i == height || \
!is_target(map[i - 1][j], "10NSWED") || !is_target(map[i][j - 1], "10NSWED") || \
!is_target(map[i + 1][j], "10NSWED") || !is_target(map[i][j + 1], "10NSWED"))
				{
					error("invalid map", NULL);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
