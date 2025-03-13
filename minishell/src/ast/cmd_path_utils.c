#include "minishell.h"

static char	*handle_relative_absolute_path(char *cmd, int *status)
{
	char		*result;
	struct stat	st;

	result = NULL;
	if (access(cmd, F_OK) == -1)
	{
		print_error("minishell: ", cmd, ": No such file or directory");
		*status = 127;
	}
	else if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error("minishell: ", cmd, ": is a directory");
		*status = 126;
	}
	else if (access(cmd, X_OK) == 0)
		result = cmd;
	else
	{
		print_error("minishell: ", cmd, ": Permission denied");
		*status = 126;
	}
	return (result);
}

static char	*get_executable_path(char **paths, char *path,
	char *cmd, int *status)
{
	int		i;
	char	*full_path;

	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			break ;
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (free_char_matrix(paths), full_path);
		free(full_path);
	}
	free_char_matrix(paths);
	print_error("minishell: ", cmd, ": command not found");
	*status = 127;
	return (NULL);
}

char	*build_cmd_path(char *cmd, t_ht *env, int *status)
{
	char	**paths;
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (handle_relative_absolute_path(cmd, status));
	path = ht_get(env, "PATH");
	if (!path)
	{
		*status = 127;
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (!paths)
	{
		*status = 127;
		return (NULL);
	}
	return (get_executable_path(paths, path, cmd, status));
}
