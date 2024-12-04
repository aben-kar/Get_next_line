#include "get_next_line.h"

char *get_next_line(int fd) {
    static char *remainder = NULL;
    char buffer[BUFFER_SIZE + 1];
    char *line;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';
        char *temp = ft_strjoin(remainder, buffer);
        if (!temp)
        {
            free(remainder);
            return NULL;
        }
        remainder = temp;
        if (ft_strchr(remainder, '\n'))
            break;
    }

    if (!remainder || *remainder == '\0') {
        free(remainder);
        remainder = NULL;
        return NULL;
    }

    char *newline_pos = ft_strchr(remainder, '\n');
    if (newline_pos)
    {
        line = ft_substr(remainder, 0, newline_pos - remainder + 1);
        if (!line)
        {
            free(remainder);
            return NULL;
        }
        char *new_remainder = ft_strdup(newline_pos + 1);
        if (!new_remainder)
        {
            free(remainder);
            free(line);
            return NULL;
        }
        free(remainder);
        remainder = new_remainder;
    }
    else
    {
        line = ft_strdup(remainder);
        free(remainder);
        remainder = NULL;
        if (!line)
            return NULL;
    }
    return line;
}

#include <fcntl.h>


int main()
{
    int fd;
    char *line; 

    fd = open("test.txt", O_CREAT | O_RDWR, 0644);
    while (1) {
        line = get_next_line(fd);
        if (!line)
            break;
        printf("%s", line);
        free(line);
    }

    close(fd);
}