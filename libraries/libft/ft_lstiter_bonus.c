/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:36:44 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 23:03:48 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Iterates the list 'lst' and applies the function f on the content of each
 * node
 *
 * PARAMETERS
 * lst: The address to a pointer to a node.
 * f  :	The address of the function used to iterate on the list.
 *
 * RETURN VALUE
 * None
 */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			if (lst != NULL)
				f(lst->content);
			lst = lst->next;
		}
	}
	return ;
}
