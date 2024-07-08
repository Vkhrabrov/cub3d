/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:10:28 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/08 21:54:10 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_data *data)
{
	if (data->player.rotate_left)
	{
		data->player.angle -= data->moves.rot_speed;
		normalize_angle(&data->player.angle);
	}
	if (data->player.rotate_right)
	{
		data->player.angle += data->moves.rot_speed;
		normalize_angle(&data->player.angle);
	}
}

void	move_player(t_data *data)
{
	if (data->player.move_forward)
	{
		data->moves.new_x += data->moves.move_speed
			* data->moves.cos_angle;
		data->moves.new_y += data->moves.move_speed
			* data->moves.sin_angle;
	}
	if (data->player.move_backward)
	{
		data->moves.new_x -= data->moves.move_speed
			* data->moves.cos_angle;
		data->moves.new_y -= data->moves.move_speed
			* data->moves.sin_angle;
	}
}

void	strafe_player(t_data *data)
{
	if (data->player.strafe_left)
	{
		data->moves.new_x += data->moves.move_speed
			* cos(data->player.angle - PI / 2);
		data->moves.new_y += data->moves.move_speed
			* sin(data->player.angle - PI / 2);
	}
	if (data->player.strafe_right)
	{
		data->moves.new_x += data->moves.move_speed
			* cos(data->player.angle + PI / 2);
		data->moves.new_y += data->moves.move_speed
			* sin(data->player.angle + PI / 2);
	}
}

void	update_player_x(t_data *data)
{
	if (!is_wall(data, data->moves.new_x
			+ data->moves.half_size, data->player.y)
		&& !is_wall(data, data->moves.new_x
			- data->moves.half_size, data->player.y))
		data->player.x = data->moves.new_x;
	else
	{
		if (data->moves.new_x > data->player.x)
			data->player.x = floor((data->moves.new_x
						+ data->moves.half_size) / data->cell_size)
				* data->cell_size - data->moves.half_size - 1;
		else
			data->player.x = ceil((data->moves.new_x
						- data->moves.half_size) / data->cell_size)
				* data->cell_size + data->moves.half_size;
	}
}

void	update_player_y(t_data *data)
{
	if (!is_wall(data, data->player.x, data->moves.new_y
			+ data->moves.half_size)
		&& !is_wall(data, data->player.x, data->moves.new_y
			- data->moves.half_size))
		data->player.y = data->moves.new_y;
	else
	{
		if (data->moves.new_y > data->player.y)
			data->player.y = floor((data->moves.new_y
						+ data->moves.half_size) / data->cell_size)
				* data->cell_size - data->moves.half_size - 1;
		else
			data->player.y = ceil((data->moves.new_y
						- data->moves.half_size) / data->cell_size)
				* data->cell_size + data->moves.half_size;
	}
}
