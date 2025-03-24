/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:17:54 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 20:06:01 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_signal_int;

void	process_prompt(char *line, t_ht *map)
{
	t_list	*token_lst;
	t_ast	*ast;
	int		status;
	char	*status_str;

	if (*line == '\0')
		return (free(line));
	if (!ht_get(map, "#ISNOTATTY"))
		add_history(line);
	token_lst = get_token_lst(line);
	free(line);
	if (!token_lst)
		return ;
	ast = ast_create_from_tokens(&token_lst, 0, map);
	ft_lstclear(&token_lst, del_token);
	if (!ast)
		return (ht_set(map, ft_strdup("?"), ft_strdup("2")));
	status = execute_ast(&ast, &ast, map);
	status_str = ft_itoa((unsigned char)status);
	ht_set(map, ft_strdup("?"), status_str);
}

int	process_not_tty_prompt(t_ht *map)
{
	char	*line;
	int		status;

	ht_set(map, ft_strdup("#ISNOTATTY"), ft_strdup("TRUE"));
	line = get_prompt_line();
	while (line)
	{
		g_signal_int = 0;
		if (!line)
			return (0);
		process_prompt(line, map);
		unlink_heredocs();
		status = (unsigned char)ft_atoi(ht_get(map, "?"));
		if (status == 2)
			return (status);
		line = get_prompt_line();
	}
	status = (unsigned char)ft_atoi(ht_get(map, "?"));
	return (status);
}

int	process_tty_prompt(t_ht *map)
{
	char			*line;

	while (1)
	{
		line = readline("minishell $> ");
		if (!line)
		{
			tputs("\033[A", 1, ft_putchar);
			tputs("minishell $> exit\n", 1, ft_putchar);
			return (0);
		}
		g_signal_int = 0;
		process_prompt(line, map);
		unlink_heredocs();
	}
	return (0);
}

int	prompt_loop(t_ht *map)
{
	if (!isatty(fileno(stdin)))
		return (process_not_tty_prompt(map));
	return (process_tty_prompt(map));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ht			map;
	unsigned char	status;
	char			*pwd;

	status = 0;
	if (argc > 1)
		return (0);
	setup_signals();
	ht_init_from_env(&map, envp);
	ht_set(&map, ft_strdup("?"), ft_strdup("0"));
	ht_set(&map, ft_strdup("0"), ft_strdup(argv[0]));
	pwd = ht_get(&map, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		ht_set(&map, ft_strdup("PWD"), pwd);
	}
	if (!ht_get(&map, "SHLVL"))
		ht_set(&map, ft_strdup("SHLVL"), ft_strdup("1"));
	ht_set(&map, ft_strdup("#BASE_PATH"), ft_strdup(pwd));
	status = prompt_loop(&map);
	rl_clear_history();
	ht_clear(&map);
	return (status);
}
