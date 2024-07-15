/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initiations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:17:22 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/13 00:07:29 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_movement(t_data *data)
{
	data->moves.delta_time = 0.028135;
	data->moves.move_speed = data->cell_size * 5.0 * data->moves.delta_time;
	data->moves.rot_speed = PI / 2.0 * data->moves.delta_time;
	data->moves.cos_angle = cos(data->player.angle);
	data->moves.sin_angle = sin(data->player.angle);
	data->moves.new_x = data->player.x;
	data->moves.new_y = data->player.y;
	data->moves.half_size = data->player_size / 2.0;
}

void	init_player(t_data *data)
{
	data->player.x = data->map.player_x * data->cell_size
		+ data->cell_size / 2;
	data->player.y = data->map.player_y * data->cell_size
		+ data->cell_size / 2;
	if (data->map.player_orientation == 'N')
		data->player.angle = 3 * PI / 2;
	if (data->map.player_orientation == 'S')
		data->player.angle = PI / 2;
	if (data->map.player_orientation == 'W')
		data->player.angle = PI;
	if (data->map.player_orientation == 'E')
		data->player.angle = 0;
	data->map.array[data->map.player_y][data->map.player_x] = '0';
}

void	init_minimap(t_data *data)
{
	data->minimap_cell_size = data->cell_size / MINIMAP_SCALE;
	data->minimap_x = 30;
	data->minimap_y = WINDOW_HEIGHT
		- (data->map.height * data->minimap_cell_size) - 20;
	data->i = 0;
}

void	calculate_ray_2(t_data *data)
{
	if (data->render.ray_x < 0)
	{
		data->render.step_x = -1;
		data->render.side_dist_x = ((data->player.x / data->cell_size)
				- data->render.map_x) * data->render.d_dist_x;
	}
	else
	{
		data->render.step_x = 1;
		data->render.side_dist_x = (data->render.map_x + 1.0
				- (data->player.x / data->cell_size)) * data->render.d_dist_x;
	}
	if (data->render.ray_y < 0)
	{
		data->render.step_y = -1;
		data->render.side_dist_y = ((data->player.y / data->cell_size)
				- data->render.map_y) * data->render.d_dist_y;
	}
	else
	{
		data->render.step_y = 1;
		data->render.side_dist_y = (data->render.map_y + 1.0
				- (data->player.y / data->cell_size)) * data->render.d_dist_y;
	}
}

void	calculate_ray(t_data *data, int x)
{
	data->render.camera_x = 2 * (x / (double)WINDOW_WIDTH) - 1;
	data->render.ray_dir_x = cos(data->player.angle);
	data->render.ray_dir_y = sin(data->player.angle);
	data->render.plane_x = -data->render.ray_dir_y * tan(data->render.fov / 2);
	data->render.plane_y = data->render.ray_dir_x * tan(data->render.fov / 2);
	data->render.ray_x = data->render.ray_dir_x + data->render.plane_x
		* data->render.camera_x;
	data->render.ray_y = data->render.ray_dir_y + data->render.plane_y
		* data->render.camera_x;
	data->render.map_x = (int)(data->player.x / data->cell_size);
	data->render.map_y = (int)(data->player.y / data->cell_size);
	data->render.d_dist_x = fabs(1 / data->render.ray_x);
	data->render.d_dist_y = fabs(1 / data->render.ray_y);
	calculate_ray_2(data);
}
