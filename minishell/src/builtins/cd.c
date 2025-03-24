/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:43:06 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:54:39 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_dir(char *pwd)
{
	struct stat	st;

	if (stat(pwd, &st) == 0 && S_ISDIR(st.st_mode))
		return (0);
	print_error("minishell: cd: ", pwd, ": No such file or directory");
	return (1);
}

static int	check_permissions(char *pwd)
{
	if (access(pwd, X_OK) == 0)
		return (0);
	print_error("minishell: cd: ", pwd, ": Permission denied");
	return (1);
}

static int	change_cd_path(char *pwd, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	if (i > 1)
	{
		print_error("bash: ", "cd: ", "too many arguments");
		return (1);
	}
	if (!*pwd)
		return (0);
	if (check_for_dir(pwd))
		return (1);
	if (check_permissions(pwd))
		return (1);
	if (chdir(pwd) != -1)
		return (0);
	perror("cd");
	return (1);
}

int	change_path(t_ht *env, char *pwd, char *old_pwd, int cd_old_pwd)
{
	if (cd_old_pwd)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	ht_set(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd));
	ht_set(env, ft_strdup("PWD"), getcwd(NULL, 0));
	return (0);
}

int	ft_cd(char **args, t_ht *env)
{
	char	*pwd;
	char	*old_pwd;
	int		cd_old_pwd;

	cd_old_pwd = 0;
	args += 1;
	old_pwd = ht_get(env, "PWD");
	if (!*args || !ft_strcmp(args[0], "--"))
	{
		pwd = ht_get(env, "HOME");
		if (!pwd)
			return (print_error("minishell: ", "cd: ", "HOME not set"), 0);
	}
	else if (!ft_strcmp(*args, "-"))
	{
		pwd = ht_get(env, "OLDPWD");
		if (!pwd || !*pwd)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
		cd_old_pwd = 1;
	}
	else
		pwd = *args;
	if (change_cd_path(pwd, args))
		return (1);
	return (change_path(env, pwd, old_pwd, cd_old_pwd));
}
