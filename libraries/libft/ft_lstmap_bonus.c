/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:46:35 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Iterates the list 'lst' and applies the function 'f' on the content of each
 * node. Creates a new list t_resulting of the successive applications of the
 * function 'f'. The 'del' function is used to delete the content of a node if
 * needed.
 *
 * PARAMETERS
 * lst:	The address of a pointer to a node.
 * f  :	The address of the function used to iterate on the list.
 * del:	The address of the function used to delete the content of a node.
 *
 * EXTERNAL FUNCTIONS
 * malloc(), free()
 *
 * RETURN VALUES
 * The new list, or NULL if the allocation fails.:
 *
 * COMMENTS
 * Cannot pass here a function 'f(lst->content)' as a parameter to another 
 * function 'ft_lstnew()'. Solved storing first function's t_result in a
 * temporary void function (tmp) and passing it as a parameter to the second
 * function.
 */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))

{
	t_list	*new_list;
	t_list	*new_node;
	void	*tmp;

	if (lst && f)
	{
		new_list = NULL;
		while (lst)
		{
			tmp = f(lst->content);
			new_node = ft_lstnew(tmp);
			if (!new_node)
				del(tmp);
			ft_lstadd_back(&new_list, new_node);
			lst = lst->next;
		}
		return (new_list);
	}
	return (NULL);
}
