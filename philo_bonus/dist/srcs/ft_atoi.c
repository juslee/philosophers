/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:25:09 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 18:04:33 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_atoi.c
 * @brief Convert a string to an integer.
 */

#include "philo_bonus.h"
#include <limits.h>

/**
 * @brief Check if the character is a space.
 * @param c The character to check.
 * @return Nonzero if the character c is a space and zero if not.
 */
static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

/**
 * @brief Check if the character is a digit.
 * @param c The character to check.
 * @return Nonzero if the character c is a digit and zero if not.
 */
static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Convert a string to an integer.
 * @param nptr The string to convert.
 * @return The integer value.
 * @note The function stops reading the string nptr at the first character that
 * is not a digit.
 */
int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX || result < INT_MIN)
			return (-1);
		++str;
	}
	return (result * sign);
}
