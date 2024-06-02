/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalpha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:10:53 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/26 20:32:14 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <ctype.h>
 *
 * DESCRIPTION
 * Tests for any character for which isupper or islower is true. The value of
 * the argument must be representable as an unsigned char or the value of EOF.
 *
 * RETURN VALUES
 * Zero if the character tests false, non-zero if the character tests true
 */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}
