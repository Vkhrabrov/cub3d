/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:02:07 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/30 22:28:27 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * The function is identical to strchr(), except it locates the LAST occurrence 
 * of 'c' (converted to a char) in the string pointed to by 's'. The terminating
 * null character is considered to be part of the string; therefore if 'c' is 
 * '\0', the function locate the terminating '\0'.
 *
 * RETURNED VALUES
 * A pointer to the located character, or NULL if the character does not appear
 * in the string
 */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}
