/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:55:47 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:46:39 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Outputs the character 'c' to the given file descriptor
 *
 * RETURN VALUES
 * None
 *
 * EXTERNAL FUNCTIONS
 * write()
 *
 * COMMENTS
 * We use the allowed function 'write' (defined in library <unistd.h>):
 * 			ssize_t(int fildes, const void *buf, size_t nbyte)
 * The function writes 'nbyte' to the object referenced by the file descriptor 
 * (standard input (value 0), standard output (value 1) or standard error (2))
 * from the buffer pointed to by buff (that's why we use the address to our 
 * char: '&c').
 * 		NOTE: ssize_t is used for functions whose return could either
 * 			be a valid size, or a negative value to indicate an error.
 * 			Whenever ou mean to return a size in bytes, use size_t instead
 */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
