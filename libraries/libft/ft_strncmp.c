/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:47:51 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/01 19:58:30 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * The function lexicographically compares 'n' characers of the null-terminated 
 * strings 's1' and 's2'.
 * Because it is designed for comparing strings rather than binarydata, 
 * characters that appear after a '\0' character are not compared.
 *
 * RETURNED VALUES
 * An integer greater than, equal to, or less than 0, according as the string
 * 's1' is greater than, equal to, or less than the string 's2'.
 *
 * COMMENTS
 * The function compares the first two characters in the string (when comparing
 * it uses their values as unsigned char, even though they are passed via 
 * pointers to char). If the characters differ or either is a null character:
 * 	- If the character from the first string is greater than the character from
 * 		the second, the function returns a positive value:
 * 	- If the first is less than the second, the function return a negative value;
 * 	- Otherwise (the characters are both null characters) the function returns 0.
 *
 * Function memcmp() is too a string comparator, but there are significant
 * differences between both. See ft_memcmp() comments for further information. 
 */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
