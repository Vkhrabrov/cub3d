/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:41:28 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/29 21:38:50 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Copies 'n' bytes from memory area 'src' to memory area 'dst'. 
 * Whether 'src' and 'dst' might overlap, behaviour is undefined. Better use 
 * memmove instead.
 *
 * RETURN VALUES
 * The original value of 'dst'
 */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)dst)[i] != '\0'
				|| ((unsigned char *)src)[i] != '\0')
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
		i++;
	}
	return (dst);
}
