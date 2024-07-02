/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_description.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:34:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/30 20:51:34 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static boolean	is_map_empty(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: could not open the file\n");
		return (-1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("Error: file is empty\n");
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

static result	find_textures_and_colors(t_data *data)
{
	if (data->map.starting_line == 1)
	{
		if (data->map.height == find_file_length(data->map.file))
			printf("Error: Textures and colors not defined in the file\n");
		else
			printf("Error: Wrong map position (placed first in file)\n");
		return (FAIL);
	}
	return (SUCCESS);
}

static result	find_map(t_data *data)
{
	if (data->map.height == 0)
	{
		printf("Error: No map found in the file\n");
		return (FAIL);
	}
	return (SUCCESS);
}

static boolean	is_map_last(t_data *data)
{
	int		fd;
	char	*line;
	int		map_end_line;
	int		flag;

	flag = TRUE;
	fd = open_file(data->map.file);
	if (fd < 0)
		return (FALSE);
	line = get_next_line(fd);
	map_end_line = data->map.starting_line + data->map.height;
	read_until_line(fd, &line, map_end_line + 1);
	while (line != NULL && flag == TRUE)
	{
		if (line[0] != '\n')
		{
			printf("Error: Wrong map position (not placed last in file)\n");
			flag = FALSE;
		}
		free(line);
		line = get_next_line(fd);
	}
	read_until_end_of_file(fd, &line);
	close(fd);
	return (flag);
}

result	check_scene_description(t_data *data)
{
	if (is_map_empty(data->map.file) == TRUE
		|| find_textures_and_colors(data) == FAIL
		|| find_map(data) == FAIL
		|| is_map_last(data) == FALSE)
		return (FAIL);
	return (SUCCESS);
}
