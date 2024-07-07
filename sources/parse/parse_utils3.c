/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:43:07 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 13:52:18 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	rgb_to_hex(int *rgb_array)
{
	return (((rgb_array[0] & 0xFF) << 16)
		| ((rgb_array[1] & 0xFF) << 8)
		| (rgb_array[2] & 0xFF));
}

int	find_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
