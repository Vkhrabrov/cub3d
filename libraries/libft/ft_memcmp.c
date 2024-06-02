/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:14:42 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/01 23:18:12 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Compares two byte strings, s1 and s2. Both ar asummed to be n bytes long.
 *
 * RETURN VALUES
 * 0 if the two strings are identical, otherwise returns the difference
 * between the two first differing bytes (treated as UNSIGNED CHAR).
 *
 * COMMENTS 
 * Though apparently memcmp() is similar to strncmp() since both compare two 
 * strings, the fact is that:
 *  - strncmp() compares at most 'n' characters of null-terminated strings;
 *  - while memcmp() compares binary byte buffers of 'n' bytes.
 * strncmp() is better equipped for string comparisons than memcmp() is 
 * (i.e, strncmp() stops at null terminator while memcmp() does not)
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
		i++;
	}
	return (0);
}
