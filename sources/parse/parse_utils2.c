/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:30:25 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 13:51:54 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	
 *	is_whitespace()
 *
 *	' ' space, '\t' horizontal tab, '\r' return carriage,
 *	'\v' vertical tab, '\f' form feed
 */
int	is_whitespace(char c)
{
	if (c == ' '
		|| c == '\t'
		|| c == '\r'
		|| c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

/*
 *	trim_endings()
 *	
 *	Removes all leading and trailing whitespaces
 */
static void	trim_endings(char **src)
{
	char	*end;

	while (is_whitespace(**src))
		(*src)++;
	end = *src + ft_strlen(*src) - 1;
	while (end > *src && is_whitespace(*end))
	{
		*end = '\0';
		end--;
	}
}

/*
 *	remove_spaces_around_comma()
 *
 *	Removes absolutely all whitespaces around the commas, leaving no
 *	space between them and the adjacent words.	
 */
static void	remove_spaces_around_comma(char **src, char **dst, int *space_found)
{
	if (*dst != *src && is_whitespace(*(*dst - 1)))
		(*dst)--;
	**dst = **src;
	(*dst)++;
	(*src)++;
	while (is_whitespace(**src))
		(*src)++;
	*space_found = 0;
}

/*
 *	reduce_spaces_in_between()
 *
 *	Reduces all whitespaces between words to just one single space,
 *	but when a comma is found, all whitespaces around are removed
 * */
static void	reduce_spaces_in_between(char *src, char *dst)
{
	int	space_found;

	space_found = 0;
	while (*src != '\0')
	{
		if (is_whitespace(*src))
		{
			space_found = 1;
			src++;
		}
		else
		{
			if (*src == ',')
				remove_spaces_around_comma(&src, &dst, &space_found);
			else
			{
				if (space_found && dst != src)
					*dst++ = ' ';
				*dst++ = *src++;
				space_found = 0;
			}
		}
	}
	*dst = '\0';
}

/*
 *	trim_and_reduce_spaces()
 *
 *	Main function to process the string, removing 
 *		- any leading or trailing white space in the string
 *		- the newline ('\n') character at the end, if it exists
 *		- all whitespaces between words, leaving just one single space
 *		- Exception: when a comma is found, no whitespace will be left 
 *					between the comma and the adjacent words
 */
void	trim_and_reduce_spaces(char *line)
{
	char	*src;
	char	*dst;
	int		len;

	src = line;
	len = ft_strlen(src);
	if (len > 0 && src[len - 1] == '\n')
		src[len - 1] = '\0';
	trim_endings(&src);
	dst = (char *)malloc(len + 1);
	if (dst == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return ;
	}
	reduce_spaces_in_between(src, dst);
	ft_strlcpy(line, dst, len + 1);
	free(dst);
}
