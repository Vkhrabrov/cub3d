/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:44 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/30 20:53:10 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void		trim_last_char(char *path);
// static result 	store_texture_path(char *line, t_textures *textures);
// static result	create_textures_array(t_map *map, t_textures *textures);
// static boolean	are_all_textures_defined(t_textures *textures);
// static boolean	are_texture_paths_valid(t_textures *textures);
// result			check_textures(t_map *map, t_textures *textures);

// static void	trim_last_char(char *path)
// {
// 	int		len;

// 	len = ft_strlen(path);
// 	if (len > 0 && path[len - 1] == '\n')
// 		path[len - 1] = '\0';
// }

static result	store_texture_path(char *line, t_textures *textures)
{
    int i = 0;
    int j;
    char *trimmed_path;

    while (i < 4)
    {
        if (ft_strncmp(line, textures->texture_ids[i], 2) == 0)
        {
            if (*(textures->paths_array[i]) != NULL)
            {
                printf("Error: Two %s textures in the file\n", \
					textures->texture_ids[i]);
                return (FAIL);
            }
            j = 2;
            while (line[j] == ' ')
                j++;
            trimmed_path = ft_strdup(line + j);
            // trim_last_char(trimmed_path);
            *(textures->paths_array[i]) = trimmed_path;
            break;
        }
        i++;
    }
    return (SUCCESS);
}

static result	create_textures_array(t_data *data, t_textures *textures)
{
    int fd;
    char *line;

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

static boolean	are_all_textures_defined(t_textures *textures)
{
    if (textures->north != NULL && textures->south != NULL
        && textures->east != NULL && textures->west != NULL)
        return (TRUE);
    if (textures->north == NULL && textures->south == NULL
        && textures->east == NULL && textures->west == NULL)
    {
        printf("Error: No textures defined in the file\n");
        return (FALSE);
    }    
    if (textures->north == NULL)
        printf("Error: North texture is missing in the file\n");
    if (textures->south == NULL)
        printf("Error: South texture is missing in the file\n");
    if (textures->east == NULL)
        printf("Error: East texture is missing in the file\n");
    if (textures->west == NULL)
        printf("Error: West texture is missing in the file\n");
    return (FALSE);
}

static boolean	are_texture_paths_valid(t_textures *textures)
{
	int i;
	int fd;
	char *path;
	
	i = 0;
	while (i < 4)
	{
    	path = *(textures->paths_array[i]);
    	fd = open(path, O_DIRECTORY);
    	if (fd >= 0)
		{
			close(fd);
      		printf("Error: '%s' is a directory\n", path);
      		return (FALSE);  // Early exit on error
    	}
    	fd = open(path, O_RDONLY);
    	if (fd < 0)
		{
      		printf("Error: Cannot open '%s'\n", path);
      		return (FALSE);  // Early exit on error
    	}
    	close(fd);
    	i++;
  	}
	return (TRUE);
}

result	check_textures(t_data *data, t_textures *textures)
{
	if (create_textures_array(data, textures) == FAIL)
		return (FAIL);
	if (are_all_textures_defined(textures) == FALSE)
		return (FAIL);
	if (are_texture_paths_valid(textures) == FALSE)
		return (FAIL);
	return (SUCCESS);
}
