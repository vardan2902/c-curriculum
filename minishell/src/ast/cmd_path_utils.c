#include "minishell.h"

static char	*handle_relative_absolute_path(char *cmd, int *status)
{
	char		*result;
	struct stat	st;

	result = ft_strdup(cmd);
	if (!result)
		return (NULL);
	*status = 0;
	if (access(result, F_OK) == -1)
	{
		print_error("minishell: ", cmd, ": No such file or directory");
		*status = 127;
	}
	else if (stat(result, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error("minishell: ", cmd, ": is a directory");
		*status = 126;
	}
	else if (access(result, X_OK) != 0)
	{
		print_error("minishell: ", cmd, ": Permission denied");
		*status = 126;
	}
	if (*status == 0)
		return (result);
	free(result);
	return (NULL);
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
	print_error(cmd, ": ", "command not found");
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
		return (handle_relative_absolute_path(cmd, status));
	paths = ft_split(path, ':');
	if (!paths || !paths[0])
		return (handle_relative_absolute_path(cmd, status));
	return (get_executable_path(paths, path, cmd, status));
}
