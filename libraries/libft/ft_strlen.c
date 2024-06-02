/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:03:29 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/04 20:57:54 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Computes the length of the string 's'.
 *
 * RETURN VALUES
 * Returns the number of characters that precede the terminating NUL character
 */

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
