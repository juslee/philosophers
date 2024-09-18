/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:46:03 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 21:47:38 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_bonus.h"

// Function to check if a philosopher has died
static int	check_philosopher_death(t_philo_data *data, int i)
{
	long	time_since_last_meal;

	time_since_last_meal = get_time_in_ms()
		- data->philosophers[i].last_meal_time;
	if (time_since_last_meal >= data->config.time_to_die)
	{
		print_status(&data->philosophers[i], "died");
		return (1);
	}
	return (0);
}

// Function to count completed meals for all philosophers
static int	check_meal_completion(t_philo_data *data)
{
	int	i;
	int	completed_meals;

	i = 0;
	completed_meals = 0;
	while (i < data->config.number_of_philosophers)
	{
		if (data->config.number_of_times_each_philosopher_must_eat > 0
			&& data->philosophers[i].meals_eaten
			>= data->config.number_of_times_each_philosopher_must_eat)
			completed_meals++;
		i++;
	}
	if (completed_meals == data->config.number_of_philosophers)
		return (1);
	return (0);
}

// Function to monitor the simulation for death or meal completion
void	monitor_simulation(t_philo_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->config.number_of_philosophers)
		{
			if (check_philosopher_death(data, i))
				return ;
			i++;
		}
		if (check_meal_completion(data))
			return ;
		usleep(1000);
	}
}
