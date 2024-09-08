/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:31:39 by welee             #+#    #+#             */
/*   Updated: 2024/09/09 00:22:23 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*generate_sem_name(int i)
{
	char	*num_str;
	char	*sem_name;

	num_str = ft_itoa(i);
	if (!num_str)
		return (NULL);
	sem_name = ft_strjoin("/fork_", num_str);
	free(num_str);
	return (sem_name);
}

// Helper function to initialize individual fork semaphores
static int	init_fork_semaphores(t_philo_data *data)
{
	int		i;
	char	*sem_name;

	i = 0;
	while (i < data->config.number_of_philosophers)
	{
		sem_name = generate_sem_name(i);
		if (!sem_name)
			return (0);
		sem_unlink(sem_name);
		data->forks[i] = sem_open(sem_name, O_CREAT, 0644, 1);
		free(sem_name);
		if (data->forks[i] == SEM_FAILED)
		{
			while (i-- > 0)
			{
				sem_close(data->forks[i]);
				sem_unlink(generate_sem_name(i));
			}
			return (0);
		}
		i++;
	}
	return (1);
}

// Function to initialize all semaphores
static int	init_semaphores(t_philo_data *data)
{
	int	i;

	data->forks = (sem_t **)malloc(sizeof(sem_t *)
			* data->config.number_of_philosophers);
	if (!data->forks)
		return (0);
	if (!init_fork_semaphores(data))
	{
		free(data->forks);
		return (0);
	}
	sem_unlink("/print_lock");
	data->print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
	if (data->print_lock == SEM_FAILED)
	{
		i = -1;
		while (i++ < data->config.number_of_philosophers)
		{
			sem_close(data->forks[i]);
			sem_unlink(generate_sem_name(i));
		}
		free(data->forks);
		return (0);
	}
	return (1);
}

// Function to initialize the philosopher array
static int	init_philosophers(t_philo_data *data)
{
	int	i;

	data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* data->config.number_of_philosophers);
	if (!data->philosophers)
		return (0);
	i = 0;
	while (i < data->config.number_of_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].data = data;
		i++;
	}
	return (1);
}

int	init_simulation(t_philo_data *data, t_philo_config *config)
{
	int	i;

	data->config = *config;
	if (!init_semaphores(data))
	{
		printf("Error: Failed to initialize semaphores.\n");
		return (0);
	}
	if (!init_philosophers(data))
	{
		i = -1;
		while (i++ < data->config.number_of_philosophers)
		{
			sem_close(data->forks[i]);
			sem_unlink(generate_sem_name(i));
		}
		sem_close(data->print_lock);
		sem_unlink("/print_lock");
		free(data->forks);
		printf("Error: Failed to initialize philosophers.\n");
		return (0);
	}
	data->start_time = get_time_in_ms();
	return (1);
}
