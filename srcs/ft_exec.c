#include "minishell.h"

extern int	g_exit_code;

static int	ft_create_all_exec(char ***folder, t_exc command)
{
	int	i;

	i = 0;
	if (!(*folder))
		return (0);
	while ((*folder)[i])
	{
		(*folder)[i] = ft_strjoin((*folder)[i], "/");
		if (!(*folder)[i])
			return (0);
		(*folder)[i] = ft_strjoin((*folder)[i], command.cmd);
		if (!(*folder)[i])
			return (0);
		i++;
	}
	return (1);
}

static int	ft_exec(t_exc command, char **env)
{
	char	**folder;
	int		i;
	char	**cmd;
	int		exit_code;

	cmd = create_cmd(command);
	if (!cmd)
		return (EXIT_FAILURE);
	i = -1;
	if (find_var_in_env("PATH", env) == -1)
		ft_perror(command.cmd, NULL, "command not found");
	folder = ft_split(getenv(env[find_var_in_env("PATH", env)]), ':');
	if (!folder)
		return (EXIT_FAILURE);
	if (!folder || !ft_create_all_exec(&folder, command))
	{
		ft_free(folder, ft_tabsize(folder));
		ft_free(cmd, ft_tabsize(cmd));
		return (EXIT_FAILURE);
	}
	while (folder[++i])
		exit_code = execve(folder[i], cmd, NULL);
	if (i == ft_tabsize(folder))
		ft_perror(command.cmd, NULL, "command not found");
	ft_free(folder, ft_tabsize(folder));
	ft_free(cmd, ft_tabsize(cmd));
	return (exit_code);
}

int	execute(t_exc exc, char ***env)
{
	if (check_builtin(exc.cmd) != 0)
	{
		ft_execute_command(exc, env);
		return (g_exit_code);
	}
	else
		return (ft_exec(exc, *env));
}
