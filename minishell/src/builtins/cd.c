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

static int	check_errors(char *pwd)
{
	if (!*pwd)
		return (0);
	if (check_for_dir(pwd))
		return (1);
	if (check_permissions(pwd))
		return (1);
	if (chdir(pwd) != -1)
		return (0);
	perror("minishell: cd");
	return (1);
}

int	ft_cd(char **args, t_ht *env)
{
	char		*pwd;
	char		*old_pwd;

	args += 1;
	old_pwd = ht_get(env, "PWD");
	if (!*args)
		pwd = ht_get(env, "HOME");
	else if (!ft_strcmp(*args, "-"))
	{
		pwd = ht_get(env, "OLDPWD");
		if (!pwd || !*pwd)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
		printf("%s\n", pwd);
	}
	else
		pwd = *args;
	if (check_errors(pwd))
		return (1);
	ht_set(env, "OLDPWD", old_pwd);
	ht_set(env, "PWD", getcwd(NULL, 0));
	return (0);
}
