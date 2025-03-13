#include "minishell.h"

static int	handle_heredoc(int fd, const char *delimiter, t_ht *env)
{
	char	*line;
	bool	is_not_a_tty;;

	is_not_a_tty = ht_get(env, "#ISNOTATTY");
	while (1)
	{
		if (is_not_a_tty)
			line = ft_strtrim(get_next_line(STDIN_FILENO), "\n");
		else
			line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	return (fd);
}

static t_char_arr	*expand_and_validate_target(const char *target, t_ht *env)
{
	t_char_arr	*expanded;

	expanded = expand_text(target, env);
	if (!expanded || !expanded->arr || !*expanded->arr || !**expanded->arr)
		return (NULL);
	expand_wildcards(expanded);
	remove_quotes(expanded);
	return (expanded);
}

static int	open_redirection_file(t_redirection *redir, const char *target)
{
	int	fd;

	if (redir->type == T_INPUT)
		fd = open(target, O_RDONLY);
	else if (redir->type == T_OUTPUT)
		fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == T_HEREDOC)
	{
		unlink(".heredoc");
		fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
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
	free(target->arr);
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

int	handle_redirection(t_redirection *redir, t_ht *env)
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
	if (redir->type == T_HEREDOC)
		fd = handle_heredoc(fd, redir->target, env);
	if (setup_redirection_fd(fd, redir) < 0)
	{
		close(fd);
		return (handle_redirection_error(target));
	}
	free(target->arr);
	free(target);
	close(fd);
	unlink(".heredoc");
	return (0);
}

int	handle_redirections(t_list *redir_lst, t_ht *env)
{
	while (redir_lst)
	{
		if (handle_redirection((t_redirection *)redir_lst->content, env) != 0)
			return (1);
		redir_lst = redir_lst->next;
	}
	return (0);
}

int	handle_redirections_and_restore(t_list *redirections,
	t_ht *env, int saved_stdin, int saved_stdout)
{
	if (handle_redirections(redirections, env) != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	return (0);
}
