/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:32:39 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 19:44:56 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Applies the function 'f' on each character of the string passed as an
 * argument, passing its index as first argument. Each character is passed by
 * address to 'f' to be modified if necessary.
 *
 * PARAMETERS
 * s:	The string on which to iterate.
 * f:	The function to apply to each character.
 *
 * RETURN VALUES
 * None
 */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
		s[i] = '\0';
	}
}
