/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:22:33 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/08 22:28:02 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_map_row(t_data *data)
{
	data->j = 0;
	while (data->j < (int)data->map.width)
	{
		process_map_cell(data);
		data->j++;
	}
}

void	render_map(t_data *data)
{
	init_minimap(data);
	while (data->i < (int)data->map.height)
	{
		render_map_row(data);
		data->i++;
	}
}

void	render_background_colors(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(data, x, y, data->colors.hex_ceiling);
			put_pixel(data, x, WINDOW_HEIGHT - 1 - y, data->colors.hex_floor);
			x++;
		}
		y++;
	}
}

void	render_3d_view(t_data *data)
{
	int	x;

	x = 0;
	data->render.fov = 60.0 * PI / 180.0;
	render_background_colors(data);
	while (x < WINDOW_WIDTH)
	{
		calculate_ray(data, x);
		cast_ray(data);
		render_wall(data, x);
		x++;
	}
}

int	render_background(t_data *data)
{
	int	player_new_x;
	int	player_new_y;
	int	scaled_player;

	render_3d_view(data);
	render_map(data);
	player_new_x = data->minimap_x + (data->player.x / MINIMAP_SCALE);
	player_new_y = data->minimap_y + (data->player.y / MINIMAP_SCALE);
	scaled_player = data->player_size / MINIMAP_SCALE;
	draw_player(data, player_new_x, player_new_y, scaled_player);
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	return (0);
}
