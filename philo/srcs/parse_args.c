/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:10:58 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 15:29:04 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_args(t_philo_config *config, int argc)
{
	if (config->number_of_philosophers <= 0 || config->time_to_die <= 0
		|| config->time_to_eat <= 0 || config->time_to_sleep <= 0
		|| (argc == 6
			&& config->number_of_times_each_philosopher_must_eat < 0))
	{
		printf("Error: Invalid argument(s).\n");
		return (0);
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_philo_config *config)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (0);
	}
	config->number_of_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		config->number_of_times_each_philosopher_must_eat = -1;
	return (validate_args(config, argc));
}
