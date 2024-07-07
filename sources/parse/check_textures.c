/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:44 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_result	check_textures(t_data *data, t_textures *textures)
{
	if (create_textures_array(data, textures) == FAIL)
		return (FAIL);
	if (are_all_textures_defined(textures) == FALSE)
		return (FAIL);
	if (are_texture_paths_valid(textures) == FALSE)
		return (FAIL);
	if (are_textures_unique(textures) == FALSE)
		return (FAIL);
	return (SUCCESS);
}
