/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_description.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:34:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/03 20:18:07 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 *	all_lines_are_valid()
 *	
 *	Checks the file line by line and rejects it when
 *		- a leading tab is found
 *		- any character different from 'NSEWFC01 ' is found
 *	
 */
boolean	all_lines_are_valid(t_data *data)
{
	int			fd;
	char		*line;

	fd = open(data->map.file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nOpen: Could not open '%s'\n", data->map.file);
		return (-1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_whitespace(line[0]) && line[0] != ' ')
		{
			free(line);
			printf("Error\nWhitespaces: Only simple spaces allowed as line leading characters \n");
			return (FALSE);
		}
		if ((line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W'
			&& line[0] != 'F' && line[0] != 'C' && line[0] != ' '
			&& line[0] != '1' && line[0] != '0' && line[0] != '\n')
			||((line[0] == 'N' && line[1] != 'O')
			|| (line[0] == 'S' && line[1] != 'O')
			|| (line[0] == 'E' && line[1] != 'A')
			|| (line[0] == 'W' && line[1] != 'E'))
			|| (((line[0] == 'N' && line[1] == 'O')
			|| (line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'E' && line[1] == 'A')
			|| (line[0] == 'W' && line[1] == 'E'))
			&& line[2] != ' '))
		{
			free(line);
			printf("Error\nFormat: Invalid characters found in the file\n");
			return (FALSE);
		}		
		free(line);
		line = get_next_line(fd);
	}
	read_until_end_of_file(fd, &line);
	free(line);
	close(fd);
	return (TRUE);
}

static boolean	is_map_empty(char *file)
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

static result	find_textures_and_colors(t_data *data)
{
	if (data->map.starting_line == 1)
	{
		if (data->map.height == find_file_length(data->map.file))
			printf("Error\nTextures/colors: Not defined in the file\n");
		else
			printf("Error\nMap: Wrong position (placed first in file)\n");
		return (FAIL);
	}
	return (SUCCESS);
}

static result	find_map(t_data *data)
{
	if (data->map.height == 0)
	{
		printf("Error\n Map: Not found in the file\n");
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
			printf("Error\nMap: Wrong position (not placed last in file)\n");
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
	if (all_lines_are_valid(data) == FALSE
		|| is_map_empty(data->map.file) == TRUE
		|| find_textures_and_colors(data) == FAIL
		|| find_map(data) == FAIL
		|| is_map_last(data) == FALSE)
		return (FAIL);
	return (SUCCESS);
}
