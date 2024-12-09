/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:36:07 by acben-ka          #+#    #+#             */
/*   Updated: 2024/12/09 17:05:32 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_store(int fd, char *rem, char *buffer)
{
	ssize_t	byte;
	char	*tmp;
	int		i;

	i = 0;
	byte = read(fd, buffer, BUFFER_SIZE);
	while (byte > 0)
	{
		buffer[byte] = '\0';
		tmp = ft_strjoin(rem, buffer);
		if (!tmp)
		{
			free(rem);
			return (NULL);
		}
		rem = tmp;
		if (rem[i] && rem[i] == '\n')
			break ;
		byte = read(fd, buffer, BUFFER_SIZE);
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
	if (!rem || !*rem)
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
		line[i++] = '\n';
	return (line);
}

char	*update_rem(char *rem)
{
	int		i;
	char	*new_rem;

	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i])
	{
		free(rem);
		return (NULL);
	}
	new_rem = ft_strdup(rem + i + 1);
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

// int main()
// {
//     int fd;
//     char *line;

//     fd = open("test.txt", O_CREAT | O_RDWR, 0644);
//     while (1) {
//         line = get_next_line(fd);
//         if (!line)
//             break;
//         printf("%s", line);
//         free(line);
//     }
//     // printf("%s", get_next_line(fd));
//     close(fd);
// }