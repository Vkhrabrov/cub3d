/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:41 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_result	check_walls(t_data *data)
{
	start_dfs_search(data);
	if (is_map_closed(data) == FALSE)
	{
		printf(RED " \u2718 " RESET);
		printf("Error\nMap: Is not closed\n");
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
