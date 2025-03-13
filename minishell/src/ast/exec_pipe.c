#include "minishell.h"

static void	setup_pipe_for_child(int pipefd[2], int side)
{
	if (side == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

static int	handle_fork_error(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	perror("minishell: fork");
	return (-1);
}

static int	execute_pipe_side(t_ast *node, t_ht *env, int pipefd[2], int side)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_pipe_for_child(pipefd, side);
		exit(execute_ast(node, env));
	}
	else if (pid < 0)
		return (handle_fork_error(pipefd));
	return (pid);
}

static void	ignore_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	execute_pipe(t_ast *node, t_ht *env)
{
	int					pipefd[2];
	pid_t				left_pid;
	pid_t				right_pid;
	int					left_status;
	int					right_status;

	if (pipe(pipefd))
		return (perror("minishell: pipe"), -1);
	left_pid = execute_pipe_side(node->left, env, pipefd, 0);
	if (left_pid < 0)
		return (-1);
	right_pid = execute_pipe_side(node->right, env, pipefd, 1);
	if (right_pid < 0)
		return (kill(left_pid, SIGKILL), -1);
	close(pipefd[0]);
	close(pipefd[1]);
	ignore_signals();
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
	setup_signals();
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	return (0);
}
