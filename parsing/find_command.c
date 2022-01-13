/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:20:55 by jlong             #+#    #+#             */
/*   Updated: 2022/01/13 09:19:46 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	tab->heredoc = NULL;
	tab->next_char = NULL;
	tab->redirect = NULL;
}

t_pars	get_command(char *line, t_state *s)
{
	int		next;
	t_pars	tab;
	char	*new_line;

	(void)s;
	init_tab(&tab);
	new_line = get_heredoc(line, &tab);
	if (new_line && ft_get_index(new_line) != 0)
	{
		next = ft_get_index(new_line);
		tab.command = ft_substr(new_line, 0, next);
		tab.command = ft_strtrim(tab.command, " ");
		tab.option = get_opt(new_line, tab.command);
		tab.redirect = get_redirect(new_line);
		tab.arg = get_arg(new_line, tab.command);
	}
	else if (new_line)
	{
		tab.command = ft_substr(new_line, 0, ft_strlen(new_line));
		tab.command = ft_strtrim(tab.command, " ");
	}
	free(new_line);
	return (tab);
}

t_pars	*find_command(t_state *s)
{
	int		i;
	t_pars	*comd;

	i = -1;
	comd = malloc(sizeof(t_pars) * (s->n_of_pipe + 1));
	if (!comd)
		exit(EXIT_FAILURE);
	while (++i <= s->n_of_pipe)
		comd[i] = get_command(s->cm[i], s);
	return (comd);
}
