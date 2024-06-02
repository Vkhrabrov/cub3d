/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:18:53 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:40:52 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <stdlib.h>
 * 
 * DESCRIPTION
 * Contiguously allocates enough space for 'count' objects that are 'size' bytes
 * of memory. The allocated memory is filled with bytes of value zero.
 *
 * EXTERNAL FUNCTIONS
 * malloc()
 *
 * RETURN VALUES
 * Returns a pointer to the allocated memory. If error, returns a NULL pointer.
 *
 * COMMENTS
 * I discarded calling ft_bzero() after francinette warning: 'Function doesn't
 * work with empty strings (?)'
 */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memspace;

	memspace = malloc(count * size);
	if (!memspace)
		return (NULL);
	ft_memset(memspace, 0, size * count);
	return (memspace);
}
