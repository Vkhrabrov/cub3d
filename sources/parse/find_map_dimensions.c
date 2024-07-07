/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map_dimensions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:47:31 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_result	find_map_starting_line(t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (is_whitespace(line[i]))
			i++;
		if (line[i] != '0' && line[i] != '1')
			++data->map.starting_line;
		else
			break ;
		free(line);
		line = get_next_line(fd);
	}
	read_until_end_of_file(fd, &line);
	return (SUCCESS);
}

static t_result	find_map_height(t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	line = get_next_line(fd);
	read_until_line(fd, &line, data->map.starting_line);
	while (line && line[0] != '\n')
	{
		i = 0;
		while (is_whitespace(line[i]))
			i++;
		if (line[i] == '1' || line[i] == '0')
			++data->map.height;
		free(line);
		line = get_next_line(fd);
	}
	read_until_end_of_file(fd, &line);
	return (SUCCESS);
}

static t_result	find_map_width(t_data *data)
{
	int		fd;
	char	*line;
	size_t	len;

	data->map.i = 0;
	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	while (data->map.i++ < data->map.starting_line)
	{
		line = get_next_line(fd);
		if (data->map.i < data->map.starting_line)
			free(line);
	}
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > data->map.width)
			data->map.width = len;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (SUCCESS);
}

t_result	find_map_dimensions(t_data *data)
{
	if (find_map_starting_line(data) == FAIL
		|| find_map_width(data) == FAIL
		|| find_map_height(data) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
