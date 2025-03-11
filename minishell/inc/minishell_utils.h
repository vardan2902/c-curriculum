#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

void		print_error(const char *prefix, const char *token, const char *sufix);
void		print_syntax_error(const char *token);
void		setup_signals(void);
int			is_valid_identifier(const char *str, int from_export);
void		handle_sigint(int signum);
void		setup_signals(void);
void		print_env(t_ht *env, int is_declare_list);

#endif
