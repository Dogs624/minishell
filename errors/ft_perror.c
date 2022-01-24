/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:28:13 by rgelin            #+#    #+#             */
/*   Updated: 2022/01/24 14:43:30 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_perror(char *cmd, char *arg, char *err_msg)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (!ft_strncmp(cmd, "export", 7) && arg)
	{
		write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "'", 1);
		write(2, ": ", 2);
	}
	else if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (err_msg)
		write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}
