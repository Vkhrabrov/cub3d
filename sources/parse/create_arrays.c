/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:05:56 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/10 21:38:59 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_result	create_arrays(t_data *data)
{
	if (!allocate_map_array(data))
		return (FAIL);
	if (fill_map_array(data) == FAIL)
	{
		free_array(data->map.array, data->map.height);
		return (FAIL);
	}
	if (!allocate_visited(data))
	{
		free_array(data->map.array, data->map.height + 2);
		return (FAIL);
	}
	fill_visited(data);
	return (SUCCESS);
}
