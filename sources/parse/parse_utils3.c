/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:43:07 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/10 21:39:06 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgb_to_hex(int *rgb_array)
{
	return (((rgb_array[0] & 0xFF) << 16)
		| ((rgb_array[1] & 0xFF) << 8)
		| (rgb_array[2] & 0xFF));
}

int	find_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	free_all(t_textures *textures, t_map *map)
{
	int	i;

	i = 0;
	if (textures->array != NULL)
	{
		while (i < 4)
		{
			if (*(textures->array[i]) != NULL)
			{
				free(*(textures->array[i]));
				*(textures->array[i]) = NULL;
			}
			i++;
		}
	}
	if (map != NULL)
	{
		free_array(map->array, map->height);
		map->array = NULL;
		free_array(map->visited, (map->height + 2));
		map->visited = NULL;
	}
	return (0);
}

void	display_map_error(char *str, int code)
{
	printf(RED " \u2718 " RESET);
	printf("Error\n%s\n", str);
	if (code)
		printf(RED "File is not valid\n" RESET);
}
