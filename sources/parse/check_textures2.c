/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:06:41 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:28:29 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_result	store_texture_path(char *line, t_textures *textures)
{
	int		i;
	int		j;
	char	*trimmed_path;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(line, textures->texture_ids[i], 2) == 0)
		{
			if (*(textures->array[i]) != NULL)
			{
				printf("Error\nTextures: Two attempts to define %s texture\n",
					textures->texture_ids[i]);
				return (FAIL);
			}
			j = 2;
			while (line[j] == ' ')
				j++;
			trimmed_path = ft_strdup(line + j);
			*(textures->array[i]) = trimmed_path;
			break ;
		}
		i++;
	}
	return (SUCCESS);
}

t_result	create_textures_array(t_data *data, t_textures *textures)
{
	int		fd;
	char	*line;

	fd = open(data->map.file, O_RDONLY);
	if (fd < 0)
	{
		printf("Failed opening file\n");
		return (FAIL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		trim_and_reduce_spaces(line);
		if (store_texture_path(line, textures) == FAIL)
		{
			free(line);
			close(fd);
			return (FAIL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}

t_boolean	are_all_textures_defined(t_textures *textures)
{
	if (textures->north != NULL && textures->south != NULL
		&& textures->east != NULL && textures->west != NULL)
		return (TRUE);
	if (textures->north == NULL && textures->south == NULL
		&& textures->east == NULL && textures->west == NULL)
	{
		printf("Error\nTextures: Not defined in the file\n");
		return (FALSE);
	}
	if (textures->north == NULL)
		printf("Error\nTextures: North is missing in the file\n");
	if (textures->south == NULL)
		printf("Error\nTextures: South is missing in the file\n");
	if (textures->east == NULL)
		printf("Error\nTextures: East is missing in the file\n");
	if (textures->west == NULL)
		printf("Error\nTextures: West is missing in the file\n");
	return (FALSE);
}

t_boolean	are_texture_paths_valid(t_textures *textures)
{
	int		i;
	int		fd;
	char	*path;

	i = 0;
	while (i < 4)
	{
		path = *(textures->array[i]);
		fd = open(path, O_DIRECTORY);
		if (fd >= 0)
		{
			close(fd);
			printf("Error\nOpen: '%s' is a directory, not a file\n", path);
			return (FALSE);
		}
		fd = open(path, O_RDONLY);
		if (fd < 0)
		{
			printf("Error\nOpen: Cannot open '%s'\n", path);
			return (FALSE);
		}
		close(fd);
		i++;
	}
	return (TRUE);
}

t_boolean	are_textures_unique(t_textures *textures)
{
	size_t	len0;
	size_t	len1;
	size_t	len2;

	len0 = ft_strlen(*(textures->array[0]));
	len1 = ft_strlen(*(textures->array[1]));
	len2 = ft_strlen(*(textures->array[2]));
	if (!ft_strncmp(*(textures->array[0]), *(textures->array[1]), len0)
		|| !ft_strncmp(*(textures->array[0]), *(textures->array[2]), len0)
		|| !ft_strncmp(*(textures->array[0]), *(textures->array[3]), len0)
		|| !ft_strncmp(*(textures->array[1]), *(textures->array[2]), len1)
		|| !ft_strncmp(*(textures->array[1]), *(textures->array[3]), len1)
		|| !ft_strncmp(*(textures->array[2]), *(textures->array[3]), len2))
	{
		printf("Error\nTextures: Must be different for every orientation\n");
		return (FALSE);
	}
	return (TRUE);
}
