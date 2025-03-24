/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:12:39 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 20:05:37 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

void			print_error(const char *prefix, const char *token,
					const char *sufix);
void			print_syntax_error(const char *token);
void			setup_signals(void);
void			ignore_signals(void);
void			handle_sigint(int signum);
int				is_valid_identifier(const char *str, int from_export);
void			print_env(t_ht *env, int is_declare_list);
void			save_std_fds(int *saved_stdin, int *saved_stdout);
void			restore_std_fds(int saved_stdin, int saved_stdout);
char			*get_prompt_line(void);
int				handle_redirections(t_cmd *cmd, t_ht *env);
void			append_str(char **result, const char *str);
void			append_to_result(t_char_arr *arr, char *new_item);
void			init_char_arr(t_char_arr *arr);
void			free_char_arr(t_char_arr *arr);
void			*ft_free(void *ptr);
void			free_char_matrix(char **matrix);
void			split_and_append(t_char_arr *result, const char *str);
bool			is_builtin(const char *cmd);
char			*build_cmd_path(char *cmd, t_ht *env, int *status);
void			unlink_heredocs(void);
void			del_redir(void *arg);
int				(*get_builtin(char *cmd))(char **args, t_ht *env);
void			update_token(t_ast *it, t_token *token,
					t_list **prev_token, t_list **token_lst);
void			init_ct(t_cmd_token *ct, t_token *token);
void			process_args(t_ast **it, t_list **token_lst,
					t_list *token_it, size_t size);
void			*free_ast_node(t_ast **node);
void			sort_strings(char **arr, size_t size);
void			split_and_update(char **current, t_char_arr *result,
					int last_space);
char			*handle_heredoc(char *delimiter, t_ht *env);
t_redirection	*create_redirection(t_cmd_token_types type);
int				is_redir_valid(t_list **token_lst, t_token *token);
void			shift_args(t_ast **node);
int				find_last_index(char **args);

#endif
