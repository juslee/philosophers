/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:41:26 by welee             #+#    #+#             */
/*   Updated: 2024/09/09 00:19:50 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

// Config structure to store parsed arguments
typedef struct s_philo_config
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_philo_config;

// Philosopher structure
typedef struct s_philosopher
{
	int					id;
	int					last_meal_time;
	int					meals_eaten;
	pid_t				pid;
	struct s_philo_data	*data;
}	t_philosopher;

// Shared data structure
typedef struct s_philo_data
{
	t_philo_config	config;
	sem_t			**forks;
	sem_t			*print_lock;
	long			start_time;
	t_philosopher	*philosophers;
}	t_philo_data;

// Function declarations
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(const char *s1, const char *s2);
int		parse_args(int argc, char **argv, t_philo_config *config);
int		init_simulation(t_philo_data *data, t_philo_config *config);
void	philosopher_routine(t_philosopher *philo);
void	print_status(t_philosopher *philo, char *status);
int		start_simulation(t_philo_data *data);
void	monitor_simulation(t_philo_data *data);
void	cleanup_simulation(t_philo_data *data);
long	get_time_in_ms(void);
void	precise_usleep(int time_in_ms);
void	*death_monitor(void *arg);
char	*generate_sem_name(int i);

#endif
