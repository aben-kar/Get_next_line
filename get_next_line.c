/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:36:07 by acben-ka          #+#    #+#             */
/*   Updated: 2024/12/17 17:06:18 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((char)c == *str)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*read_and_store(int fd, char *rem, char *buffer)
{
	ssize_t	byte;
	int		i;

	i = 0;
	byte = 1;
	while (byte > 0 && !ft_strchr(buffer, '\n'))
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		buffer[byte] = '\0';
		rem = ft_strjoin(rem, buffer);
		if (!rem)
			return (NULL);
	}
	if (byte < 0 || (!rem && byte == 0))
		return (NULL);
	return (rem);
}

char	*add_line(char *rem)
{
	int		i;
	char	*line;

	i = 0;
	if (!rem)
		return (NULL);
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] == '\n')
		i++;
	line = ft_calloc(i + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
	{
		line[i] = rem[i];
		i++;
	}
	if (rem[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*update_rem(char *rem)
{
	int		i;
	char	*new_rem;

	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] == '\n')
		i++;
	if (!rem[i])
	{
		free(rem);
		return (NULL);
	}
	new_rem = ft_strdup(rem + i);
	if (!new_rem)
	{
		free(rem);
		return (NULL);
	}
	free(rem);
	return (new_rem);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*buffer;
	char		*line;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	rem = read_and_store(fd, rem, buffer);
	free(buffer);
	if (!rem)
		return (NULL);
	line = add_line(rem);
	rem = update_rem(rem);
	return (line);
}
