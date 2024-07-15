/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:43:42 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/08 22:28:24 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map_cell(t_data *data)
{
	if (data->j < (int)ft_strlen(data->map.array[data->i]))
	{
		if (data->map.array[data->i][data->j] == '1')
			draw_map_square(data, 1);
		else if (data->map.array[data->i][data->j] == '0')
			draw_map_square(data, 0);
		else if (data->map.array[data->i][data->j]
				== data->map.player_orientation)
			init_player(data);
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 65361)
		data->player.rotate_left = 1;
	else if (keycode == 65363)
		data->player.rotate_right = 1;
	else if (keycode == 65362 || keycode == 119)
		data->player.move_forward = 1;
	else if (keycode == 65364 || keycode == 115)
		data->player.move_backward = 1;
	else if (keycode == 97)
		data->player.strafe_left = 1;
	else if (keycode == 100)
		data->player.strafe_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 65361)
		data->player.rotate_left = 0;
	else if (keycode == 65363)
		data->player.rotate_right = 0;
	else if (keycode == 65362 || keycode == 119)
		data->player.move_forward = 0;
	else if (keycode == 65364 || keycode == 115)
		data->player.move_backward = 0;
	else if (keycode == 97)
		data->player.strafe_left = 0;
	else if (keycode == 100)
		data->player.strafe_right = 0;
	return (0);
}

void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * PI;
	while (*angle >= 2 * PI)
		*angle -= 2 * PI;
}
