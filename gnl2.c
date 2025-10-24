#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_append(char **ret, void *buf, size_t bufsize)
{
	size_t	i;
	size_t	retlen;
	char	*retret;
	char	*buff;

	buff = (char *)buf;
	i = 0;
	if (!*ret)
	{
		*ret = malloc(bufsize + 1);
		if (!*ret)
			return (NULL);
	}
	retlen = ft_strlen(*ret);
	retret = malloc (retlen + bufsize + 1);
	if (!retret)
		return (NULL);
	while ((*ret)[i])
	{
		retret[i] = (*ret)[i];
		i++;
	}
	i = 0;
	while (i < bufsize)
	{
		retret[retlen] = buff[i];
		retlen++;
		i++;
	}
	retret[retlen] = '\0';
	free(*ret);
	return (retret);
}

int	check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*makesave(char **s)
{
	size_t	i;
	size_t	j;
	char	*ret;

	i = 0;
	j = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\n')
		{
			ret = malloc(ft_strlen(*s) - i + 1);
			if (!ret)
				return (NULL);
			i++;
			while ((*s)[i])
			{
				ret[j] = (*s)[i];
				(*s)[i] = '\0';
				i++;
				j++;
			}
		}
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	void	*buf[BUFFER_SIZE + 1];
	size_t	bufsize;
	char	*ret;
	static char	*save;

	if (save)
		ret = ft_append(&ret, (void *)save, ft_strlen(save));
	bufsize = read(fd, buf, BUFFER_SIZE);
	ret = ft_append(&ret, buf, bufsize);
	if (!check(ret))
		get_next_line(fd);
	save = makesave(&ret);
	return (ret);
}

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
}
