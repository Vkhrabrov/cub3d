/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:40:19 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/04 22:19:00 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <ctype.h>
 *
 * DESCRIPTION
 * Tests for a decimal digit character. The value of the argument must be 
 * representable as an unsigned char or the value of EOF.
 *
 * RETURN VALUES
 * Zero if the character tests false, non-zero if the character tests true.
 */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
