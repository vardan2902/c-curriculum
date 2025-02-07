/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:20:51 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 13:22:04 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bin_to_char(int signum, char *c)
{
	*c <<= 1;
	if (signum == SIGUSR1)
		*c |= 1;
}

void	respond(int *pid, int signum)
{
	static char	c;
	static int	i;

	bin_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (c == '\0')
		{
			kill(*pid, SIGUSR1);
			ft_printf("\n"RESET);
			*pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
	kill(*pid, SIGUSR2);
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	pid;

	(void)context;
	if (pid == 0 && info->si_pid != 0)
	{
		if (signum == SIGUSR1)
		{
			pid = info->si_pid;
			ft_printf(BOLD_CYAN"[%d]"BOLD_YELLOW \
					" Connection accepted.\n"BOLD_WHITE, pid);
			kill(pid, SIGUSR2);
		}
		return ;
	}
	if (!info->si_pid)
		return ;
	if (info->si_pid && pid && pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	respond(&pid, signum);
}

int	main(void)
{
	t_sigaction	sa;

	ft_printf(BOLD_GREEN"Server is running on process: " \
			BOLD_YELLOW"%d\n"RESET, getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
