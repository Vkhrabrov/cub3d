/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:58:55 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/09 18:34:02 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_boolean	all_chars_are_valid(t_data *data)
{
	char	*valid_chars;
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

/*
 *	is_player_on_edge()
 *	
 *	Finds if the player is placed at any of the map's edges by:
 *	 1. Checking that he is not in the left, right, top or bottom lines
 *	 2. Checking that he has no spaces around
 */
t_boolean	is_player_on_edge(t_map *map)
{
	size_t	x;
	size_t	y;

	x = map->player_x;
	y = map->player_y;
	if (x == 0
		|| x == map->width - 2
		|| y == 0
		|| y == map->height - 1
		|| (x > 0 && map->array[y][x - 1] == ' ')
		|| (x < (map->width - 2) && map->array[y][x + 1] == ' ')
		|| (y > 0 && map->array[y - 1][x] == ' ')
		|| (y < (map->height - 1) && map->array[y + 1][x] == ' '))
		return (TRUE);
	return (FALSE);
}

static int	process_player(t_data *data, int i, int j, int *counter)
{
	data->map.player_orientation = data->map.array[i][j];
	data->map.player_x = j;
	data->map.player_y = i;
	if (is_player_on_edge(&data->map) == TRUE)
		return (-1);
	(*counter)++;
	return (0);
}

int	player_count(t_data *data)
{
	int	player_counter;

	player_counter = 0;
	data->map.i = 0;
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
			if (ft_strchr("NSEW", data->map.array[data->map.i][data->map.j]))
			{
				if (process_player(data, data->map.i,
						data->map.j, &player_counter) < 0)
					return (-1);
			}
			data->map.j++;
		}
		data->map.i++;
	}
	return (player_counter);
}

t_result	check_player(t_data *data)
{
	int	nbr_players;

	if (all_chars_are_valid(data) == FALSE)
	{
		printf("Error\nMap: Contains invalid characters\n");
		return (FAIL);
	}
	nbr_players = player_count(data);
	if (nbr_players == -1)
	{
		printf("Error\nPlayer: Must be placed within the walls\n");
		return (FAIL);
	}
	if (nbr_players == 0)
	{
		printf("Error\nPlayer: Not found\n");
		return (FAIL);
	}
	if (nbr_players > 1)
	{
		printf("Error\nPlayer: More than one player found\n");
		return (FAIL);
	}
	return (SUCCESS);
}
