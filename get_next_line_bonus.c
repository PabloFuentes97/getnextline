/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/20 12:11:12 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_str_newline(char *str)
{
	int	cont;

	cont = 0;
	if (!str)
		return (0);
	while (str[cont])
	{
		if (str[cont] == '\n')
			return (1);
		cont++;
	}
	return (0);
}

char	*create_new_stash(char *stash)
{
	char	*new_stash;
	int		cont;

	if (!stash)
		return (NULL);
	cont = 0;
	new_stash = NULL;
	while (stash[cont] && stash[cont] != '\n')
		cont++;
	if (stash[cont + 1] == '\0' || stash[cont] == '\0')
		free (stash);
	else
	{
		new_stash = ft_substr(stash, cont + 1, (ft_strlen(stash)) - cont + 1);
		free (stash);
		if (!new_stash)
			return (NULL);
	}
	return (new_stash);
}

char	*create_line(char *stash)
{
	char	*line;
	size_t	cont;

	cont = 0;
	if (!stash)
		return (NULL);
	while (stash[cont] && stash[cont] != '\n')
		cont++;
	if (stash[cont] == '\n')
		line = ft_substr(stash, 0, cont + 1);
	else
		line = ft_strdup(stash);
	if (!line)
		return (NULL);
	return (line);
}

char	*create_stash(char *stash, int fd)
{
	char	*buf;
	int		bytes;

	buf = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && ft_str_newline(stash) == 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1 || buf == NULL)
			return (NULL);
		buf[bytes] = '\0';
		if (bytes > 0)
		{
			if (!stash)
				stash = ft_calloc(1, 1);
			stash = ft_strjoin(stash, buf);
		}
	}
	if (buf)
		free (buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	char static	*stash[257];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash[fd] = create_stash(stash[fd], fd);
	line = create_line(stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = create_new_stash(stash[fd]);
	return (line);
}
