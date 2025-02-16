#include "philo.h"

void	sem_close_opened(t_info *info)
{
	sem_post(info->forks);
	sem_post(info->eat_count_sem);
	sem_post(info->died_sem);
	sem_post(info->finish_sem);
	sem_post(info->fork_guard_sem);
	sem_close(info->forks);
	sem_close(info->eat_count_sem);
	sem_close(info->print_sem);
	sem_close(info->died_sem);
	sem_close(info->finish_sem);
	sem_close(info->fork_guard_sem);
}
