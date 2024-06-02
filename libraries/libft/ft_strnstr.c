/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:52:09 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/01 23:19:18 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 * 
 * DESCRIPTION
 * Locates the first occurrence of the null-terminated string 'needle' in the
 * string 'haystack', where no more than 'len' characters are searched.
 * Characters that appear after a '\0' character are not searched.
 *
 * RETURNED VALUES
 * If 'needle' is an empty string, 'haystack' is returned;
 * If 'needle' occurs nowhere in 'haystack', NULL is returned;
 * Otherwise a pointer to the first character of the first occurrence of 
 * 'needle' is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (needle[j] == haystack[i + j] && (i + j) < len)
			{
				j++;
				if (needle[j] == '\0')
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}
