/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:45:46 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 16:41:27 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
void	safe_sleep(t_philo_config *config, int ms)
{
	long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < ms)
	{
		if (config->philo_dead)
			break ;
		usleep(100);
	}
}
