/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arrays2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:37:02 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/10 21:38:38 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_map_array(t_data *data)
{
	size_t	i;

	data->map.array = malloc(data->map.height * sizeof(char *));
	if (!data->map.array)
	{
		printf("Error\nMalloc: Could not allocate memory for map\n");
		return (0);
	}
	i = 0;
	while (i < data->map.height)
	{
		data->map.array[i] = malloc((data->map.width + 1) * sizeof(char));
		if (!data->map.array[i])
		{
			printf("Error\nMalloc: Could not allocate memory for map row\n");
			while (i > 0)
				free(data->map.array[--i]);
			free(data->map.array);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	process_line(t_data *data, char *line)
{
	size_t	len;

	data->map.j = 0;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	while (data->map.j < data->map.width)
	{
		if (data->map.j < len && line[data->map.j] != '\0')
			data->map.array[data->map.i][data->map.j] = line[data->map.j];
		else
			data->map.array[data->map.i][data->map.j] = '\0';
		data->map.j++;
	}
	data->map.array[data->map.i][data->map.width] = '\0';
}

t_result	fill_map_array(t_data *data)
{
	int		fd;
	char	*line;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	line = get_next_line(fd);
	read_until_line(fd, &line, data->map.starting_line);
	data->map.i = 0;
	while (line && data->map.i < data->map.height)
	{
		process_line(data, line);
		free(line);
		line = get_next_line(fd);
		data->map.i++;
	}
	return (read_until_end_of_file(fd, &line, SUCCESS));
}

int	allocate_visited(t_data *data)
{
	data->map.visited = malloc((data->map.height + 2) * sizeof(char *));
	if (!data->map.visited)
	{
		printf("Error\nMalloc: Could not allocate memory for visited_map\n");
		return (0);
	}
	data->map.i = 0;
	while (data->map.i < data->map.height + 2)
	{
		data->map.visited[data->map.i] = malloc((data->map.width + 2)
				* sizeof(char));
		if (!data->map.visited[data->map.i])
		{
			printf("Error\nMalloc: Couldn't allocate memory for visited_map\n");
			while (data->map.i > 0)
				free(data->map.visited[--(data->map.i)]);
			free(data->map.visited);
			return (0);
		}
		ft_memset(data->map.visited[data->map.i], ' ', (data->map.width + 1));
		data->map.visited[data->map.i][data->map.width + 1] = '\0';
		data->map.i++;
	}
	return (1);
}

void	fill_visited(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.array[i][j] != '\0')
				data->map.visited[i + 1][j + 1] = data->map.array[i][j];
			j++;
		}
		i++;
	}
}
