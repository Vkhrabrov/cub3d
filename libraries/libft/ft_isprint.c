/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:27:36 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/26 20:45:41 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <ctype.c>
 *
 * DESCRIPTION
 * Tests for any printing character, including space. In the ASCII decimal 
 * character set, this includes from character 32 to character 126, inclusive.
 *
 * RETURN VALUES
 * Zero if the value tests false, non -zero if the character tests true.
 */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
