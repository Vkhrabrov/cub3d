/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:29:57 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/10 23:03:24 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(t_data *data)
{
	data->render.hit = 0;
	while (data->render.hit == 0)
	{
		if (data->render.side_dist_x < data->render.side_dist_y)
		{
			data->render.side_dist_x += data->render.d_dist_x;
			data->render.map_x += data->render.step_x;
			data->render.side = 0;
		}
		else
		{
			data->render.side_dist_y += data->render.d_dist_y;
			data->render.map_y += data->render.step_y;
			data->render.side = 1;
		}
		if (data->render.map_x < 0 || data->render.map_y < 0
			|| data->render.map_x >= (int)data->map.width
			|| data->render.map_y >= (int)data->map.height)
			break ;
		if (data->map.array[data->render.map_y][data->render.map_x] == '1')
			data->render.hit = 1;
	}
}

void	calculate_wall_distance(t_data *data)
{
	if (data->render.side == 0)
		data->render.perp_wall_dist = (data->render.map_x - data->player.x
				/ data->cell_size + (1 - data->render.step_x) / 2)
			/ data->render.ray_x;
	else
		data->render.perp_wall_dist = (data->render.map_y - data->player.y
				/ data->cell_size + (1 - data->render.step_y) / 2)
			/ data->render.ray_y;
	data->render.line_height = (int)(WINDOW_HEIGHT
			/ data->render.perp_wall_dist);
	data->render.draw_start = -data->render.line_height
		/ 2 + WINDOW_HEIGHT / 2;
	if (data->render.draw_start < 0)
		data->render.draw_start = 0;
	data->render.draw_end = data->render.line_height / 2 + WINDOW_HEIGHT / 2;
	if (data->render.draw_end >= WINDOW_HEIGHT)
		data->render.draw_end = WINDOW_HEIGHT - 1;
}

void	select_texture(t_data *data)
{
	if (data->render.side == 0)
	{
		if (data->render.step_x > 0)
			data->texture = data->west_texture;
		else
			data->texture = data->east_texture;
	}
	else
	{
		if (data->render.step_y > 0)
			data->texture = data->north_texture;
		else
			data->texture = data->south_texture;
	}
	if (data->render.side == 0)
		data->render.wall_x = data->player.y / data->cell_size
			+ data->render.perp_wall_dist * data->render.ray_y;
	else
		data->render.wall_x = data->player.x / data->cell_size
			+ data->render.perp_wall_dist * data->render.ray_x;
	data->render.wall_x -= floor(data->render.wall_x);
	data->tex_x = (int)(data->render.wall_x * (double)data->texture.width);
	if ((data->render.side == 0 && data->render.ray_x > 0)
		|| (data->render.side == 1 && data->render.ray_y < 0))
		data->tex_x = data->texture.width - data->tex_x - 1;
}

void	draw_textured_wall(t_data *data, int x)
{
	int	y;

	y = data->render.draw_start;
	data->render.step = 1.0 * data->texture.height
		/ data->render.line_height;
	data->render.tex_pos = (data->render.draw_start - WINDOW_HEIGHT
			/ 2 + data->render.line_height / 2) * data->render.step;
	while (y < data->render.draw_end)
	{
		data->tex_y = (int)data->render.tex_pos
			& (data->texture.height - 1);
		data->render.tex_pos += data->render.step;
		put_texture_pixel(data, x, y);
		y++;
	}
}

int	is_wall(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / data->cell_size);
	map_y = (int)(y / data->cell_size);
	if (map_x < 0 || map_x >= (int)data->map.width
		|| map_y < 0 || map_y >= (int)data->map.height)
		return (1);
	return (data->map.array[map_y][map_x] == '1');
}
