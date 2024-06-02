/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 22:14:35 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/30 22:02:22 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Copies 'len' bytes from string 'src' to string 'dst'. Strings may overlap.
 * Unlike memcpy, memmovr does not copy data one by one from one location to 
 * another. It copies the data first to an intermediate buffer, then from the 
 * buffer to destination.
 *
 * RETURN VALUES
 * The original value of 'dst'.
 *
 * COMMENTS
 * We are reading from one memory segment, 'src' and copying it to another 
 * memory segment, 'dst'. If both memor segments coincide at some point, an 
 * overlapping would occur. 
 * By comparing the src and dst adresses we can find if they overlap. 
 * 	- If they do overlap, we have to find which end of 'dst' overlaps with 
 * 	  the source and choose the direction of copying accordingly:
 * 		* If the beginning of 'dst' overlaps ('dst > 'src'), copy from 
 * 			end to beginning
 * 		* If the end of 'dst' overlaps ('dst' <= 'src') copy from 
 * 			beginning to end
 *	- If they do not overlap, we can copy in any direction.
 */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	if (dst <= src)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	return (dst);
}
