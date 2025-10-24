/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-mal <kael-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:29:46 by kael-mal          #+#    #+#             */
/*   Updated: 2025/10/23 10:27:23 by kael-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_buffer(char *next_ret, char *buf, size_t newline_index, size_t bufsize)
{
	size_t	i;

	i = 0;
	next_ret = malloc(bufsize - newline_index + 1);
	if (!next_ret)
		return (0);
	while (newline_index++ < bufsize)
	{
		next_ret[i] = buf[newline_index];
		i++;
	}
	next_ret[i] = '\0';
	// free (buf);
	return (next_ret);
}

char	*ft_strjoinn(char *line, char *buf, size_t newline_index)
{
	size_t	i;
	size_t	line_len;
	char	*ret;

	i = 0;
	line_len = ft_strlen(line);
	ret = malloc(line_len + newline_index + 2);
	if (!ret)
		return (0);
	while (line[i])
	{
		ret[i] = line[i];
		i++;
	}
	free(line);
	i = 0;
	while (i <= newline_index)
	{
		ret[line_len] = buf[i];
		i++;
		line_len++;
	}
	ret[line_len] = '\0';
	// free(buf);
	return (ret);
}

char	*ft_strnjoin(char *line, char *buf, size_t bufsize)
{
	size_t	i;
	size_t	line_len;
	char	*ret;

	i = 0;
	line_len = ft_strlen(line);
	ret = malloc(line_len + bufsize + 1);
	if (!ret)
		return (0);
	while (i < line_len)
	{
		ret[i] = line[i];
		i++;
	}
	// free(line);
	i = 0;
	while (i < bufsize)
	{
		ret[line_len] = buf[i];
		i++;
		line_len++;
	}
	// free(buf);
	ret[line_len] = '\0';
	return (ret);
}

int	check_newline(char *line, size_t bufsize)
{
	size_t	i;

	i = 0;
	while (i < bufsize)
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*next_ret;
	size_t		bufsize;
	void		*buf[BUFFER_SIZE];
	int			newline_index;
	char		*ret;

	newline_index = -1;
	ret = malloc(1);
	ret[0] = 0;
	if (next_ret)
		ret = next_ret;
	bufsize = read(fd, buf, BUFFER_SIZE);
	newline_index = check_newline((char *)buf, bufsize);
	if (newline_index < 0)
	{
		ret = ft_strnjoin(ret, (char *)buf, bufsize);
		ret = get_next_line(fd);
	}
	ret = ft_strjoinn(ret, (char *)buf, (size_t)newline_index);
	next_ret = ft_buffer(next_ret, (char *)buf, newline_index, bufsize);
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
