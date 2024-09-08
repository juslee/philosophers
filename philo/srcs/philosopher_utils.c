/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:59:23 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 17:02:17 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Lock the forks.
 * @param first The first fork.
 * @param second The second fork.
 * @param philo The philosopher.
 * @return 1 if the forks are locked, 0 otherwise.
 */
static int	lock_forks(pthread_mutex_t *first, pthread_mutex_t *second,
	t_philosopher *philo)
{
	pthread_mutex_lock(first);
	print_status(philo, "has taken a fork");
	if (philo->config->philo_dead)
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	print_status(philo, "has taken a fork");
	if (philo->config->philo_dead)
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (0);
	}
	return (1);
}

/**
 * @brief Taken the forks.
 * @param philo The philosopher.
 * @note The function will lock the mutexes for the forks.
 * The function will print a message to the console to indicate that the
 * philosopher has taken a fork.
 * The function will lock the mutex for the left fork first if the philosopher's
 * ID is odd.
 * The function will lock the mutex for the right fork first if the philosopher's
 * ID is even.
 */
void	taken_forks(t_philosopher *philo)
{
	if (philo->config->philo_dead)
		return ;
	if (philo->id % 2 == 1)
	{
		if (!lock_forks(philo->left_fork, philo->right_fork, philo))
			return ;
	}
	else
	{
		if (!lock_forks(philo->right_fork, philo->left_fork, philo))
			return ;
	}
}

/**
 * @brief Eating.
 * @param philo The philosopher.
 * @note The function will lock the mutex for the state before updating the last
 * meal time.
 * The function will print a message to the console to indicate that the
 * philosopher is eating.
 * The function will sleep for a specified amount of time to simulate the
 * philosopher eating.
 * The function will increment the number of meals eaten by the philosopher.
 * The function will unlock the mutex for the state after updating the last meal
 * time.
 */
void	eating(t_philosopher *philo)
{
	if (philo->config->philo_dead)
		return ;
	pthread_mutex_lock(&philo->config->state_mutex);
	philo->last_meal_time = get_time_in_ms();
	print_status(philo, "is eating");
	safe_sleep(philo->config, philo->config->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->config->state_mutex);
}

/**
 * @brief Sleeping.
 * @param philo The philosopher.
 * @note The function will print a message to the console to indicate that the
 * philosopher is sleeping.
 * The function will sleep for a specified amount of time to simulate the
 * philosopher sleeping.
 * The function will print a message to the console to indicate that the
 * philosopher is thinking.
 */
void	sleeping(t_philosopher *philo)
{
	if (philo->config->philo_dead)
		return ;
	pthread_mutex_lock(&philo->config->state_mutex);
	print_status(philo, "is sleeping");
	safe_sleep(philo->config, philo->config->time_to_sleep);
	pthread_mutex_unlock(&philo->config->state_mutex);
}

/**
 * @brief Thinking.
 * @param philo The philosopher.
 * @note The function will print a message to the console to indicate that the
 * philosopher is thinking.
 */
void	thinking(t_philosopher *philo)
{
	if (philo->config->philo_dead)
		return ;
	pthread_mutex_lock(&philo->config->state_mutex);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->config->state_mutex);
}
