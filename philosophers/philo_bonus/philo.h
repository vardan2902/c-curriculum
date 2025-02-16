/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:16:40 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/14 22:20:51 by vapetros         ###   ########.fr       */
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
# define DIED_SEM "/philo/died_sem"
# define PRINT_SEM "/philo/print_sem"
# define FINISH_SEM "/philo/finish_sem"
# define FORK_GUARD_SEM "/philo/fork_guard_sem"

typedef struct timeval	t_timeval;

typedef struct s_general_info
{
	pid_t		*philos;
	sem_t		*forks;
	sem_t		*eat_count_sem;
	sem_t		*died_sem;
	sem_t		*print_sem;
	sem_t		*finish_sem;
	sem_t		*fork_guard_sem;
	t_timeval	start_time;
	int			number_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
}	t_info;

typedef struct s_philo
{
	t_info		*info;
	t_timeval	last_eat;
	int			num;
	int			eat_count;
}	t_philo;

void	print_state(const char *state, t_philo *philo);
void	print_usage(char *name);
int		parse_args(int argc, char *argv[], t_info *info);
void	wait_ms(int ms);
int		get_ms_from_start(t_timeval tv);
int		get_current_ms(void);
int		get_ms(t_timeval *tv);
void	*start_philo_life(t_philo *args);
void	pkill_all_ctrl(t_info *info);
void	sem_close_opened(t_info *info);

#endif
