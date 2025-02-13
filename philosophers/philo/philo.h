/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:16:40 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/13 21:05:52 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define YELLOW "\e[0;33m"
# define CYAN "\e[0;36m"
# define GREEN "\e[0;32m"
# define HGREEN "\e[0;92m"
# define RED "\e[0;31m"
# define RESET "\e[0m"

typedef struct timeval	t_timeval;

typedef struct s_general_info
{
	t_timeval	start_time;
	int			number_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			philo_died;
	int			finished;
}	t_general_info;

typedef struct s_philos_and_forks
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}	t_philos_and_forks;

typedef struct s_philo
{
	t_timeval			*last_eat;
	t_philos_and_forks	*pf;
	t_general_info		*info;
	int					num;
	int					eat_count;
	int					eating;
}	t_philo;

void	print_fork_taken(int ms, t_philo *philo);
void	print_eating(int ms, t_philo *philo);
void	print_sleeping(int ms, t_philo *philo);
void	print_thinking(int ms, t_philo *philo);
void	print_died(int ms, t_philo *philo);
void	print_usage(char *name);
int		parse_args(int argc, char *argv[], t_general_info *info);
int		philo_atoi(const char *str);
void	wait_ms(int ms, t_general_info *info);
int		get_ms_from_start(t_timeval tv);
int		get_current_ms(void);
int		get_ms(t_timeval *tv);
void	*philo_live_cycle_routine(void *args);

#endif
