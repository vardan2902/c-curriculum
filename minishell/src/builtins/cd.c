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

static int	check_errors(char *pwd, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	if (i > 1)
	{
		print_error("bash: ","cd: ", "too many arguments");
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

int	ft_cd(char **args, t_ht *env)
{
	char	*pwd;
	char	*old_pwd;
	int		cd_old_pwd;

	cd_old_pwd = 0;
	args += 1;
	old_pwd = ht_get(env, "PWD");
	if (!*args)
		pwd = ht_get(env, "HOME");
	else if (!ft_strcmp(*args, "-"))
	{
		pwd = ht_get(env, "OLDPWD");
		if (!pwd || !*pwd)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
		cd_old_pwd = 1;
	}
	else
		pwd = *args;
	if (check_errors(pwd, args))
		return (1);
	if (cd_old_pwd)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	ht_set(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd));
	ht_set(env, ft_strdup("PWD"), getcwd(NULL, 0));
	return (0);
}
