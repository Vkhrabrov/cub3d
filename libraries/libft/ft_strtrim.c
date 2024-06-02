/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:56:54 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:43:19 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Allocates and returns a copy of 's1' with the characters specified in 
 * 'set' removed form the beginning and the end of the string. 
 *
 * EXTERNAL FUNCTIONS
 * malloc() 
 *
 * RETURN VALUES
 * The trimmed string, or NULL if allocation fails.
 *
 * COMMENTS
 * The function looks for occurrences of ANY OF the set's character (NOT 
 * NECESSARILY ALL OF THEM) starting from the beginning of 's1' until first 
 * non-occurrence is found. Then it does the same at the end of 's1', and 
 * returns the substring with the ocurrences removed.
 *
 * There is no standard library in c that includes a similar function. Trimming
 * is mainly used to remove all kind of undesired blank spaces at either the
 * beggining or the end of the string:
 * 		'' space, '\n' new line, '\t' horizontal tab, '\v' vertical tab, 
 * 		'\f' form feed, '\r' carriage return
 * However, the subject demands removing not only blank spaces but any character 
 * or characters specified in the 'set' parameter. So the function uses our
 * previously defined function 'ft_strchr' to check occurrences of 'set' chars
 * in the string 's1'.
 *  - A first while loop counts 'i' occurrences found at the beginning of 's1'
 *  - Next we calculate the length of 's1' and store it in 'len'; 
 *  - A second while loop substracts from 'len' every time an occurrence is 
 *  	found at the end of 's1'. When loop ends len does not include the 'set'
 *  	ending characters.
 *  - finally we call 'ft_substr' to extract a substring from 's1' that begins 
 *  	at 'i' position and ends at 'len - i' position (remember now len is 
 *  	NOT the original length of the string because it does not count the 
 *  	'set' characters at the end).i
 *
 * 	NOTE: Below there's a shorter and smarter version using previously defined 
 * 		  functions (ft_strchr() to look for occurrences and ft_substr() to 
 * 		  create the new substring). 		  
 */

#include "libft.h"

int	ft_start_occurrences(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	occurrences;

	i = 0;
	j = 0;
	occurrences = 0;
	while (s1[i] != '\0')
	{
		while (set[j] != '\0')
		{
			if (s1[i] != set[j])
				j++;
			else
			{
				occurrences++;
				j = 0;
				break ;
			}
		}
		i++;
	}
	return (occurrences);
}

int	ft_end_occurrences(char const *s1, char const *set)
{
	int	j;
	int	occurrences;
	int	s1_len;

	j = 0;
	occurrences = 0;
	s1_len = ft_strlen(s1);
	while ((s1_len - 1) > 0)
	{
		while (set[j] != 0)
		{
			if (s1[s1_len - 1] != set[j])
				j++;
			else
			{
				occurrences++;
				j = 0;
				break ;
			}
		}
		s1_len--;
	}
	return (occurrences);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*substr;
	int		len_substr;
	int		i;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len_substr = ft_strlen(s1) - ft_start_occurrences(s1, set)
		- ft_end_occurrences(s1, set);
	if (len_substr <= 0)
		return (ft_strdup(""));
	substr = malloc ((len_substr + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len_substr)
	{
		substr[i] = s1[ft_start_occurrences(s1, set) + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/* 
 * SHORTER VERSION of the function

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*newstr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	len = ft_strlen(s1);
	while (((len - i) > 0) && ft_strchr(set, s1[len - 1]))
		len--;
	newstr = ft_substr((char *) s1, i, len - i);
	return (newstr);
}

*/
