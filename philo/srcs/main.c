/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:08:29 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 16:57:05 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_config	config;
	pthread_t		*threads;
	pthread_t		death_monitor_thread;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;

	if (!parse_args(argc, argv, &config))
		return (EXIT_FAILURE);
	threads = malloc(sizeof(pthread_t) * config.number_of_philosophers);
	philosophers = malloc(sizeof(t_philosopher)
			* config.number_of_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * config.number_of_philosophers);
	if (!threads || !philosophers || !forks)
		return (EXIT_FAILURE);
	if (!init_mutexes(forks, &config))
		return (EXIT_FAILURE);
	init_philosophers(philosophers, &config, forks);
	if (!create_threads(threads, &death_monitor_thread, philosophers, &config))
		return (EXIT_FAILURE);
	join_threads(threads, death_monitor_thread, &config);
	cleanup_resources(threads, philosophers, forks, &config);
	return (EXIT_SUCCESS);
}
