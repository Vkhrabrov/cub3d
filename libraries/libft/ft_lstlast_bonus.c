/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:26:36 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:49:43 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Returns the last node of the list.
 *
 * PARAMETERS
 * lst: The beginning of the list.
 *
 * RETURN VALUE
 * Last node of the list
 */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->next != NULL)
			lst = lst->next;
		else
			return (lst);
	}
	return (lst);
}
