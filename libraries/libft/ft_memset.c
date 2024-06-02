/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:01:31 by ccarrace          #+#    #+#             */
/*   Updated: 2023/10/06 19:43:18 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Writes 'len' bytes of value 'c' (converted to an UNSIGNED CHAR) to string 'b'
 *
 * RETURN VALUES
 * Returns its first argument
 *
 * COMMENTS
 * memset() is used to set a block of memory to a specific value. It's a low-level
 * memory manipulation and operates byte by byte, meaning that it sets each byte
 * in the memory block individually. It can be used to initialize structures since
 * it is not possible to access struct members by index as we do with arrays.
 * However it is not suitable for initializing complex structures, just structs 
 * with simple data types like characters or integers (e.g SIGACTION)
 */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
