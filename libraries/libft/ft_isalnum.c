/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:13:38 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/02 18:29:48 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <ctype.h>
 *
 * DESCRIPTION
 * Tests for any character for which isalpha(3) or isdigit(3) is true. The value
 * of the argument must be representable as an unsigned char or the value of EOF
 *
 * RETURN VALUES
 * Zero if the character tests false, non-zero if the character tests true.
 */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	else
		return (0);
}
