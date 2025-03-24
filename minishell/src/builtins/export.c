/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:42:19 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:42:20 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_to_value(char **value, char **key, char *token, t_ht *env)
{
	char	*eq;
	char	*prev_value;

	eq = ft_strchr(token, '=');
	*key = ft_substr(token, 0, eq - token - 1);
	prev_value = ht_get(env, *key);
	if (!prev_value)
		prev_value = ft_strdup("");
	*value = ft_strjoin(prev_value, eq + 1);
	free(prev_value);
}

static void	set_value(char **value, char **key, char *token, char *eq)
{
	*key = ft_substr(token, 0, eq - token);
	*value = ft_substr(eq + 1, 0, ft_strlen(eq + 1));
}

void	export_new_env(char *token, t_ht *env)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(token, '=');
	if (eq)
	{
		if (*(eq - 1) == '+')
			append_to_value(&value, &key, token, env);
		else
			set_value(&value, &key, token, eq);
		ht_set(env, key, value);
	}
	else if (!ht_get(env, token))
		ht_set(env, ft_strdup(token), NULL);
}

int	ft_export(char **args, t_ht *env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[i])
		++i;
	if (i == 1)
	{
		print_env(env, 1);
		return (0);
	}
	i = 0;
	while (args[++i])
	{
		if (is_valid_identifier(args[i], 1))
			export_new_env(args[i], env);
		else
			status = 1;
	}
	return (status);
}
