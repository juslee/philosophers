/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:11:09 by welee             #+#    #+#             */
/*   Updated: 2024/09/09 00:17:12 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Log the philosopher's death.
 * @param philosopher The philosopher.
 * @note The function will lock the mutex for printing before printing the
 * philosopher's death.
 * The function will print the philosopher's ID and that the philosopher has died
 * to the console.
 * The function will unlock the mutex for printing after printing the
 * philosopher's death.
 */
static void	log_philosopher_death(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->config->print_mutex);
	printf("%ld %d died\n", get_time_in_ms() - philosopher->config->start_time,
		philosopher->id);
	pthread_mutex_unlock(&philosopher->config->print_mutex);
	philosopher->config->philo_dead = 1;
}

/**
 * @brief Check if the philosopher has died.
 * @param philosopher The philosopher.
 * @return 1 if the philosopher has died, 0 otherwise.
 * @note The function will calculate the time since the philosopher's last meal.
 * The function will return 1 if the time since the philosopher's last meal is
 * greater than the time to die.
 */
static int	is_philosopher_dead(t_philosopher *philosopher)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philosopher->config->print_mutex);
	time_since_last_meal = get_time_in_ms() - philosopher->last_meal_time;
	pthread_mutex_unlock(&philosopher->config->print_mutex);
	return (time_since_last_meal > philosopher->config->time_to_die);
}

/**
 * @brief Check if the philosophers have eaten the required number of meals.
 * @param philosophers The philosophers.
 * @param config The configuration.
 * @return 1 if the philosophers have eaten the required number of meals, 0
 * otherwise.
 * @note The function will check if each philosopher has eaten the required
 * number of meals.
 * The function will return 1 if each philosopher has eaten the required number
 * of meals.
 */
static int	check_meals_eaten(t_philosopher *philosophers,
	t_philo_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (config->number_of_times_each_philosopher_must_eat >= 0)
		{
			if (philosophers[i].meals_eaten
				>= config->number_of_times_each_philosopher_must_eat)
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Monitor the philosophers for death.
 * @param arg The philosophers.
 * @return NULL
 * @note The function will check if each philosopher has died.
 * The function will log the philosopher's death if the philosopher has died.
 */
void	*death_monitoring_routine(void *arg)
{
	t_philosopher	*philosophers;
	t_philo_config	*config;
	int				i;

	philosophers = (t_philosopher *)arg;
	config = philosophers[0].config;
	while (!config->philo_dead)
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			if (is_philosopher_dead(&philosophers[i]))
			{
				log_philosopher_death(&philosophers[i]);
				return (NULL);
			}
			i++;
		}
		if (check_meals_eaten(philosophers, config))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
