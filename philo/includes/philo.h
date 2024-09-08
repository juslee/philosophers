/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:53:20 by welee             #+#    #+#             */
/*   Updated: 2024/09/09 00:14:17 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

// Structure to hold philosopher configuration
typedef struct s_philo_config
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				philo_dead;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	long			start_time;
}	t_philo_config;

// Structure to hold philosopher data
typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	t_philo_config	*config;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

// Argument parsing
int		ft_atoi(const char *str);
int		parse_args(int argc, char **argv, t_philo_config *config);

// Resource management
int		init_mutexes(pthread_mutex_t *forks, t_philo_config *config);
void	init_philosophers(t_philosopher *philosophers, t_philo_config *config,
			pthread_mutex_t *forks);
int		create_threads(pthread_t *threads, pthread_t *death_monitor_thread,
			t_philosopher *philosophers, t_philo_config *config);
void	join_threads(pthread_t *threads, pthread_t death_monitor_thread,
			t_philo_config *config);
void	cleanup_resources(pthread_t *threads, t_philosopher *philosophers,
			pthread_mutex_t *forks, t_philo_config *config);

// Philosopher routines
void	*philosopher_routine(void *arg);
void	taken_forks(t_philosopher *philo);
void	eating(t_philosopher *philo);
void	sleeping(t_philosopher *philo);
void	thinking(t_philosopher *philo);
void	*death_monitoring_routine(void *arg);

// Helper functions for printing
void	print_status(t_philosopher *philo, const char *status);

// Helper functions for timing and sleeping
long	get_time_in_ms(void);
void	safe_sleep(t_philo_config *config, int ms);

#endif // PHILO_H
