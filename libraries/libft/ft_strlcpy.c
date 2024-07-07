/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:07:46 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Copies up to 'dstsize - 1' characters from the string 'src' to 'dst',
 * NUL-terminating the t_result if 'dstsize' is not 0.
 * If the 'src' and 'dst' strings overlap. the behaviour is undefined.
 *
 * RETURN VALUES
 * The length of 'src'
 */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_length;

	src_length = 0;
	while (src[src_length] != '\0')
		src_length++;
	if (dstsize == 0)
		return (src_length);
	i = 0;
	while ((src[i] != '\0') && (i < (dstsize - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_length);
}
