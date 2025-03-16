#include "minishell.h"

static int	handle_heredoc(int fd, const char *delimiter, t_ht *env, int saved_stdin)
{
	char		*line;
	bool		is_not_a_tty;
	char		*lim;
	char		lim_fd;
	t_char_arr	target;

	target.size = 1;
	target.arr = (char **)ft_calloc(2, sizeof (char *));
	if (!target.arr)
		return (-1);
	target.arr[0] = ft_strdup(delimiter);
	remove_quotes(&target);
	is_not_a_tty = ht_get(env, "#ISNOTATTY");
	if (is_not_a_tty)
	{
		lim = ft_strjoin(ht_get(env, "#BASE_PATH"), "/.lim");
		lim_fd = open(lim, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (lim_fd < 0)
			return (-1);
		while (get_next_line(lim_fd))
			;
		ft_putendl_fd(*target.arr, lim_fd);
		close(lim_fd);
	}
	while (1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		if (is_not_a_tty)
			line = ft_strtrim(get_next_line(STDIN_FILENO), "\n");
		else
			line = readline("> ");
		if (!line || !ft_strcmp(line, *target.arr))
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

int	handle_redirection(t_redirection *redir, t_ht *env, int saved_stdin)
{
	int			fd;
	t_char_arr	*target;

	target = NULL;
	if (redir->type != T_HEREDOC)
	{
		target = expand_and_validate_target(redir->target, env);
		if (!target)
			return (1);
		if (target->size > 1)
		{
			print_error("minishell: ", redir->target, ": ambiguous redirect");
			return (1);
		}
		fd = open_redirection_file(redir, *target->arr);
	}
	else
	{
		unlink(".heredoc");
		fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fd = handle_heredoc(fd, redir->target, env, saved_stdin);
	}
	if (fd < 0)
		return (handle_redirection_error(target));
	if (setup_redirection_fd(fd, redir) < 0)
	{
		close(fd);
		return (handle_redirection_error(target));
	}
	if (target)
	{
		free(target->arr);
		free(target);
	}
	close(fd);
	unlink(".heredoc");
	return (0);
}

int	handle_redirections(t_list *redir_lst, t_ht *env, int saved_stdin)
{
	while (redir_lst)
	{
		if (handle_redirection((t_redirection *)redir_lst->content, env, 
				saved_stdin) != 0)
			return (1);
		redir_lst = redir_lst->next;
	}
	return (0);
}

int	handle_redirections_and_restore(t_list *redirections,
	t_ht *env, int saved_stdin, int saved_stdout)
{
	if (handle_redirections(redirections, env, saved_stdin) != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	return (0);
}
