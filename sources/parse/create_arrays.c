/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:05:56 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/03 20:17:27 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	allocate_map_array(t_data *data)
{
	size_t	i;

	data->map.array = malloc((data->map.height) * sizeof(char *));
	if (!data->map.array)
	{
		printf("Error\nMalloc: Could not allocate memory for map\n");
		return ;
	}
	i = 0;
	while (i < data->map.height)
	{
		data->map.array[i] = malloc((data->map.width + 1) * sizeof(char));
		if (!data->map.array[i])
		{
			printf("Error\nMalloc: Could not allocate memory for map\n");
			return ;
		}
		i++;
	}
	// return (data->map.array);
}

static result fill_map_array(t_data *data)
{
    int     fd;
    char    *line;
    size_t  len;

	fd = open_file(data->map.file);
    if (fd < 0)
        return (FAIL);
    line = get_next_line(fd);
    // data->map.i = 1;
    // while (data->map.i < data->map.starting_line)
    // {
    //     free(line);
    //     line = get_next_line(fd);
    //     data->map.i++;
    // }
	read_until_line(fd, &line, data->map.starting_line);
	data->map.i = 0;
    while (line && data->map.i < data->map.height)
    {
        data->map.j = 0;
        // Ensure line does not contain a newline at the end
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        // Copy characters to data->map.array, handling shorter lines
        while (data->map.j < data->map.width)
        {
            if (data->map.j < len && line[data->map.j] != '\0')
                data->map.array[data->map.i][data->map.j] = line[data->map.j];
            else
                data->map.array[data->map.i][data->map.j] = '\0';
            data->map.j++;
        }
		data->map.array[data->map.i][data->map.width] = '\0';
        free(line);
        line = get_next_line(fd);
        data->map.i++;
    }
	// while (line != NULL)
	// {
	// 	free(line);
	// 	line = get_next_line(fd);		
	// }
	read_until_end_of_file(fd, &line);
    free(line);
    close(fd);
    return (SUCCESS);
}

void	allocate_visited_array(t_data *data)
{
    size_t i;

	data->map.visited_array = malloc((data->map.height + 2) * sizeof(char *));
	if (!data->map.visited_array)
	{
		printf("Error\nMalloc: Could not allocate memory for visited_map\n");
		return ;
	}
	i = 0;
    while (i < data->map.height + 2)
	{
        data->map.visited_array[i] = malloc((data->map.width + 2) * sizeof(char));
        if (!data->map.visited_array[i])
		{
			printf("Error\nMalloc: Could not allocate memory for visited_map\n");
            while (i > 0)
                free(data->map.visited_array[--i]);
            free(data->map.visited_array);
            return;
        }
        ft_memset(data->map.visited_array[i], ' ', (data->map.width + 1));
		data->map.visited_array[i][data->map.width + 1] = '\0'; // Set the last character to null-terminator
		i++;
    }
}

static void	fill_visited_array(t_data *data)
{
	size_t	i;
	size_t	j;

    i = 0;
	while (i < data->map.height)
	{
		j = 0;
        while (j < data->map.width)
		{
            // Copy each character except the null-terminator
            if (data->map.array[i][j] != '\0')
                data->map.visited_array[i + 1][j + 1] = data->map.array[i][j];
            j++;
        }
		i++;
    }
}

result	create_arrays(t_data *data)
{
	allocate_map_array(data);
    if (fill_map_array(data) == FAIL)
		return (FAIL);
	allocate_visited_array(data);
	fill_visited_array(data);
	return (SUCCESS);
}