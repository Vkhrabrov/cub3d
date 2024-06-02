/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:09:32 by ccarrace          #+#    #+#             */
/*   Updated: 2024/05/26 22:54:08 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Appends string 'src' to the end of 'dst'. It will append at most (dstsize -
 * strlen(dst) - 1) characters. It will then NUL-terminate, unless dstsize is 0.
 * 
 * RETURN VALUES
 * The initial length of 'dst' plus the length of 'src'.
 *
 * COMMENTS
 * Be clear that 'dstsize' first includes the string 'dst' and then appends 'src'
 * Hence to concatenate both string, 'dstsize' value should be the initial length
 * of 'dst' plus the length of 'src'. In this case, 'dstsize' is returned.
 *
 * If 'dstsize' is smaller, 'src' will be truncated when appended at the end of 
 * 'dst'. Anyhow, the returned value will stil be the length of the desired 
 * string (the initial length of 'dst' plus the length of 'src'). 
 *
 * Just in case 'dstsize' is even smaller than the length of 'dst' (which means
 * 'dst' should be truncated), the returned value will be 'dstsize' plus the 
 * length of 'src'.
 */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;
	size_t	dst_length;
	size_t	i;

	i = 0;
	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	if (dstsize == 0)
		return (src_length);
	while (src[i] != '\0' && (dst_length + i) < (dstsize - 1))
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	if (dstsize >= dst_length)
		return (dst_length + src_length);
	return (dstsize + src_length);
}

// #include <string.h>
// int	main(void)
// {
// 	char dst[15] = "Hello";
// 	char src[] = " World!";

// 	char dst1[15] = "Hello";
// 	char src1[] = " World!";

// 	printf("\nstrlcat returned value    = %lu\n",  strlcat(dst, src, ));
// 	printf("strlcat dst   : %s\n", dst);
// 	printf("-------------------------------\n");
// 	printf("ft_strlcat returned value = %lu\n",  ft_strlcat(dst1, src1, 15));	
// 	printf("ft_strlcat ds : %s\n\n", dst1);
// 	return (0);
// } 	
#include <string.h>
/*int	main(void)
{
    char dst[15] = "Hello";
    char src[] = ".World!";

    char dst1[15] = "Hello";
    char src1[] = ".World!";

    printf("strlcat returned value      : %lu\n", strlcat(dst, src, 7));
    printf("strlcat concatenated dst    : %s\n", dst);
    printf("--------------------\n");
    printf("ft_strlcat returned value   : %lu\n", ft_strlcat(dst1, src1, 7));
    printf("ft_strlcat concatenated dst : %s\n", dst1);

    return (0);
}*/
