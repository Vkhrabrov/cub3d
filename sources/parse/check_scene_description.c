/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_description.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:34:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_boolean	is_invalid_whitespace(char *line)
{
	if (is_whitespace(line[0]) && line[0] != ' ')
	{
		printf("Error\nWhitespaces: tabs leading lines not allowed \n");
		return (TRUE);
	}
	return (FALSE);
}

static t_boolean	contains_invalid_characters(char *line)
{
	if ((line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W'
			&& line[0] != 'F' && line[0] != 'C' && line[0] != ' '
			&& line[0] != '1' && line[0] != '0' && line[0] != '\n')
		|| ((line[0] == 'N' && line[1] != 'O')
			|| (line[0] == 'S' && line[1] != 'O')
			|| (line[0] == 'E' && line[1] != 'A')
			|| (line[0] == 'W' && line[1] != 'E'))
		|| (((line[0] == 'N' && line[1] == 'O')
				|| (line[0] == 'S' && line[1] == 'O')
				|| (line[0] == 'E' && line[1] == 'A')
				|| (line[0] == 'W' && line[1] == 'E'))
			&& line[2] != ' '))
	{
		printf("Error\nFormat: Invalid characters found in the file\n");
		return (TRUE);
	}
	return (FALSE);
}

/*
 *	all_lines_are_valid()
 *	
 *	Checks the file line by line and rejects it when
 *		- a leading tab is found
 *		- any character different from 'NSEWFC01 ' is found
 *	
 */
t_boolean	all_lines_are_valid(t_data *data)
{
	int			fd;
	char		*line;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FALSE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_invalid_whitespace(line) || contains_invalid_characters(line))
		{
			read_until_end_of_file(fd, &line);
			return (FALSE);
		}
		free(line);
		line = get_next_line(fd);
	}
	read_until_end_of_file(fd, &line);
	return (TRUE);
}

t_result	check_scene_description(t_data *data)
{
	if (all_lines_are_valid(data) == FALSE
		|| is_map_empty(data->map.file) == TRUE
		|| find_textures_and_colors(data) == FAIL
		|| find_map(data) == FAIL
		|| is_map_last(data) == FALSE)
		return (FAIL);
	return (SUCCESS);
}
