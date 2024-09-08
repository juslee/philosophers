/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:40:26 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 21:33:18 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	taken_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = (philo->id - 1 + philo->data->config.number_of_philosophers)
		% philo->data->config.number_of_philosophers;
	right_fork = philo->id - 1;
	sem_wait(philo->data->forks[left_fork]);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks[right_fork]);
	print_status(philo, "has taken a fork");
}

void	eating(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	print_status(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	precise_usleep(philo->data->config.time_to_eat);
	philo->meals_eaten += 1;
	left_fork = (philo->id - 1 + philo->data->config.number_of_philosophers)
		% philo->data->config.number_of_philosophers;
	right_fork = philo->id - 1;
	sem_post(philo->data->forks[left_fork]);
	sem_post(philo->data->forks[right_fork]);
}

void	sleeping(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->data->config.time_to_sleep);
}

void	thinking(t_philosopher *philo)
{
	print_status(philo, "is thinking");
}

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
void	philosopher_routine(t_philosopher *philo)
{
	t_philo_config	config;
	pthread_t		monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &death_monitor, philo) != 0)
	{
		printf("Error: Failed to create death monitor thread.\n");
		exit(1);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	config = philo->data->config;
	while (1)
	{
		if (config.number_of_times_each_philosopher_must_eat >= 0)
		{
			if (philo->meals_eaten
				>= config.number_of_times_each_philosopher_must_eat)
				break ;
		}
		taken_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(monitor_thread, NULL);
}
