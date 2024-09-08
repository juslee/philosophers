/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:01:57 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 16:42:45 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Print the philosopher's status.
 * @param philo The philosopher.
 * @param status The status message.
 * @note The function will lock the mutex for printing before printing the status
 * message.
 * The function will print the philosopher's ID, the current time, and the status
 * message to the console.
 * The function will unlock the mutex for printing after printing the status
 * message.
 * The function will not print the status message if the philosopher is dead.
 */
void	print_status(t_philosopher *philo, const char *status)
{
	pthread_mutex_lock(&philo->config->print_mutex);
	if (!philo->config->philo_dead)
		printf("%ld %d %s\n", get_time_in_ms(), philo->id, status);
	pthread_mutex_unlock(&philo->config->print_mutex);
}
