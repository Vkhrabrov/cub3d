/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:36:57 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/08 21:49:08 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = NULL;
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	j = y;
	while (j < y + data->minimap_cell_size)
	{
		i = x;
		while (i < x + data->minimap_cell_size)
		{
			put_pixel(data, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_player(t_data *data, int x, int y, int size)
{
	data->minimap_cell_size = size;
	draw_square(data, x - data->minimap_cell_size / 2,
		y - data->minimap_cell_size / 2, PLAYER_COLOR);
}

void	put_texture_pixel(t_data *data, int x, int y)
{
	char	*src;
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0
		&& y < WINDOW_HEIGHT && data->tex_x >= 0
		&& data->tex_x < data->texture.width
		&& data->tex_y >= 0 && data->tex_y < data->texture.height)
	{
		src = data->texture.addr + (data->tex_y
				* data->texture.line_length + data->tex_x
				* (data->texture.bits_per_pixel / 8));
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = *(unsigned int *)src;
	}
}

void	draw_map_square(t_data *data, int is_wall)
{
	if (is_wall)
		data->color = WALL_COLOR;
	else
		data->color = EMPTY_COLOR;
	draw_square(data, data->minimap_x + data->j
		* data->minimap_cell_size,
		data->minimap_y + data->i
		* data->minimap_cell_size, data->color);
}
