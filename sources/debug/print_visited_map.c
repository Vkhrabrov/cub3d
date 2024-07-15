/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_visited_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:01:43 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/08 19:42:51 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_checks(void)
{
	printf(GREEN " \u2714 " RESET);
	printf("Scene description check passed\n");
	printf(GREEN " \u2714 " RESET);
	printf("Textures check passed\n");
	printf(GREEN " \u2714 " RESET);
	printf("Colors check passed\n");
	printf(GREEN " \u2714 " RESET);
	printf("Player check passed\n");
	printf("Checking map...\n");
}

static char	*get_cell_color(t_data *data, size_t row, size_t column)
{
	char	cell;

	cell = data->map.visited[row][column];
	if (cell == '@')
	{
		if (data->map.visited[row - 1][column] == ' '
			|| data->map.visited[row][column + 1] == ' '
			|| data->map.visited[row + 1][column] == ' '
			|| data->map.visited[row][column - 1] == ' ')
			return (BCK_RED);
		else
			return (GREEN);
	}
	else if (cell == '0')
		return (RED);
	return (RESET);
}

void	print_visited_map(t_data *data)
{
	size_t	row;
	size_t	column;
	char	cell;
	char	*color;

	data->map.visited_height = data->map.height + 2;
	data->map.visited_width = data->map.width + 1;
	system("clear");
	display_checks();
	row = 0;
	while (row < data->map.visited_height)
	{
		column = 0;
		while (column < data->map.visited_width)
		{
			cell = data->map.visited[row][column];
			color = get_cell_color(data, row, column);
			printf("%s%c" RESET, color, cell);
			column++;
		}
		row++;
		printf("\n");
	}
}
