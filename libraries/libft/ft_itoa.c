/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:38:28 by ccarrace          #+#    #+#             */
/*   Updated: 2022/07/03 22:45:04 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
 * Allocates and returns a string representing th e integer received as 
 * an argument. Negative numbers must be handled.
 *
 * PARAMETERS
 * n:	The integer to convert.
 *
 * EXTERNAL FUNCTIONS
 * malloc()
 *
 * RETURN VAULES
 * The string representing the integer, or NULL if the allocation fails.
 *
 * COMMENTS
 * 1. Count how many digits make up the integer (ft_intlength):
 * 	- if integer is negative, add 1 to len to include the sign;
 * 	- if integer is 0, add 1 to make sure malloc allocates enough space.
 *
 * 2. Special cases to consider:
 * 	- Integer value is INT_MIN: handled with an specific function (ft_intmin)
 * 	    that behaves as predefined function "ft_strdup";
 * 	- Integer is 0; 
 * 	- Integer is negative: add char '-' at the beginning of the string,
 * 		and make integer positive multiplying it by -1.
 *
 * 3. Conversion to string (from last to first digit):
 *	- Get last digit using remainder of 10 and convert it 'up to char';
 *	- Get the rest of the integer dividing by 10;
 *	- Loop as many times as integer's length;
 *	- Add null-terminating char at the end of the string.
 *
 * 	NOTE!!!: INT_MIN can be easily handled declaring a new LONG INT variable
 * 	and assigning to it the value of INT 'n'. Thus, there is no need to write 
 * 	an specific function.
 */

#include "libft.h"

static int	ft_intlength(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_intmin(void)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	tmp = "-2147483648";
	while (i < 11)
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_intlength(n);
	if (n == -2147483648)
		return (ft_intmin());
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = n + '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
	}
	while (n > 0)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}	
	return (str);
}
