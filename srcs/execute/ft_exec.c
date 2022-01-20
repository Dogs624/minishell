/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:24:36 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/20 12:17:08 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_all_exec(char ***folder, t_exc command)
{
	int	i;

	i = 0;
	if (!command.cmd)
		return (1);
	if (!(*folder))
		return (0);
	while ((*folder)[i])
	{
		(*folder)[i] = ft_strjoin_free((*folder)[i], "/");
		if (!(*folder)[i])
			return (0);
		(*folder)[i] = ft_strjoin_free((*folder)[i], command.cmd);
		if (!(*folder)[i])
			return (0);
		i++;
	}
	return (1);
}

static int	ft_free_exec(char **folder, char **cmd)
{
	ft_free(folder, ft_tabsize(folder));
	ft_free(cmd, ft_tabsize(cmd));
	return (EXIT_FAILURE);
}

static int	ft_try_exec(t_exc command, char **cmd, char **folder, char **env)
{
	int	i;

	i = -1;
	if (!ft_strlen(command.cmd) && ft_tabsize(command.heredoc)
		&& g_global.exit_code == 0)
		exit(EXIT_SUCCESS);
	if (ft_tabsize(command.heredoc) && g_global.exit_code == 1)
		exit(EXIT_FAILURE);
	if (!ft_strlen(command.cmd))
		exit(EXIT_SUCCESS);
	while (folder[++i])
		g_global.exit_code = execve(folder[i], cmd, env);
	g_global.exit_code = execve(command.cmd, cmd, env);
	ft_perror(command.cmd, NULL, "command not found");
	return (127);
}

static int	ft_exec(t_exc command, char **env)
{
	char	**folder;
	char	**cmd;
	char	*line;

	ft_signal_msg();
	cmd = create_cmd(command);
	if (!cmd)
		exit (EXIT_FAILURE);
	line = our_getenv(ft_strdup("PATH"), env);
	if (!ft_strcmp(line, ""))
	{
		ft_perror(command.cmd, NULL, "command not found");
		return (127);
	}
	folder = ft_split(line, ':');
	if (!folder)
		return (ft_free_exec(folder, cmd));
	if (!ft_create_all_exec(&folder, command))
		return (ft_free_exec(folder, cmd));
	g_global.exit_code = ft_try_exec(command, cmd, folder, env);
	command.exit_code = g_global.exit_code;
	ft_free_exec(folder, cmd);
	return (g_global.exit_code);
}

int	execute(t_exc exc, char ***env, int nbr_pipe)
{
	if (check_builtin(exc.cmd) != 0)
	{
		ft_execute_command(exc, env, nbr_pipe);
		return (g_global.exit_code);
	}
	else
		return (ft_exec(exc, *env));
}
