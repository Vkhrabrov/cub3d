/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:30:37 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/03 20:18:36 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_file_type_valid(char *filename, char *expected_extension)
{
	size_t	len;
	char	*file_extension;

	len = ft_strlen(filename);
	file_extension = ft_substr(filename, len - 4, 4);
	if (ft_strncmp(file_extension, expected_extension, 4) != 0)
	{
		free(file_extension);
		return (0);
	}
	free(file_extension);
	return (1);
}

void	free_array(char **array, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_rgb_values(char **rgb_array)
{
	int	i;

	i = 0;
	while (rgb_array[i] != NULL)
	{
		free(rgb_array[i]);
		i++;
	}
	free(rgb_array);
}

int is_valid_number(const char *str)
{
    if (*str == '\0')
        return (0);
    while (*str)
    {
        if (!ft_isdigit((unsigned char)*str) && *str != '\n')
            return (0);
        str++;
    }
    return (1);
}

size_t	find_file_length(char *file)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nOpen: Could not open '%s'\n", file);
		return (-1);
	}
	len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		len++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (len);
}
