/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:04:56 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:08:59 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

bool	is_redir(t_cmd_token_types type);
bool	is_word_or_redir(t_cmd_token_types type);
bool	is_operation(t_cmd_token_types type);
bool	are_parentheses_valid(t_ast **ast, t_list **token_lst);
int		get_precedence(int token);
t_ast	*ast_create_root(void);
t_ast	*ast_create_from_tokens(t_list **token_lst, int indent, t_ht *env);
int		ast_add_cmd(t_ast **it, t_list **token_lst, t_ht *env);
int		ast_add_redirection(t_cmd *cmd, t_list **token_lst, t_list *prev,
			t_ht *env);
int		ast_process_parentheses(t_ast **ast, t_list **token_lst,
			int indent, t_ht *env);
int		handle_redirection(char *cmd, t_redirection *redir, t_ht *env);
int		handle_redirections_and_restore(t_cmd *cmd,
			t_ht *env, int saved_stdin, int saved_stdout);
int		execute_ast(t_ast **root, t_ast **node, t_ht *env);
int		exec_builtin(t_ast **node, t_ht *env);
void	exec_non_builtin(t_ast **node, t_ht *env);
int		execute_command(t_ast **node, t_ht *env);
int		handle_cmd_exec(t_ast **node, t_ht *env);
int		handle_or_exec(t_ast **root, t_ast **node, t_ht *env);
int		handle_and_exec(t_ast **root, t_ast **node, t_ht *env);
int		handle_pipe_exec(t_ast **root, t_ast **node, t_ht *env);
void	*free_ast_node(t_ast **node);

#endif
