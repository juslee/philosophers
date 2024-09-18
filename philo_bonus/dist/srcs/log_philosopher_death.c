/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_philosopher_death.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:22:55 by welee             #+#    #+#             */
/*   Updated: 2024/09/08 18:34:28 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	log_philosopher_death(t_philo_config *config, int id)
{
	sem_wait(config->log_sem);
	printf("%ld %d died\n", get_time_in_ms() - config->start_time, id);
	config->philo_dead = 1;
	sem_post(config->log_sem);
}
