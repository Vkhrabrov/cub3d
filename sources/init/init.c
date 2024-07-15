/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:02:33 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/11 00:18:18 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_data *data, char *map_file)
{
	data->map.file = map_file;
	data->map.starting_line = 1;
	data->map.ending_line = 0;
	data->map.height = 0;
	data->map.width = 0;
	data->map.array = NULL;
	data->map.i = 0;
	data->map.j = 0;
	data->map.visited_height = 0;
	data->map.visited_width = 0;
	data->map.visited = NULL;
	data->map.player_x = 0;
	data->map.player_y = 0;
	data->map.new_x = 0;
	data->map.new_y = 0;
}

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->texture_ids[0] = "NO";
	textures->texture_ids[1] = "SO";
	textures->texture_ids[2] = "EA";
	textures->texture_ids[3] = "WE";
	textures->array[0] = &textures->north;
	textures->array[1] = &textures->south;
	textures->array[2] = &textures->east;
	textures->array[3] = &textures->west;
}

void	init_colors(t_data *data)
{
	data->colors.floor[0] = -1;
	data->colors.floor[1] = -1;
	data->colors.floor[2] = -1;
	data->colors.ceiling[0] = -1;
	data->colors.ceiling[1] = -1;
	data->colors.ceiling[2] = -1;
	data->colors.hex_floor = 0x0;
	data->colors.hex_ceiling = 0x0;
}

void	initialize_game_data(t_data *data)
{
	data->player.x = 0.0f;
	data->player.y = 0.0f;
	data->player.angle = PI / 2;
	data->player.move_forward = 0;
	data->player.move_backward = 0;
	data->player.rotate_left = 0;
	data->player.rotate_right = 0;
	data->player.ray_length = 0.0;
	data->player.strafe_left = 0;
	data->player.strafe_right = 0;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->image, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	init(char *file_name, t_data *data, t_textures *textures)
{
	init_map(data, file_name);
	init_textures(textures);
	init_colors(data);
	initialize_game_data(data);
}
