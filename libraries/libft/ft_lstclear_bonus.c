/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:59:39 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:58:38 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Deletes and frees the given node and every successor of that node, using the
 * function 'del' and 'free'. Finally, the pointer must be set to NULL.
 *
 * PARAMETERS
 * lst: The addres of a pointer to a node.
 * del: The address of the function used to delete the content of the node.
 *
 * EXTERNAL FUNCTION
 * free()
 *
 * RETURN VALUES
 * None
 */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_head;

	if (lst && del)
	{
		while (*lst)
		{
			if (*lst != NULL)
			{
				del((*lst)->content);
				lst_head = *lst;
				*lst = lst_head->next;
				free(lst_head);
			}
		}
		*lst = NULL;
	}
}
