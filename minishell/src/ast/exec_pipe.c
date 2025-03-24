/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:07:30 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:07:31 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_fork_error(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	perror("minishell: fork");
	return (-1);
}

static int	execute_pipe_left_side(t_ast **root, t_ast **node,
	t_ht *env, int pipefd[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		status = execute_ast(root, node, env);
		ht_clear(env);
		free_ast_node(root);
		exit(status);
	}
	else if (pid < 0)
		return (handle_fork_error(pipefd));
	return (pid);
}

static int	execute_pipe_right_side(t_ast **root, t_ast **node,
	t_ht *env, int pipefd[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		status = execute_ast(root, node, env);
		ht_clear(env);
		free_ast_node(root);
		exit(status);
	}
	else if (pid < 0)
		return (handle_fork_error(pipefd));
	return (pid);
}

int	handle_pipe_exec(t_ast **root, t_ast **node, t_ht *env)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		left_status;
	int		right_status;

	if (pipe(pipefd))
		return (perror("minishell: pipe"), -1);
	left_pid = execute_pipe_left_side(root, &(*node)->left, env, pipefd);
	if (left_pid < 0)
		return (-1);
	right_pid = execute_pipe_right_side(root, &(*node)->right, env, pipefd);
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
