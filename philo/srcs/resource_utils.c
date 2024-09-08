/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:56:28 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 17:16:17 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initialize the mutexes.
 * @param forks The forks.
 * @param config The configuration.
 * @return 1 if the mutexes are initialized, 0 otherwise.
 */
int	init_mutexes(pthread_mutex_t *forks, t_philo_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&config->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&config->state_mutex, NULL) != 0)
		return (0);
	config->philo_dead = 0;
	return (1);
}

/**
 * @brief Initialize the philosophers.
 * @param philosophers The philosophers.
 * @param config The configuration.
 * @param forks The forks.
 */
void	init_philosophers(t_philosopher *philosophers,
		t_philo_config *config, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].config = config;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1)
			% config->number_of_philosophers];
		philosophers[i].meals_eaten = 0;
		philosophers[i].last_meal_time = get_time_in_ms();
		i++;
	}
}

/**
 * @brief Create the threads.
 * @param threads The threads.
 * @param death_monitor_thread The death monitor thread.
 * @param philosophers The philosophers.
 * @param config The configuration.
 * @return 1 if the threads are created, 0 otherwise.
 */
int	create_threads(pthread_t *threads, pthread_t *death_monitor_thread,
		t_philosopher *philosophers, t_philo_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				&philosophers[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(death_monitor_thread, NULL, death_monitoring_routine,
			philosophers) != 0)
		return (0);
	return (1);
}

/**
 * @brief Join the threads.
 * @param threads The threads.
 * @param death_monitor_thread The death monitor thread.
 * @param config The configuration.
 */
void	join_threads(pthread_t *threads, pthread_t death_monitor_thread,
		t_philo_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(death_monitor_thread, NULL);
}

/**
 * @brief Cleanup the resources.
 * @param threads The threads.
 * @param philosophers The philosophers.
 * @param forks The forks.
 * @param config The configuration.
 */
void	cleanup_resources(pthread_t *threads, t_philosopher *philosophers,
		pthread_mutex_t *forks, t_philo_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&config->print_mutex);
	pthread_mutex_destroy(&config->state_mutex);
	free(threads);
	free(philosophers);
	free(forks);
}
