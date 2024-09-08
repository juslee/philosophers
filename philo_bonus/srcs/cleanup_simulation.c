/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:39:16 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 21:40:00 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Function to free allocated memory and clean up semaphores
void	cleanup_simulation(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->config.number_of_philosophers)
	{
		sem_close(data->forks[i]);
		sem_unlink(generate_sem_name(i));
		i++;
	}
	free(data->forks);
	sem_close(data->print_lock);
	sem_unlink("/print_lock");
	free(data->philosophers);
}
