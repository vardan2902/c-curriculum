#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

void	print_error(const char *prefix, const char *token, const char *sufix);
void	print_syntax_error(const char *token);
void	setup_signals(void);
int		is_valid_identifier(const char *str, int from_export);

#endif
