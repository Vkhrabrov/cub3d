/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcelona.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:53:53 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:41:40 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Allocates and returns a substring from the string 's'
 *
 * PARAMETERS
 * s	:	The substring from which to create the string;
 * start:	The start index of the substring in the existing string 's';
 * len	:	The maximum length of the substring.
 *
 * EXTERNAL FUNCTIONS
 * malloc()
 *
 * RETURN VALUES
 * The substring, or NULL if the allocation fails.
 *
 * COMMENTS
 * If 'start' is bigger than 's' length,  we are pretending that the substring
 * begins in a place that doesn't exist. So we allocate memory just for just one
 * byte, the null termination ('\0') of substring, and then return the substring.
 * This can also be done by calling ft_strdup and passing an empty string "" as 
 * a parameter.
 *
 * If the 'start' position plus the 'len' size of substring is bigger than 's'
 * length, we are pretending to keep copying in substring though 's' has ended.
 * Thus, we redefine 'len' size of the substring so that it does not exceed the
 * length of 's': len = ft_strlen(s) - start
 */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		substr = malloc(sizeof(char));
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
