/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:01:57 by welee             #+#    #+#             */
/*   Updated: 2024/09/09 00:13:16 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
void	print_status(t_philosopher *philo, char *status)
{
	long	timestamp;

	timestamp = get_time_in_ms() - philo->data->start_time;
	sem_wait(philo->data->print_lock);
	printf("%ld %d %s\n", timestamp, philo->id, status);
	sem_post(philo->data->print_lock);
}
