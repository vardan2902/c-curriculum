#include "minishell.h"

static t_char_arr	*expand_and_validate_target(const char *target, t_ht *env)
{
	t_char_arr	*expanded;

	expanded = expand_text(target, env);
	if (!expanded)
		return (NULL);
	if (!expanded->arr || !*expanded->arr || !**expanded->arr)
		return (free_char_arr(expanded), NULL);
	expand_wildcards(expanded);
	remove_quotes(expanded);
	return (expanded);
}

static int	open_redirection_file(t_redirection *redir, const char *target)
{
	int	fd;

	if (redir->type == T_INPUT || redir->type == T_HEREDOC)
		fd = open(target, O_RDONLY);
	else if (redir->type == T_OUTPUT)
		fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

static int	handle_redirection_error(t_char_arr *target)
{
	char	*err;

	err = ft_strjoin(": ", strerror(errno));
	print_error("minishell: ", *target->arr, err);
	free(err);
	free_char_arr(target);
	free(target);
	return (1);
}

static int	setup_redirection_fd(int fd, t_redirection *redir)
{
	if (fd != -1 && (redir->type == T_INPUT || redir->type == T_HEREDOC))
		dup2(fd, STDIN_FILENO);
	else if (fd != -1 && (redir->type == T_APPEND || redir->type == T_OUTPUT))
		dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	handle_redirection(char *cmd, t_redirection *redir, t_ht *env)
{
	int			fd;
	t_char_arr	*target;

	target = expand_and_validate_target(redir->target, env);
	if (!target)
		return (1);
	if (target->size > 1)
	{
		print_error("minishell: ", redir->target, ": ambiguous redirect");
		return (1);
	}
	fd = open_redirection_file(redir, *target->arr);
	if (fd < 0)
		return (handle_redirection_error(target));
	if (cmd && setup_redirection_fd(fd, redir) < 0)
	{
		close(fd);
		return (handle_redirection_error(target));
	}
	free_char_arr(target);
	free(target);
	close(fd);
	return (0);
}

int	handle_redirections(t_cmd *cmd, t_ht *env)
{
	t_list	*redir_lst;

	redir_lst = cmd->redirections;
	while (redir_lst)
	{
		if (handle_redirection(cmd->name, (t_redirection *)redir_lst->content, env) != 0)
			return (1);
		redir_lst = redir_lst->next;
	}
	return (0);
}

int	handle_redirections_and_restore(t_cmd *cmd,
	t_ht *env, int saved_stdin, int saved_stdout)
{
	if (handle_redirections(cmd, env) != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	return (0);
}
