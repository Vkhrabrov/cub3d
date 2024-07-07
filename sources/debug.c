/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:01:10 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:26:59 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map_by_lines(char **array, size_t height, size_t width)
{
	(void)width;
	size_t	i;

	i = 0;
	while (i < height)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	print_map_by_chars(char **array, size_t height, size_t width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			printf("%c", array[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	debug_x_collision(t_data *data, double new_x, double new_y)
{
	int	half_size;
	
	half_size = data->player_size / 2;
	if (is_wall(data, new_x - half_size, data->player.y))
	{
		printf("cell size   = %d\n", data->cell_size);
		printf("player size = %d\n", data->player_size);
		printf("player new position = (%f, %f)\n", new_x, new_y);
		printf("player south edge   = (%f, %f)\n", new_x, new_y + half_size);
		printf("player north edge   = (%f, %f)\n", new_x, new_y - half_size);
		printf("player east edge    = (%f, %f)\n", new_x - half_size, new_y);
		printf("player west edge    = (%f, %f)\n", new_x + half_size, new_y);
		printf(" --> east wall collision at  %f\n\n", new_x - half_size);
	}
    else if (is_wall(data, new_x + half_size, data->player.y))
	{
		printf("cell size   = %d\n", data->cell_size);
		printf("player size = %d\n", data->player_size);
		printf("player new position = (%f, %f)\n", new_x, new_y);
		printf("player south edge   = (%f, %f)\n", new_x, new_y + half_size);
		printf("player north edge   = (%f, %f)\n", new_x, new_y - half_size);
		printf("player east edge    = (%f, %f)\n", new_x - half_size, new_y);
		printf("player west edge    = (%f, %f)\n", new_x + half_size, new_y);
		printf(" --> west wall collision at  %f\n\n", new_x + half_size);
	}
}

void	debug_y_collision(t_data *data, double new_x, double new_y)
{
	int	half_size;
	
	half_size = data->player_size / 2;
	if (is_wall(data, data->player.x, new_y + half_size))
	{
		printf("cell size   = %d\n", data->cell_size);
		printf("player size = %d\n", data->player_size);
		printf("player new position = (%f, %f)\n", new_x, new_y);
		printf("player south_edge   = (%f, %f)\n", new_x, new_y + half_size);
		printf("player north_edge   = (%f, %f)\n", new_x, new_y - half_size);
		printf("player east_edge    = (%f, %f)\n", new_x - half_size, new_y);
		printf("player west_edge    = (%f, %f)\n", new_x + half_size, new_y);
		printf(" --> south wall collision at %f\n\n", new_y + half_size);
	}
	else if (is_wall(data, data->player.x, new_y - half_size))
	{
		printf("cell size   = %d\n", data->cell_size);
		printf("player size = %d\n", data->player_size);
		printf("player_new_position = (%f, %f)\n", new_x, new_y);
		printf("player south_edge   = (%f, %f)\n", new_x, new_y + half_size);
		printf("player north_edge   = (%f, %f)\n", new_x, new_y - half_size);
		printf("player east_edge    = (%f, %f)\n", new_x - half_size, new_y);
		printf("player west_edge    = (%f, %f)\n", new_x + half_size, new_y);
		printf(" --> north wall collision at %f\n\n", new_y - half_size);
	}
}
