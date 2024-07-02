/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:02:33 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/30 20:37:58 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_data *data, char *map_file)
{
	data->map.file = map_file;
	data->map.starting_line = 1;
	data->map.ending_line = 1;
	data->map.height = 0;
	data->map.width = 0;
	data->map.array = NULL;
	data->map.i = 0;
	data->map.j = 0;
	data->map.visited_height = 0;
	data->map.visited_width = 0;
	data->map.visited_array = NULL;
	data->map.player_x = 0;
	data->map.player_y = 0;
	data->map.closed = true;
	data->map.new_x = 0;
	data->map.new_y = 0;
}

void  init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->texture_ids[0] = "NO";
	textures->texture_ids[1] = "SO";
	textures->texture_ids[2] = "EA";
	textures->texture_ids[3] = "WE";
	textures->paths_array[0] = &textures->north;
	textures->paths_array[1] = &textures->south;
	textures->paths_array[2] = &textures->east;
	textures->paths_array[3] = &textures->west;	
}

void  init_colors(t_colors *colors)
{
  colors->floor[0] = -1;
  colors->floor[1] = -1;
  colors->floor[2] = -1;
  colors->ceiling[0] = -1; 
  colors->ceiling[1] = -1;
  colors->ceiling[2] = -1;
}