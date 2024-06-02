/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:04:37 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/25 23:22:04 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Applies the function 'f' to each character of the string 's', and passing its
 * index as first argument to crate a new string (with malloc) resulting from
 * successive applications of 'f'.
 *
 * PARAMETERS
 * s:	The string on which to iterate.
 * f:	The function to apply to each character.
 *
 * EXTERNAL FUNCTIONS
 * malloc()
 *
 * RETURN VALUES
 * The string created from the successive applications of 'f', or NULL if the
 * allocation fails.
 */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;
	size_t	s_len;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	new_str = malloc((s_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
/*
#include <stdio.h>
#include <stdlib.h>

// Function to convert characters at even indices to uppercase and odd indices to lowercase
char my_custom_function(unsigned int index, char c)
{
    if (index % 2 == 0) {
        // Convert characters at even indices to uppercase
        return ft_toupper(c);
    } else {
        // Convert characters at odd indices to lowercase
        return ft_tolower(c);
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
	{
        char *new_str;

		new_str = ft_strmapi(argv[1], my_custom_function);
        if (new_str) {
            printf("Transformed string: %s\n", new_str);
            free(new_str);
        } else {
            printf("Memory allocation failed.\n");
        }
    }
    return 0;
}
*/
