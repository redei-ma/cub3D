#include "parsing.h"

static int	skip_initial_spaces_for_texture(char *new_line, int *i)
{
	while (new_line[*i] == ' ')
		(*i)++;
	if (new_line[*i] == '\n' || new_line[*i] == '\0')
		return (error("incorrect syntax", NULL), 0);
	return (1);
}

static int	check_theres_nothing_after_texture(char *new_line, int len)
{
	while (new_line[len] == ' ')
		len++;
	if (new_line[len] != '\n')
		return (0);
	return (1);
}

static int	check_texture_is_valid(char *texture)
{
	if (access(texture, R_OK) == -1)
	{
		free(texture);
		error("texture path is invalid", NULL);
		return (0);
	}
	return (1);
}

static void	put_texture(t_basic_elements *str, char *new_line, char *texture)
{
	if (new_line[0] == 'N')
		str->north_texture1 = texture;
	if (new_line[0] == 'S')
		str->south_texture = texture;
	if (new_line[0] == 'W')
		str->west_texture = texture;
	if (new_line[0] == 'E')
		str->east_texture = texture;
}

/**
 * Parses one NO, SO, WE or EA line and stores the texture path
 *
 * @param str: receives the path, owned from here on
 * @param new_line: the whole line, identifier included
 * @return 1 if the path is readable, 0 otherwise
 *
 * The path is checked with access(R_OK) here, at parse time, rather than
 * when the image is loaded: a scene that names a missing texture is a
 * malformed scene, and failing now means failing before a window is opened.
 *
 * The wall the texture belongs to is read from the first letter of the
 * line, which is why only N, S, W and E are tested: the identifier was
 * already matched by get_element.
 */
int	get_texture(t_basic_elements *str, char *new_line)
{
	int		i;
	int		len;
	char	*texture;

	i = 2;
	if (skip_initial_spaces_for_texture(new_line, &i) == 0)
		return (0);
	len = i;
	while (new_line[len] != '\0' && new_line[len] != ' ' && \
		!(new_line[len] >= 9 && new_line[len] <= 13))
		len++;
	if (check_theres_nothing_after_texture(new_line, len) == 0)
		return (error("incorrect syntax", NULL), 0);
	texture = malloc(sizeof(char) * (len - i + 1));
	if (!texture)
		return (error("malloc failed", NULL), 0);
	ft_strlcpy(texture, &new_line[i], len - i + 1);
	if (check_texture_is_valid(texture) == 0)
		return (0);
	put_texture(str, new_line, texture);
	return (1);
}
