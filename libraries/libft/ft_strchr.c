/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:22:51 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/01 18:55:11 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Locates the LAST occurrence of 'c' (converted to a char) in the string 
 * pointed to by 's'. The terminating null character is considered to be part of 
 * the string; therefore if 'c' is '\0', function locates the terminating '\0'.
 *
 * RETURNED VALUES
 * A pointer to the located character, or NULL if the character does not appear
 * in the string
 *
 * COMMENTS
 * The function memchr() is virtually the same. 
 * See comments in ft_memchr.c for further information.
 */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}
