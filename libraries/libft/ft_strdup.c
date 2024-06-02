/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:49:45 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:41:15 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Allocates enough memory for a copy of the string 's1'.
 *
 * EXTERNAL FUNCTIONS
 * malloc()
 *
 * RETURN VALUES
 * Returns a pointer to the copy of 's1'. The pointer may subsequently be used
 * as an argument to the function FREE.
 * If insufficient memory is available, returns NULL.
 */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		count;
	int		i;

	count = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * count);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
