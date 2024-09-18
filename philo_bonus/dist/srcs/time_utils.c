/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:45:46 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 21:58:48 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Get the current time in milliseconds.
 * @return The current time in milliseconds.
 */
long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief Sleep for a specified number of milliseconds.
 * @param ms The number of milliseconds to sleep.
 */
void	precise_usleep(int time_in_ms)
{
	long	start_time;
	long	current_time;

	start_time = get_time_in_ms();
	while (1)
	{
		current_time = get_time_in_ms();
		if ((current_time - start_time) >= time_in_ms)
			break ;
		usleep(100);
	}
}
