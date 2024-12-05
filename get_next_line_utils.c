#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (num != 0 && (18446744073709551615UL / num < size))
		return (NULL);
	total_size = num * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*concate;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		s2 = ft_calloc(1, sizeof(char));

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	concate = (char *)ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (concate == NULL)
		return (NULL);

	ft_memcpy(concate, s1, len_s1);
	ft_memcpy(concate + len_s1, s2, len_s2);
	free(s1);
	return (concate);
}


char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)ft_calloc((len + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	return (ptr);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	len_s;
// 	char	*dest;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	len_s = ft_strlen(s);
// 	if (start >= len_s)
// 		return (ft_strdup(""));
// 	if (start + len > len_s)
// 		len = len_s - start;
// 	dest = (char *)malloc((len + 1) * sizeof(char));
// 	if (dest == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s[start + i] && i < len)
// 	{
// 		dest[i] = s[start + i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }


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


// char *merged(const char *s , int c , int mode)//si 1 for strchr , 0 strdup 
// {
// 	if(mode == 0)
// 	{
// 		//strchr
// 			if (!s)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if ((char)c == *s)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// 	}else
// 	{
// 		//strdup 
// 	size_t	len;
// 	char	*ptr;

// 	if (!s)
// 		return (NULL);
// 	len = ft_strlen(s);
// 	ptr = (char *)ft_calloc((len + 1), sizeof(char));
// 	if (ptr == NULL)
// 		return (NULL);
// 	ft_memcpy(ptr, s, len);
// 	return (ptr);
// 	}
// }