/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:08:29 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 21:52:17 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo_config	config;
	t_philo_data	data;

	if (!parse_args(argc, argv, &config))
		return (EXIT_FAILURE);
	if (!init_simulation(&data, &config))
		return (EXIT_FAILURE);
	if (!start_simulation(&data))
	{
		printf("Error: Simulation failed to start.\n");
		cleanup_simulation(&data);
		return (EXIT_FAILURE);
	}
	monitor_simulation(&data);
	cleanup_simulation(&data);
	return (EXIT_SUCCESS);
}
