#include <unistd.h> // Pour read
#include <stdlib.h> // Pour malloc et free
#include <fcntl.h>  // Pour open
#include <stdio.h>  // Pour debug avec printf

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// **Prototype des fonctions**
char    *get_next_line(int fd);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_strdup(const char *s);
char    *ft_substr(const char *s, unsigned int start, size_t len);
char    *ft_strchr(const char *s, int c);
size_t  ft_strlen(const char *s);

// **Fonction principale**
char *get_next_line(int fd) {
    static char *remainder = NULL; // Pour stocker les données non traitées
    char buffer[BUFFER_SIZE + 1];
    char *line;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';
        char *temp = ft_strjoin(remainder, buffer); // Ajouter ce qui a été lu
        if (!temp) {
            free(remainder);
            return NULL;
        }
        remainder = temp;
        if (ft_strchr(remainder, '\n')) // Vérifie si une ligne est complète
            break;
    }

    if (!remainder || *remainder == '\0') {
        free(remainder);
        remainder = NULL;
        return NULL;
    }

    // Extraire la ligne jusqu'au '\n'
    char *newline_pos = ft_strchr(remainder, '\n');
    if (newline_pos) {
        line = ft_substr(remainder, 0, newline_pos - remainder + 1);
        if (!line) {
            free(remainder);
            return NULL;
        }
        char *new_remainder = ft_strdup(newline_pos + 1);
        if (!new_remainder) {
            free(remainder);
            free(line);
            return NULL;
        }
        free(remainder);
        remainder = new_remainder;
    } else {
        line = ft_strdup(remainder);
        free(remainder);
        remainder = NULL;
        if (!line) return NULL;
    }

    return line;
}

// **Fonctions Utilitaires**
char *ft_strjoin(char *s1, char *s2) {
    if (!s1 && !s2) return NULL;
    if (!s1) return ft_strdup(s2);
    if (!s2) return ft_strdup(s1);

    size_t len1 = ft_strlen(s1), len2 = ft_strlen(s2);
    char *joined = malloc(len1 + len2 + 1);
    if (!joined) return NULL;

    size_t i = 0;
    for (; i < len1; i++) joined[i] = s1[i];
    for (size_t j = 0; j < len2; j++) joined[i++] = s2[j];
    joined[i] = '\0';

    free(s1); // Libère l'ancien contenu de s1
    return joined;
}

char *ft_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = ft_strlen(s);
    char *dup = malloc(len + 1);
    if (!dup) return NULL;

    for (size_t i = 0; i < len; i++) dup[i] = s[i];
    dup[len] = '\0';
    return dup;
}

char *ft_substr(const char *s, unsigned int start, size_t len) {
    if (!s) return NULL;
    size_t s_len = ft_strlen(s);
    if (start >= s_len) return ft_strdup("");

    size_t substr_len = (s_len - start < len) ? s_len - start : len;
    char *substr = malloc(substr_len + 1);
    if (!substr) return NULL;

    for (size_t i = 0; i < substr_len; i++) substr[i] = s[start + i];
    substr[substr_len] = '\0';
    return substr;
}

char *ft_strchr(const char *s, int c) {
    if (!s) return NULL;
    while (*s) {
        if (*s == (char)c) return (char *)s;
        s++;
    }
    return (c == '\0') ? (char *)s : NULL;
}

size_t ft_strlen(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

// #include <stdio.h>
// #//include "get_next_line_bonus.h"

// int main(int ac, char **av)
// {
//     int fd, fd1, fd2;
//     (void)ac;

//     fd = open(av[1], O_RDONLY);
//     fd1 = open(av[2], O_RDONLY);
//     fd2 = open(av[3], O_RDONLY);

//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd1));
//     printf("%s", get_next_line(fd2));

//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd1));
//     printf("%s", get_next_line(fd2));

//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd1));
//     printf("%s", get_next_line(fd2));

//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd1));
//     printf("%s", get_next_line(fd2));

//     close(fd);
//     close(fd1);
//     close(fd2);

//     return 0;
// }
