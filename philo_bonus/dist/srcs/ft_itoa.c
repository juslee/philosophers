/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:05:10 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 21:03:54 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_itoa.c
 * @brief Convert an integer to a string
 */

#include <stdlib.h>

/**
 * @brief Count the number of digits in an integer
 * @param n The integer to count the digits
 * @return The number of digits
 */
static int	ft_count_digits(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/**
 * @brief Fill the string with the integer
 * @param str The string to fill
 * @param n The integer to convert
 * @param len The length of the string
 * @param sign The sign of the integer
 */
static void	ft_fill_str(char *str, int n, int len, int sign)
{
	int	i;
	int	digit;

	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return ;
	}
	if (sign)
		str[0] = '-';
	i = len - 1;
	while (n != 0)
	{
		digit = n % 10;
		if (n < 0)
			digit = -digit;
		str[i--] = '0' + digit;
		n /= 10;
	}
}

/**
 * @brief Convert an integer to a string
 * @param n The integer to convert
 * @return The string representation of the integer
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	sign = n < 0;
	len = ft_count_digits(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_fill_str(str, n, len, sign);
	return (str);
}
