/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:43:57 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/29 22:57:28 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <ctype.h>
 *
 * DESCRIPTION
 * Converts a lower-case letter to the corresponding upper-case letter.
 *
 * RETURN VALUES
 * If the argument is a lower-case letter, returns the corresponding upper-case
 * letter if there is one; otherwise, the argument is returned unchanged
 */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
