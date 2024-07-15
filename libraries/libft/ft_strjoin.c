/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:53:43 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/09 23:46:24 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Allocates and returns a new string, which is the t_result of the concatenation
 * of 's1' and 's2'.
 *
 * EXTERNAL FUNCTIONS
 * malloc()
 *
 * RETURN VALUES
 * The new string, or NULL if the allocation fails.
 *
 * COMMENTS
 * There's a shorter way to write this function, calling ft_strlcpy to copy s1
 * in the new string and strlcat to concatenate the newstring and s2 (see below)
 */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

/* SHORTER VERSION
 *
 * 	char	*ft_strjoin(char const *s1, char const *s2)
 *	{
 *		char	*newstr;
 *
 *  	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
 *		if (!s1 || !s2 || !newstr)
 *			return (NULL);
 *		ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
 *		ft_strlcat(newstr, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
 *		return (newstr);
 *	}
 */	
