/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:04:47 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:48:33 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Outputs the integer 'n' to the given file descriptor.
 *
 * PARAMETERS
 * n  :	The integer to output;
 * fd :	The file descriptor on which to write.
 *
 * EXTERNAL FUNCTIONS
 * write()
 *
 * RETURN VALUE
 * None
 *
 * COMMENTS
 * 1. INT_MIN handling
 * 		To avoid special handling of 'n' if it's value is INT_MIN (see 
 * 		ft_itoa.c), we copy 'n' into a new variable 'ln' of type long int.
 * 2. Negative value
 * 		If 'n' is negative, we change its sign multiplying by -1, and output
 * 		the sign character '-'.
 * 3. To output 'n' we must break down the number recursively to each individual
 * 		digit, where we will convert it into a character. The division by 10
 * 		will take us further into the recursion until we finally reach the very
 * 		firs number in our int. The modulus 10 + '0' converts the number into a
 * 		char value. Though this might seem to be output immediately, it will 
 * 		actually happen last since it will be the last thing to happen when we
 * 		backtrack out of our recursion. 
 */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int			c;
	long int	ln;

	ln = n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln = ln * -1;
	}
	if (ln >= 10)
	{
		ft_putnbr_fd(ln / 10, fd);
		c = ln % 10 + 48;
		write(fd, &c, 1);
	}
	else
	{
		c = ln + 48;
		write(fd, &c, 1);
	}
}
