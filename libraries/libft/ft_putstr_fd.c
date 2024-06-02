/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:48:21 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:47:19 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Outputs the string 's' to the given file descriptor
 *
 * EXTERNAL FUNCTIONS
 * write()
 *
 * RETURN VALUES
 * None
 *
 * COMMENTS
 * In this case, in terms of saving space there is no difference between 
 * calling predefined function ft_putchar_fd or rewriting it instead
 */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
