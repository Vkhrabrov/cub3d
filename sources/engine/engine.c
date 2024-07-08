/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:06:48 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/08 20:56:16 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}

void	render_wall(t_data *data, int x)
{
	if (data->render.hit == 1)
	{
		calculate_wall_distance(data);
		select_texture(data);
		draw_textured_wall(data, x);
	}
}

void	update_player(t_data *data)
{
	init_player_movement(data);
	rotate_player(data);
	move_player(data);
	strafe_player(data);
	update_player_x(data);
	update_player_y(data);
}

int	main_loop(t_data *data)
{
	update_player(data);
	render_background(data);
	return (0);
}
