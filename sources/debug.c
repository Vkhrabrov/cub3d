/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:01:10 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/24 20:23:18 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	print line by line
void	print_map_array(char **array, size_t height, size_t width)
{
	(void)width;
	size_t	i;

	i = 0;
	while (i < height)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

// //	print char by char
// void	print_map_array(char **array, size_t height, size_t width)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (i < height)
// 	{
// 		j = 0;
// 		while (j < width)
// 		{
// 			printf("%c", array[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }
