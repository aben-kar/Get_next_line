#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *rem = NULL;
    char buffer[BUFFER_SIZE];
    char *line;
    size_t byte;
    char *tmp;
    int i;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    // byte = read(fd, buffer, BUFFER_SIZE);
    while ((byte = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (byte < 0)
            return(NULL);
        buffer[byte] = '\0';
        tmp = ft_strjoin(rem, buffer);
        if (!tmp)
        {
            free(rem);
            return (NULL);
        }
        free(rem);
        rem = tmp;
        int i = 0;
        if (rem[i] && rem[i] == '\n')
            break;
    }

    if (byte < 0 || (!rem && byte == 0)) // endena error f read || male9a maye9ra f dak l file (EOF).
        return NULL;

    i = 0;
    while (rem[i] && rem[i] != '\n')
        i++;
    line = malloc(i + 2);
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

    tmp = ft_strdup(rem + i); //update rem bach readiw line jaya
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