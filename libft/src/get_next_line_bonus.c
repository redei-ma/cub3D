#include "get_next_line_bonus.h"

static char	*find_newline(char **str)
{
	char	*fin;
	char	*tmp;
	int		i;

	i = 0;
	fin = NULL;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		fin = ft_substr(*str, 0, i + 1);
		if (!fin)
			return (free(*str), NULL);
		if (i == (int)ft_strlen(*str) - 1)
			tmp = NULL;
		else
		{
			tmp = ft_substr(*str, i + 1, ft_strlen(*str) - i - 1);
			if (!tmp)
				return (free(fin), free(*str), NULL);
		}
		free(*str);
		*str = tmp;
	}
	return (fin);
}

static int	read_line(char **s, int fd)
{
	char	*buff;
	char	*tmp;
	ssize_t	bytes_read;

	buff = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (-1);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		tmp = ft_strjoin(*s, buff);
		if (!tmp)
		{
			free(buff);
			return (-1);
		}
		free(*s);
		*s = tmp;
	}
	free(buff);
	return (bytes_read);
}

static char	*test(char **leftovers, char **final, int bytes)
{
	if (bytes < 0)
	{
		free(*leftovers);
		*leftovers = NULL;
		return (NULL);
	}
	else if (bytes == 0)
	{
		if (*leftovers && ft_strlen(*leftovers) > 0)
		{
			*final = *leftovers;
			*leftovers = NULL;
			return (*final);
		}
		free(*leftovers);
		*leftovers = NULL;
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftovers[4096];
	char		*final;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// the array is indexed by fd, and nothing stops the system from handing
	// out a descriptor past its end: the bound comes from the array itself
	if ((size_t)fd >= sizeof(leftovers) / sizeof(*leftovers))
		return (NULL);
	if (!leftovers[fd])
		leftovers[fd] = (ft_strdup(""));
	if (!leftovers[fd])
		return (NULL);
	while (1)
	{
		final = find_newline(&leftovers[fd]);
		if (final)
			return (final);
		if (!leftovers[fd])
			return (NULL);
		bytes = read_line(&leftovers[fd], fd);
		if (bytes <= 0)
			return (test(&leftovers[fd], &final, bytes));
	}
}

/*int main(int argc, char **argv)
{
    int fd1, fd2;
    char *line1, *line2;
	if (argc != 3) // two input files are required
    {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return (EXIT_FAILURE);
    }    // open the first file
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0)
    {
        perror("Error opening file 1");
        return (EXIT_FAILURE);
    }    // open the second file
    fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0)
    {
        perror("Error opening file 2");
        close(fd1); // close the first file before leaving
        return (EXIT_FAILURE);
    }    // read from both files alternately
    while (1)
    {
        line1 = get_next_line(fd1);
        if (line1 != NULL)
        {
            printf("File1: %s\n", line1);
            free(line1);
        }        line2 = get_next_line(fd2);
        if (line2 != NULL)
        {
            printf("File2: %s\n", line2);
            free(line2);
        }
        if (line1 == NULL && line2 == NULL)
            break;
    }    close(fd1);
    close(fd2);
    return (EXIT_SUCCESS);
} */
