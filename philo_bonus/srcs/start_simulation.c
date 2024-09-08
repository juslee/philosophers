/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:47:22 by welee             #+#    #+#             */
/*   Updated: 2024/09/09 00:22:01 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Function to start the philosopher processes
int	start_simulation(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->config.number_of_philosophers)
	{
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
		{
			printf("Error: Failed to fork philosopher %d.\n", i + 1);
			return (0);
		}
		if (data->philosophers[i].pid == 0)
		{
			philosopher_routine(&data->philosophers[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	return (1);
}
