/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:51:29 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/09 23:41:54 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Takes as a paramenter a node and frees the memory of the node's content using
 * the function 'del' given as a parameter and free the node. 
 * The memory of 'next' must not be freed.
 *
 * PARAMETERS
 * lst: The node to free.
 * del: The address of the function used to delete the content.
 *
 * EXTERNAL FUNCTIONS
 * free()
 *
 * RETURN VALUE
 * None
 */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}
