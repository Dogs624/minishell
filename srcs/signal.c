/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:44:48 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 11:44:49 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_msg(void)
{
	if (g_global.exit_code == 130)
		ft_putchar_fd('\n', 1);
	else if (g_global.exit_code == 131)
		ft_putendl_fd("QUIT: 3", 1);
}

void	ft_ctrl_c(int signal)
{
	(void)signal;
	if (g_global.in_heredoc)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	if (!g_global.fork_pid)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exit_code = 1;
	}
}

void	ft_ctrl_backslash(int signal)
{
	(void)signal;
	if (g_global.in_heredoc)
		return ;
	if (!g_global.fork_pid)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
