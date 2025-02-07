/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:21:00 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 13:40:30 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_flags = 0;

static void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	i;

	(void)context;
	(void)info;
	if (signum == SIGUSR2)
	{
		if (!(g_flags & HANDSHAKE_DONE))
			g_flags |= HANDSHAKE_DONE;
		else
		{
			++i;
			g_flags |= RECEIVER;
		}
	}
	else if (signum == SIGUSR1)
	{
		if (g_flags & HANDSHAKE_DONE)
		{
			ft_printf(BOLD_YELLOW"Received: %d bytes\n"RESET, i / 8);
			exit(0);
		}
		else
			g_flags |= SLEEP_INTERRUPTED;
	}
}

void	handshake(int pid)
{
	int	attempts;

	attempts = 0;
	while (!(g_flags & HANDSHAKE_DONE) && attempts < 20)
	{
		kill(pid, SIGUSR1);
		usleep(200 * 1000);
		if (!(g_flags & HANDSHAKE_DONE))
		{
			ft_printf(BOLD_CYAN"Server busy, retry.\n"RESET);
			if (g_flags & SLEEP_INTERRUPTED)
			{
				g_flags &= ~SLEEP_INTERRUPTED;
				usleep(200 * 1000);
			}
		}
		++attempts;
	}
	if (!(g_flags & HANDSHAKE_DONE))
		exit(1);
}

int	char_to_bin(char c, int pid)
{
	int	it;
	int	bit_index;

	bit_index = 8;
	while (--bit_index >= 0)
	{
		it = 0;
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!(g_flags & RECEIVER))
		{
			if (it == 50)
			{
				++bit_index;
				break ;
			}
			++it;
			usleep(100);
		}
		g_flags &= ~RECEIVER;
	}
	return (0);
}

pid_t	get_pid_or_exit(int argc, char *argv[])
{
	int		i;
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf(BOLD_RED"Usage:\t<pid>\t<message>\n"RESET);
		exit(1);
	}
	i = -1;
	while (argv[1][++i])
	{
		if (!(ft_isdigit(argv[1][i]) || ft_isspace(argv[1][i])
				|| argv[1][i] == '+'))
		{
			ft_printf(BOLD_RED"Usage:\t<pid>\t<message>\n"RESET);
			exit(1);
		}
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf(BOLD_RED"Usage:\t<pid>\t<message>\n"RESET);
		exit(1);
	}
	return (pid);
}

int	main(int argc, char *argv[])
{
	t_sigaction	sa;
	int			byte_index;
	pid_t		pid;

	pid = get_pid_or_exit(argc, argv);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	handshake(pid);
	byte_index = -1;
	while (argv[2][++byte_index])
		char_to_bin(argv[2][byte_index], pid);
	char_to_bin('\0', pid);
	return (0);
}
