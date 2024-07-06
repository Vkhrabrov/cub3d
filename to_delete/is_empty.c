#include <stdio.h>
#include "../libraries/libft/libft.h"

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

int is_empty(char *file)
{
	int		fd;
	char 	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nOpen: Could not open '%s'\n", file);
		return (-1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("Error\nOpen: File is empty\n");
		close(fd);
		return (1);
	}
	free(line);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		is_empty(argv[1]);
	return (0);
}


static char	*ft_extract_remainder(char *depot)
{
	int		i;
	char	*remainder;

	i = 0;
	while (depot[i] != '\n' && depot[i] != '\0')
		i++;
	if (depot[i] != '\0' && depot[i] == '\n')
		i++;
	remainder = ft_substr(depot, i, ft_strlen(depot) - i);
	if (!remainder || *remainder == '\0')
	{
		free (remainder);
		remainder = NULL;
	}
	return (remainder);
}

static char	*ft_extract_line(char *depot)
{
	int		i;
	char	*line;

	i = 0;
	while (depot[i] != '\n' && depot[i] != '\0')
		i++;
	if (depot[i] != '\0' && depot[i] == '\n')
		i++;
	line = ft_substr(depot, 0, i);
	if (!line || *line == '\0')
	{
		free (line);
		line = NULL;
	}
	return (line);
}

static char	*ft_load_data(int fd, char *buffer, char *depot)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (0);
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (!depot)
			depot = ft_strdup("");
		temp = ft_strdup(depot);
		free(depot);
		depot = NULL;
		depot = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (depot);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char static	*depot;
	char		*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (!buffer)
		return (NULL);
	store = ft_load_data(fd, buffer, depot);
	free(buffer);
	buffer = NULL;
	if (!store || *store == '\0')
	{
		free(depot);
		depot = NULL;
		return (NULL);
	}
	line = ft_extract_line(store);
	depot = ft_extract_remainder(store);
	free (store);
	store = NULL;
	return (line);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		substr = malloc(sizeof(char));
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		count;
	int		i;

	count = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * count);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}