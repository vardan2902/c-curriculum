#include "minishell.h"

void	print_error(const char *prefix, const char *token, const char *sufix)
{
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd(sufix, STDERR_FILENO);
}

void	print_syntax_error(const char *token)
{
	print_error("minishell: syntax error near unexpected token `", token, "'");
}
