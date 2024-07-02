/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:41 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/01 20:02:45 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_visited_map(t_data *data)
{
	size_t	row;
	size_t	column;
	
	data->map.visited_height = data->map.height + 2;
	data->map.visited_width = data->map.width + 1;	
	row = 0;
	system("clear");

	printf(GREEN " \u2714 " RESET);
	printf("Scene description check passed\n");
	printf(GREEN " \u2714 " RESET);
	printf("Textures check passed\n");
	printf(GREEN " \u2714 " RESET);
	printf("Colors check passed\n");
	printf(GREEN " \u2714 " RESET);
	printf("Player check passed\n");
	printf("Checking map...\n");
	
	while (row < data->map.visited_height)
	{
		column = 0;
		while (column < data->map.visited_width)
		{
			if (data->map.visited_array[row][column] == '@')
			{
				if ((data->map.visited_array[row - 1][column] == ' ') || (data->map.visited_array[row][column + 1] == ' ')
					|| (data->map.visited_array[row + 1][column] == ' ') || (data->map.visited_array[row][column - 1] == ' '))
					printf(BCK_RED "%c" RESET, data->map.visited_array[row][column]);				
				else
					printf(GREEN "%c" RESET, data->map.visited_array[row][column]);
			}
			else if (data->map.visited_array[row][column] == '0')
				printf(RED "%c" RESET, data->map.visited_array[row][column]);
			else
				printf("%c", data->map.visited_array[row][column]);
			column++;			
		}
		row++;
		printf("\n");
	}
}

/*
 *	dfs()
 *
 * 	dfs() is inspired in Depth-First Search, an algorythm used for traversing
 *  or searching through tree or graph data estructures. 
 *  The goal of our dfs() is to mark as visited all the walkable cells in the 
 *  map. To this effect, it traverses recursively the map changing to value '@'
 *	all the visited cells if their value is '0'.
 *  The resultant 'visited_array' stores the map with the walls ('1'), the 
 * 	visited cells ('@') and the non-walkable parts ('0'). It will be used later
 *	to find if map is closed, and if it's fully playable.
 */

void	dfs(t_data *data, int row, int column)
{
	data->map.visited_height = data->map.height + 2;
	data->map.visited_width = data->map.width + 1;

	if (row < 0
		|| row >= (int)data->map.visited_height
		|| column < 0
		|| column >= (int)data->map.visited_width 
		|| data->map.visited_array[row][column] == ' ' 
		|| data->map.visited_array[row][column] == '1' 
		|| data->map.visited_array[row][column] == '@')
		return ;
	data->map.visited_array[row][column] = '@';
	// usleep(100000);
	// print_visited_map(data);
	dfs(data, row -1, column);
	dfs(data, row, column + 1);
	dfs(data, row + 1, column);
	dfs(data, row, column - 1);
}

/*
 *	start_dfs_search()
 *
 *	Start the dfs search from the player's position (replace all
 *	walkable cells (that is, zeros) with '@')
 */

void	start_dfs_search(t_data *data)
{
	size_t row = data->map.player_y + 1;
	while (row < (data->map.height + 2))
	{
		size_t	column = data->map.player_x + 1;
		while (column < (data->map.width + 1))
		{
			if (data->map.visited_array[row][column] != '0')
				dfs(data, row, column);
			column++;
		}
		row++;
	}
}
/*
 *	is_map_closed()
 *
 *	Searches if the map is closed (all visited cells ('@') should be adjacent
 *	to other visited cells or walls ('@', '1'), never to a whitespace)
 */
boolean	is_map_closed(t_data *data)
{
	size_t	row;
	size_t	column;
	
	data->map.visited_height = data->map.height + 2;
	data->map.visited_width = data->map.width + 1;
	row = 0;
	while (row < data->map.visited_height)
	{
		column = 0;
		while (column < data->map.visited_width)
		{
			if (data->map.visited_array[row][column] == '@')
			{
				if ((row > 0 && data->map.visited_array[row - 1][column] == ' ')
					|| (row < (data->map.visited_height - 1) && data->map.visited_array[row + 1][column] == ' ')
					|| (column > 0 && data->map.visited_array[row][column - 1] == ' ')
					|| (column < (data->map.visited_width - 1) && data->map.visited_array[row][column + 1] == ' '))
					return (FALSE);
			}
			column++;
		}
		row++;
	}
	return (TRUE);
}

/*
 *	is_fully_walkable()
 *
 * 	Search if the map has non-reachable areas in the map (any cell remaining 
 * 	with value '0' after running dfs)
 */
boolean	is_fully_walkable(t_data *data)
{
	size_t	row;
	size_t	column;
	
	data->map.visited_height = data->map.height + 2;
	data->map.visited_width = data->map.width + 1;
	row = 0;
	while (row < data->map.visited_height)
	{
		column = 0;
		while (column < data->map.visited_width)
		{
			if (data->map.visited_array[row][column] == '0')
					return (FALSE);
			column++;
		}
		row++;
	}
	return (TRUE);
}

result	check_walls(t_data *data)
{
	start_dfs_search(data);
	if (is_map_closed(data) == FALSE)
	{
		printf(RED " \u2718 " RESET);
		printf("Error: Map is not closed\n");
		printf(RED "Map is not valid\n" RESET);
		return (FAIL);
	}
	else if (is_fully_walkable(data) == FALSE)
	{
		printf(YELLOW " \xE2\x9A\xA0 " RESET);
		printf("Warning: Map has walkable but non-reachable parts\n");
	}
	printf(GREEN " \u2714 " RESET);
	printf("Map is closed. Map check passed\n");
	printf(GREEN "All checks passed. Map is valid\n" RESET);
	printf("Starting cub3D...\n");
	return (SUCCESS);
}
