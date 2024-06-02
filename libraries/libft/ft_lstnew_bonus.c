/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:48:59 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Allocates and returns a new node. The member variable 'content' 
 * is initialized with the value of the parameter 'content'. The
 * variable 'next' is initialized to NULL.
 *
 * PARAMETERS
 * content: The content to create the node with
 *
 * EXTERNAL FUNCTIONS
 * malloc()
 *
 * RETURN VALUES
 * The new node
 */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
