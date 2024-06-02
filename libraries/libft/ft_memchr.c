/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:32:37 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/01 18:56:14 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Locates the first occurence of c (CONVERTED TO AN UNSIGNED CHAR) in string s.
 *
 * RETURN VALUES
 * Returns a pointer to the byte located, or NULL if no such byte exists within
 * n bytes.
 *
 * COMMENTS
 * Functionally there is no difference between memchr() and strchr() in that 
 * both scan an array/ponter for a provided value 'c'.
 * The memchr() version just takes an extra parameter because it needs to know
 * the length of the provided pointer.
 * The difference is that strchr() stops when it hits a null character but 
 * memchr() does not; this is why the former does not need a length parameter
 * but the latter does.
 * Differences can popu if you attempt to use a char* which stores binary data
 * with strchar() as it potentially won't see the full length of the string. 
 * This is true of pretty much any char* with binary data and a str* function.
 * For non binary data though they are virtually the same function.
 */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (((void *)s) + i);
		i++;
	}
	return (NULL);
}
