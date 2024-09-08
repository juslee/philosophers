/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:30:53 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 22:01:39 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_monitor(void *arg)
{
	t_philosopher	*philo;
	long			time_since_last_meal;

	philo = (t_philosopher *)arg;
	while (1)
	{
		time_since_last_meal = get_time_in_ms() - philo->last_meal_time;
		if (time_since_last_meal >= philo->data->config.time_to_die)
		{
			print_status(philo, "died");
			sem_wait(philo->data->print_lock);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}
