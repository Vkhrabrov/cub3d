/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:41 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/08 19:43:35 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 *	dfs()
 *
 * 	dfs() is inspired in Depth-First Search, an algorythm used for traversing
 *  or searching through tree or graph data estructures. 
 *  The goal of our dfs() is to mark as visited all the walkable cells in the 
 *  map. To this effect, it traverses recursively the map changing to value '@'
 *	all the visited cells if their value is '0'.
 *  The t_resultant 'visited' stores the map with the walls ('1'), the 
 * 	visited cells ('@') and the non-walkable parts ('0'). It will be used later
 *	to find if map is closed, and if it's fully playable.
 *
 * 	'print_visited_map() is called here to display the map with the visited and
 * 	unvisited cells highlighted in different colors. If you want to see how the
 * 	recursive function works dinamically add a 'usleep(100000)' before the call
 * 	to 'print_visited_map()'
 */

static void	dfs(t_data *data, int row, int column)
{
	data->map.visited_height = data->map.height + 2;
	data->map.visited_width = data->map.width + 1;
	if (row < 0
		|| row >= (int)data->map.visited_height
		|| column < 0
		|| column >= (int)data->map.visited_width
		|| data->map.visited[row][column] == ' '
		|| data->map.visited[row][column] == '1'
		|| data->map.visited[row][column] == '@')
		return ;
	data->map.visited[row][column] = '@';
	if (DEBUG_MODE == 1)
	{
		usleep(100000);
		print_visited_map(data);
	}
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
static void	start_dfs_search(t_data *data)
{
	size_t	row;
	size_t	column;

	row = data->map.player_y + 1;
	while (row < (data->map.height + 2))
	{
		column = data->map.player_x + 1;
		while (column < (data->map.width + 1))
		{
			if (data->map.visited[row][column] != '0')
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
static t_boolean	is_map_closed(t_data *data)
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
			if (data->map.visited[row][column] == '@'
					&& ((row > 0 && data->map.visited[row - 1][column] == ' ')
					|| (row < (data->map.visited_height - 1)
						&& data->map.visited[row + 1][column] == ' ')
					|| (column > 0 && data->map.visited[row][column - 1] == ' ')
					|| (column < (data->map.visited_width - 1)
						&& data->map.visited[row][column + 1] == ' ')))
				return (FALSE);
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
static t_boolean	is_fully_walkable(t_data *data)
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
			if (data->map.visited[row][column] == '0')
				return (FALSE);
			column++;
		}
		row++;
	}
	return (TRUE);
}

t_result	check_walls(t_data *data)
{
	start_dfs_search(data);
	if (is_map_closed(data) == FALSE)
	{
		printf("Error\nMap: Is not closed\n");
		return (FAIL);
	}
	if (DEBUG_MODE == 0)
		display_checks();
	if (is_fully_walkable(data) == FALSE)
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
