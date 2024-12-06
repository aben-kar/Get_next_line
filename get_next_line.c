#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *rem;
    char buffer[BUFFER_SIZE + 1];
    char *line;
    size_t byte;
    char *tmp;
    int i;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
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

        if (ft_strchr(rem, '\n'))
            break;
        byte = read(fd, buffer, BUFFER_SIZE);
    }

    if (byte < 0 || (!rem && byte == 0))
        return NULL;

    i = 0;
    while (rem[i] && rem[i] != '\n')
        i++;

    line = ft_calloc(i + 2, 1);
    if (!line)
    {
        free(rem);
        return (NULL);
    }

    i = 0;
    while (rem[i] && rem[i] != '\n')
    {
        line[i] = rem[i];
        i++;
    }

    if (rem[i] == '\n')
    {
        line[i] = '\n';
        i++;
    }
    line[i] = '\0';


    tmp = ft_strdup(rem + i);
    free(rem);
    rem = tmp;

    if (!rem || !*rem)
    {
        free(rem);
        rem = NULL;
    }

    return line;
}


int main()
{
    int fd;
    char *line; 

    fd = open("get.txt", O_CREAT | O_RDWR, 0644);
    while (1) {
        line = get_next_line(fd);
        if (!line)
            break;
        printf("%s", line);
        free(line);
    }
    close(fd);
}