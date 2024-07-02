/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:15:09 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/21 19:32:28 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define MAGENTA "\033[0;35m"
# define RESET "\x1B[0m"

#include "floodfill.h"
#include <unistd.h>

void	print_map(char **map_array, int map_height, int map_width)
{
	int	row = 0;
	system("clear");
	
	while (row < map_height)
	{
		int	column = 0;
		while (column < map_width)
		{
			if (map_array[row][column] == '@')
				printf(MAGENTA "%c" RESET, map_array[row][column]);
			else
				printf("%c", map_array[row][column]);
			column++;			
		}
		row++;
		printf("\n");
	}
	printf("\n");
}

// void	fill(char **tab, t_point size, t_point cur, char to_fill)
void	fill(char **map_array, int row, int column, int map_height, int map_width)
{
	if ( row < 0 || row >= map_height || column < 0 || column >= map_width 
		|| map_array[row][column] == ' ' || map_array[row][column] == '1' || map_array[row][column] == '@' )
		return;

	map_array[row][column] = '@';
	usleep(300000);
	print_map(map_array, map_height, map_width);
	
	fill(map_array, row -1, column, map_height, map_width);
	fill(map_array, row, column + 1, map_height, map_width);
	fill(map_array, row + 1, column, map_height, map_width);
	fill(map_array, row, column - 1, map_height, map_width);
}
 
int	is_closed(char **map_array, int map_height, int map_width)
{
	int	row;
	int	column;

	row = 0;
	while (row < map_height)
	{
		column = 0;
		while (column < map_width)
		{
			if (map_array[row][column] == '@')
			{
				if ((row > 0 && map_array[row - 1][column] == ' ')
					|| (row < (map_height - 1) && map_array[row + 1][column] == ' ')
					|| (column > 0 && map_array[row][column - 1] == ' ')
					|| (column < (map_width - 1) && map_array[row][column + 1] == ' '))
					return (0);
			}
			column++;
		}
		row++;
	}
	return (1);
}

int	has_non_reachable_areas(char **map_array, int map_height, int map_width)
{
	int	row;
	int	column;

	row = 0;
	while (row < map_height)
	{
		column = 0;
		while (column < map_width)
		{
			if (map_array[row][column] == '0')
				return (0);
			column++;
		}
		row++;
	}
	return (1);
}
