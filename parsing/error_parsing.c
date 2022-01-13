/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:20:50 by jlong             #+#    #+#             */
/*   Updated: 2022/01/12 15:45:43 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_free_pars_tab(t_state *s)
{
	if (s->pipe)
		free(s->pipe);
	/*int	nbr;

	nbr = 0;
	while (nbr <= s->n_of_pipe)
	{
		if (s->cm[nbr] != NULL || s->cm[nbr][0] == '\0')
		{
			printf("s->cm[nbr] = %s\n", s->cm[nbr]);
		}
		//free(s->cm[nbr]);
		nbr++;
	}*/
	//if (s->cm)
	//	free(s->cm);
	if (s->line)
		free(s->line);
}

void	ft_free_pars_error(t_state *s)
{
	int	nbr;

	nbr = 0;
	if (s->line)
		free(s->line);
	if (s->pipe)
		free(s->pipe);
	if (s->cm)
	{
		while (nbr <= s->n_of_pipe)
		{
			free(s->cm[nbr]);
			nbr++;
		}
	}
	if (s)
		free(s);
	g_global.exit_code = 1;
}

void	ft_error_malloc(t_state *s)
{
	int	nbr;

	nbr = 0;
	if (s->pipe)
		free(s->pipe);
	while (nbr <= s->n_of_pipe)
	{
		if (s->cm[nbr] != NULL || s->cm[nbr][0] == '\0')
			free(s->cm[nbr]);
		nbr++;
	}
	if (s->cm)
		free(s->cm);
	ft_perror("Malloc", NULL, "Error allocation memory");
}
