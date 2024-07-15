/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_description2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:41:14 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/11 00:42:10 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_result	find_textures_and_colors(t_data *data)
{
	if (data->map.starting_line == 1)
	{
		if (data->map.height == find_file_length(data->map.file))
			printf("Error\nTextures/colors: Not defined in the file\n");
		else
			printf("Error\nMap: Wrong position (not placed last in file)\n");
		return (FAIL);
	}
	return (SUCCESS);
}

t_result	find_map(t_data *data)
{
	if (data->map.height == 0)
	{
		printf("Error\nMap: Not found in the file\n");
		return (FAIL);
	}
	return (SUCCESS);
}

t_boolean	is_map_empty(char *file)
{
	int		fd;
	char	*line;

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
		free(line);
		return (1);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

t_result	is_map_last(t_data *data)
{
	int		fd;
	char	*line;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	line = get_next_line(fd);
	read_until_line(fd, &line, data->map.ending_line + 1);
	while (line != NULL)
	{
		if (line[0] != '\n')
		{
			printf("Error\nMap: Wrong position (not placed last in file)\n");
			return (read_until_end_of_file(fd, &line, FAIL));
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}
