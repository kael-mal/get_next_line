#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(char *s)
{
	size_t	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_append(char **ret, void *buf, size_t bufsize)
{
	size_t	retlen = ft_strlen(*ret);
	char	*new;
	size_t	i = 0, j = 0;
	char	*buff = (char *)buf;

	new = malloc(retlen + bufsize + 1);
	if (!new)
		return (NULL);

	while (j < retlen)
	{
		new[j] = (*ret)[j];
		j++;
	}
	while (i < bufsize)
		new[j++] = buff[i++];
	new[j] = '\0';

	free(*ret);
	*ret = new;
	return (new);
}

int	check(char *s)
{
	int	i = 0;
	while (s && s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}

char	*makesave(char **s)
{
	size_t	i = 0, j = 0;
	char	*ret;

	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if (!(*s)[i])
		return (NULL);
	ret = malloc(ft_strlen(*s) - i);
	if (!ret)
		return (NULL);
	i++;
	while ((*s)[i])
		ret[j++] = (*s)[i++];
	ret[j] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bufsize;
	char	*ret = NULL;
	static char	*save;

	if (save)
		ret = ft_append(&ret, save, ft_strlen(save));
	while (!check(ret))
	{
		bufsize = read(fd, buf, BUFFER_SIZE);
		if (bufsize <= 0)
			break;
		buf[bufsize] = '\0';
		ret = ft_append(&ret, buf, bufsize);
	}
	free(save);
	save = makesave(&ret);
	return (ret);
}

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}