/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:48:50 by acben-ka          #+#    #+#             */
/*   Updated: 2024/12/09 23:31:34 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_store(int fd, char *rem, char *buffer)
{
	ssize_t	byte;
	int		i;

	i = 0;
	byte = read(fd, buffer, BUFFER_SIZE);
	while (byte > 0)
	{
		buffer[byte] = '\0';
		rem = ft_strjoin(rem, buffer);
		if (!rem)
			return (NULL);
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
	static char	*rem[1024];
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
	rem[fd] = read_and_store(fd, rem[fd], buffer);
	free(buffer);
	if (!rem[fd])
		return (NULL);
	line = add_line(rem[fd]);
	rem[fd] = update_rem(rem[fd]);
	return (line);
}

// int main()
// {
//     // int fd;
    // char *line;

    // fd = open("test.txt", O_CREAT | O_RDWR, 0644);
    // int fd2 = open("test2.txt", O_RDWR | O_CREAT, 0644);
    // int fd3 = open("test3.txt", O_RDWR | O_CREAT, 0644);
    // line = get_next_line(fd);
    // char *line2 = get_next_line(fd2);
    // char *line3 = get_next_line(fd3);
	// while (line || line2 || line3)
	// {
	// 	printf("%s", line);
    //     printf("%s", line2);
    //     printf("%s", line3);
	// 	free(line);
	// 	free(line2);
	// 	free(line3);
	// 	line = get_next_line(fd);
    //     line2 = get_next_line(fd2);
    //     line3 = get_next_line(fd3);
	// }
	
	// char *line;
	// int fd = open("test.txt", O_CREAT | O_RDWR, 0644);
	// line = get_next_line(fd);
    // printf("%s",line);
	// free(line);
	
// 	// char *line1;
// 	// int fd1 = open("test2.txt", O_CREAT | O_RDWR, 0644);
// 	// line1 = get_next_line(fd1);
//     // printf("%s",line1);
// 	// free(line1);

// 	// char *line2;
// 	// int fd2 = open("test3.txt", O_CREAT | O_RDWR, 0644);
// 	// line2 = get_next_line(fd2);
//     // printf("%s",line2);
// 	// free(line2);
	
// }