#include "philo.h"

void	pkill_all_ctrl(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
		kill(info->philos[i], SIGKILL);
}
