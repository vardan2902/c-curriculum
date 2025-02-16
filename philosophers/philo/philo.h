/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:16:40 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/16 20:44:28 by vapetros         ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_general_info
{
	pthread_mutex_t		eat_count_mutex;
	pthread_mutex_t		print_mutex;
	t_timeval			start_time;
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					total_ate;
	int					finished;
}	t_info;

typedef struct s_philos_and_forks
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}	t_pf;

typedef struct s_philo
{
	t_timeval		*last_eat;
	t_pf			*pf;
	t_info			*info;
	int				num;
	int				eat_count;
	pthread_mutex_t	died;
}	t_philo;

void	print_state(const char *state, t_philo *philo);
void	print_usage(char *name);
int		parse_args(int argc, char *argv[], t_info *info);
void	wait_ms(int ms, t_info *info);
int		get_ms_from_start(t_timeval tv);
int		get_current_ms(void);
int		get_ms(t_timeval *tv);
void	*philo_routine(void *args);

#endif
