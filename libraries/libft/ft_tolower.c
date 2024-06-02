/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:08:16 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/29 22:56:52 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <ctype.h>
 *
 * DESCRIPTION
 * Converts an upper-case letter to the correspondig lower-case letter.
 *
 * RETURN VALUES
 * if the argument is an upper-case letter, returns the corresponding lower-case
 * letter if there is one; otherwise, the argument is returned unchanged.
 */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
