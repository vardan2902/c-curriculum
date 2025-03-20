#include "minishell.h"

static char	*handle_heredoc(char *delimiter, t_ht *env)
{
	char		*line;
	bool		is_not_a_tty;
	t_char_arr	target;
	bool		target_contains_quotes;
	char 		*heredoc;
	int			fd;

	int i = 0;
	while (1)
	{
		char *sym = ft_itoa(i);
		heredoc = ft_strjoin(".heredoc_", sym);
		if (access(heredoc, F_OK) == 0)
		{
			free(sym);
			free(heredoc);
			++i;
			continue ;
		}
		free(sym);
		fd = open(heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		target.size = 1;
		target.arr = (char **)ft_calloc(2, sizeof (char *));
		if (!target.arr)
			return (NULL);
		target.arr[0] = ft_strdup(delimiter);
		target_contains_quotes = ft_strchr(*target.arr, '\'') || ft_strchr(*target.arr, '"');
		remove_quotes(&target);
		is_not_a_tty = ht_get(env, "#ISNOTATTY");
		while (1)
		{
			if (is_not_a_tty)
				line = ft_strtrim(get_next_line(STDIN_FILENO), "\n"); // Memory leak
			else
				line = readline("> ");
			if (!line || !ft_strcmp(line, *target.arr))
				break ;
			int	i = -1;
			char *key;
			char *value;
			while (line[++i])
			{
				if (!target_contains_quotes && line[i] == '$')
				{
					key = extract_var_name(line, &i);
					if (!key)
						continue ;
					value = ht_get(env, key);
					free(key);
					if (!value)
						continue ;
					ft_putstr_fd(value, fd);
				}
				else
					ft_putchar_fd(line[i], fd);
			}
			ft_putchar_fd('\n', fd);
			free(line);
		}
		close(fd);
		break ;
	}
	return (heredoc);
}


static t_redirection	*create_redirection(t_cmd_token_types type)
{
	t_redirection	*redir;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = NULL;
	return (redir);
}

static int	is_redir_valid(t_list **token_lst, t_token *token)
{
	if (!*token_lst)
		return (print_syntax_error("newline"), 0);
	if (token->type != T_WORD)
		return (print_syntax_error(token->value), 0);
	return (1);
}

static void	process_redirection_target(t_redirection *redir, t_list **token_lst, t_ht *env)
{
	char	*target;

	target = ((t_token *)(*token_lst)->content)->value;
	if (redir->type == T_HEREDOC)
		target = handle_heredoc(target, env);
	redir->target = target;
	*token_lst = (*token_lst)->next;
}

static int	add_redirection_to_cmd(t_cmd *cmd, t_redirection *redir)
{
	t_list	*redir_token;

	redir_token = ft_lstnew(redir);
	if (!redir_token)
	{
		free(redir->target);
		free(redir);
		return (0);
	}
	ft_lstadd_back(&cmd->redirections, redir_token);
	return (1);
}

int	ast_add_redirection(t_cmd *cmd, t_list **token_lst, t_list *prev, t_ht *env)
{
	t_redirection	*redir;
	t_token			*token;
	t_list			*it;

	token = (t_token *)(*token_lst)->content;
	while (*token_lst && is_redir(token->type))
	{
		token = (t_token *)(*token_lst)->content;
		redir = create_redirection(token->type);
		if (!redir)
			return (0);
		it = *token_lst;
		*token_lst = (*token_lst)->next;
		free(((t_token *)it->content)->value);
		free(it);
		if (*token_lst)
			token = (t_token *)(*token_lst)->content;
		if (!is_redir_valid(token_lst, token))
		{
			free(redir);
			return (0);
		}
		process_redirection_target(redir, token_lst, env);
		if (prev)
			prev->next = *token_lst;
		if (!add_redirection_to_cmd(cmd, redir))
			return (0);
	}
	return (1);
}
