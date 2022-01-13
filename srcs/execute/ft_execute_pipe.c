/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:25:07 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/13 03:25:54 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_open_pipes(int nbr_pipe, int **fds)
{
	int	i;

	i = 0;
	*fds = (int *)malloc(sizeof(int) * nbr_pipe * 2);
	if (!fds)
	{
		ft_perror("malloc", NULL, "Error malloc pipe");
		exit(EXIT_FAILURE);
	}
	while (i < nbr_pipe)
	{
		if (pipe(*fds + i * 2) == -1)
		{
			ft_perror("pipe", NULL, "Error pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	ft_close_pipes(int nbr_pipe, int *fds)
{
	int	i;

	i = 0;
	while (i < (nbr_pipe * 2))
	{
		if (close(fds[i]) == -1)
		{
			ft_perror("close", NULL, "Error close");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	ft_waiting_all_child(int nbr_pipe)
{
	int	i;
	int	status;

	i = 0;
	(void)nbr_pipe;
	while (i <= nbr_pipe)
	{
		waitpid(0, &status, 0);
		if (g_global.fork_pid > 0)
		{
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = 128 + WTERMSIG(status);
		}
		if (i == 0)
			g_global.exit_code = status;
		i++;
	}
	// g_global.exit_code = *status;
	// printf("exit code: %d\n", g_global.exit_code);
}

void	ft_exec_heredoc(int nbr_pipe, t_exc *cmds)
{
	int	i;

	i = -1;
	while (++i <= nbr_pipe)
		ft_heredoc(cmds[i]);
}

void	ft_execute_pipe(t_exc *cmds, int nbr_pipe, char **env)
{
	int	*fds;
	int	i;
	int	n_pipe;

	n_pipe = 0;
	ft_open_pipes(nbr_pipe, &fds);
	ft_exec_heredoc(nbr_pipe, cmds);
	i = -1;
	while (++i <= nbr_pipe)
	{
		g_global.fork_pid = fork();
		if (g_global.fork_pid == 0)
		{
			ft_redirect_output(cmds[i], n_pipe, fds, nbr_pipe);
			ft_redirect_input(cmds[i], n_pipe, fds);
			ft_close_pipes(nbr_pipe, fds);
			exit (execute(cmds[i], &env));
		}
		n_pipe += 2;
	}
	ft_close_pipes(nbr_pipe, fds);
	ft_waiting_all_child(nbr_pipe);
	ft_signal_msg();
	free(fds);
}
