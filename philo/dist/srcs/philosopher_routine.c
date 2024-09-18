/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:40:26 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 17:03:24 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief The philosopher routine.
 * @param arg The philosopher.
 * @return NULL.
 * @note The philosopher routine is the main routine for each philosopher thread.
 * The function will run in a loop until the philosopher has eaten the specified
 * number of meals or the philosopher has died.
 * The function will take the forks.
 * The function will eat.
 * The function will sleep.
 * The function will think.
 * The function will exit the loop if the philosopher has eaten the specified
 * number of meals.
 */
void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!philo->config->philo_dead)
	{
		if (philo->config->number_of_times_each_philosopher_must_eat >= 0)
		{
			if (philo->meals_eaten
				>= philo->config->number_of_times_each_philosopher_must_eat)
				break ;
		}
		taken_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
