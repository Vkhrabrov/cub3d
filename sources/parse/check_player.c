/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:58:55 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/03 20:05:55 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

boolean all_chars_are_valid(t_data *data)
{
    char    *valid_chars;
	size_t	i;
	size_t	j;
	
    valid_chars = "NSEW10 ";
    i = 0;
	if (data->map.array == NULL)
	{
		printf("Error\nMap or map array is NULL\n");
        return (FALSE);
	}
    while (i < data->map.height)
    {
        j = 0;
        while (data->map.array[i][j] != '\0')
        {
            if (!ft_strchr(valid_chars, data->map.array[i][j]))
                return (FALSE);
            j++;
        }
        i++;
    }
	return (TRUE);    
}

// boolean	is_player_on_edge(t_map *map)
// {
// 	if (data->map.player_x == 0
// 		|| data->map.player_y == 0
// 		|| data->map.player_x == data->map.width - 2
// 		|| data->map.player_y == data->map.height - 1
// 		|| data->map.visited_array[data->map.player_x][data->map.player_y + 1] == ' '	// left
// 		|| data->map.visited_array[data->map.player_x][data->map.player_y + 3] == ' '	// right
// 		|| data->map.visited_array[data->map.player_x - 1][data->map.player_y + 2] == ' '	// up
// 		|| data->map.visited_array[data->map.player_x + 1][data->map.player_y + 2] == ' ')	// down
// 		return (TRUE);
// 	return (FALSE);
// }

// boolean	is_player_on_edge(t_map *map)
// {
// 	if (data->map.player_x == 0
// 		|| data->map.player_y == 0
// 		|| data->map.player_x == data->map.width - 2
// 		|| data->map.player_y == data->map.height - 1
// 		|| (data->map.player_y > 0 && data->map.array[data->map.player_x - 1][data->map.player_y] == ' ')	// left
// 		|| (data->map.player_y < data->map.width && data->map.array[data->map.player_x + 1][data->map.player_y] == ' ')	// right
// 		|| (data->map.player_x > 0 && data->map.array[data->map.player_x][data->map.player_y - 1] == ' ')	// up
// 		|| (data->map.player_x < data->map.height && data->map.array[data->map.player_x][data->map.player_y + 1] == ' '))	// down
// 		return (TRUE);
// 	return (FALSE);
// }
boolean is_player_on_edge(t_map *map)
{
    if (map->player_x == 0  // Left edge
        || map->player_x == map->width - 2  // Right edge
        || map->player_y == 0  // Top edge
        || map->player_y == map->height - 1  // Bottom edge
        || (map->player_x > 0 && map->array[map->player_y][map->player_x - 1] == ' ')  // Left empty space
        || (map->player_x < map->width - 2 && map->array[map->player_y][map->player_x + 1] == ' ')  // Right empty space
        || (map->player_y > 0 && map->array[map->player_y - 1][map->player_x] == ' ')  // Top empty space
        || (map->player_y < map->height - 1 && map->array[map->player_y + 1][map->player_x] == ' '))  // Bottom empty space
        return (TRUE);
    return (FALSE);
}

int player_count(t_data *data)
{
    int		player_counter;
    char    *valid_directions;

    valid_directions = "NSEW";
    data->map.i = 0;
	player_counter = 0;
	if (data->map.array == NULL)
	{
		printf("Error\nMap or map array is NULL\n");
        return (0);
	}
    while (data->map.i < data->map.height)
    {
        data->map.j = 0;
        while (data->map.array[data->map.i][data->map.j] != '\0')
        {
            if (ft_strchr(valid_directions, data->map.array[data->map.i][data->map.j]))
            {
                data->map.player_orientation = data->map.array[data->map.i][data->map.j];
				data->map.player_x = data->map.j;
				data->map.player_y = data->map.i;
				if (is_player_on_edge(&data->map))
					return (-1);
                player_counter++;
            }
            data->map.j++;
        }
        data->map.i++;
    }
	return (player_counter);
}

result check_player(t_data *data)
{
    int nbr_players;

    if (all_chars_are_valid(data) == FALSE)
	{
		printf("Error\nMap: Contains invalid characters\n");
		return (FAIL);
	}
    nbr_players = player_count(data);
    if (nbr_players == -1)
	{
		printf("Error\nPlayer: Cannot be placed in a map edge\n");
		return (FAIL);
	}
    if (nbr_players == 0) //|| (is_player_on_edge(map) == TRUE)) 
	{
		printf("Error\nPlayer: Not found\n");
		return (FAIL);
	}
    if (nbr_players > 1)
	{
		printf("Error\nPlayer: More than one player found\n");
		return (FAIL);
	}
	// if (is_player_on_edge(map) == TRUE)
	// {
	// 	printf("Error\nPlayer is not inside the map\n");
	// 	return (FAIL);
	// }
    return (SUCCESS);
}
