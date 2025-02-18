/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:16:40 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/18 16:55:21 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <signal.h>

# define FORKS_SEM "/philo/forks_sem"
# define EAT_COUNT_SEM "/philo/eat_count_sem"
# define STOP_SEM "/philo/stop_sem"
# define PRINT_SEM "/philo/print_sem"

typedef struct timeval	t_timeval;

typedef struct s_general_info
{
	sem_t		*forks;
	sem_t		*eat_count;
	sem_t		*stop;
	sem_t		*print;
	t_timeval	start_time;
	int			number_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			offset;
	pid_t		philos[200];
}	t_info;

typedef struct s_philo
{
	t_info		*info;
	sem_t		*meal;
	t_timeval	last_eat;
	int			num;
	int			eat_count;
}	t_philo;

void	print_state(const char *state, t_philo *philo);
void	print_usage(char *name);
int		parse_args(int argc, char *argv[], t_info *info);
void	wait_ms(int ms);
int		get_ms_from_start(t_timeval tv, int offset);
int		get_current_ms(void);
int		get_ms(t_timeval *tv);
void	*start_philo_life(t_philo *args);
void	pkill_all_ctrl(t_info *info);
void	clean_up(t_info *info);
void	kill_processes(t_info *info);
void	unlink_named_sem(void);
void	wait_untill_sim_start(t_timeval *tv, int offset);

#endif
