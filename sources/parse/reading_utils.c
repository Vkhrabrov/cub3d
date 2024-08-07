/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:55:28 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/10 20:30:33 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
 *	These are just snippets of code to shorten the functions that open and read
 *	a file and need to move to specific lines or sections
 */

#include "cub3d.h"

int	open_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		printf("Error\nOpen: Could not open '%s'\n", file_path);
	return (fd);
}

void	read_until_line(int fd, char **line, int target_line)
{
	int	i;

	i = 0;
	while (i < target_line && *line != NULL)
	{
		i++;
		if (i < target_line)
		{
			free(*line);
			*line = get_next_line(fd);
		}
	}
}

t_result	read_until_end_of_file(int fd, char **line, t_result res)
{
	while (*line != NULL)
	{
		free(*line);
		*line = get_next_line(fd);
	}
	close(fd);
	return (res);
}
