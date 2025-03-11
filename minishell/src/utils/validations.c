#include "minishell.h"

int	is_valid_identifier(const char *identifier, int from_export)
{
	int	i;

	i = -1;
	while (identifier[++i])
	{
		if (i == 0 && (!ft_isalpha(identifier[i]) && identifier[i] != '_'))
		{
			if (from_export)
				print_error("minishell: export: `", identifier,
					"': not a valid identifier");
			return (0);
		}
		if (identifier[i] == '=')
			break ;
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
		{
			if (from_export)
			{
				if (i != 0 && identifier[i] == '+' && identifier[i + 1] == '=')
					continue ;
				print_error("minishell: export: `", identifier, "': not a valid identifier");
			}
			return (0);
		}
	}
	return (1);
}
