#include "minishell.h"

static int	is_first_symbol_invalid(int is_first, const char *identifier,
	int c, int from_export)
{
	if (is_first && (!ft_isalpha(c) && c != '_'))
	{
		if (from_export)
			print_error("minishell: export: `", identifier,
				"': not a valid identifier");
		return (1);
	}
	return (0);
}

static int	is_symbol_invalid(int is_first, const char *identifier,
	int c, int from_export)
{
	if (!ft_isalnum(c) && c != '_')
	{
		if (from_export)
		{
			if (!is_first && c == '+' && c == '=')
				return (0);
			print_error("minishell: export: `", identifier,
				"': not a valid identifier");
		}
		return (1);
	}
	return (0);
}

int	is_valid_identifier(const char *identifier, int from_export)
{
	int	i;

	i = -1;
	while (identifier[++i])
	{
		if (is_first_symbol_invalid(i == 0, identifier, identifier[i],
				from_export))
			return (0);
		if (identifier[i] == '=')
			break ;
		if (is_symbol_invalid(i == 0, identifier, identifier[i], from_export))
			return (0);
	}
	return (1);
}
