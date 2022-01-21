/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:30:52 by jlong             #+#    #+#             */
/*   Updated: 2022/01/21 12:00:35 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*get_var_env_bis(char *tab_redirect, char **env, int i)
{
	t_tmp	new;

	init_tmp(&new);
	new.tmp = ft_substr(tab_redirect, 0, i);
	new.rest = ft_substr(tab_redirect, i, (ft_strlen(tab_redirect) - i));
	new.var = ft_arg_bis(new.rest, env);
	new.new_line = ft_strjoin_double_free(new.tmp, new.var);
	free(tab_redirect);
	free(new.var);
	tab_redirect = NULL;
	return (new.new_line);
}

char	*ft_arg_bis(char *arg, char **env)
{
	if (arg[0] == '\'')
	{
		arg = ft_strtrim(arg, "\'");
	}
	else if (arg[0] == '\"')
	{
		arg = ft_strtrim(arg, "\"");
		arg = check_var_env(arg, env);
	}
	else
	{
		arg = check_var_env(arg, env);
	}
	return (arg);
}

int	return_index_all_string(char *line, int index, char c)
{
	int	i;

	i = index + 1;
	while (line[i] != '\0')
	{
		if (c != 'N' && line[i] == c)
		{
			break ;
		}
		if (c == 'N' && (line[i] == '\'' || line[i] == '\"'))
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	check_all_string_bis(char	**line, char **env, char c, int index)
{
	t_tmp	tmp;
	int		i;
	int		size;

	size = 0;
	init_tmp(&tmp);
	i = return_index_all_string(*line, index, c);
	if (index > 0)
		tmp.nl = ft_substr((*line), 0, index - 1);
	else
		tmp.nl = ft_substr((*line), 0, index);
	if (c == '\'' || c == '\"')
	{
		tmp.tmp = ft_substr((*line), index, (i + 1) - index);
		tmp.rest = ft_substr((*line), i, ((ft_strlen(*line) - 1) - i));
	}
	else
	{
		tmp.tmp = ft_substr((*line), index, i - index);
		tmp.rest = ft_substr((*line), i, (ft_strlen(*line) - i));
	}
	tmp.var = ft_arg_bis(tmp.tmp, env);
	tmp.new_line = ft_strjoin_double_free(tmp.nl, tmp.var);
	size = ft_strlen(tmp.new_line);
	tmp.new_line = ft_strjoin_double_free(tmp.new_line, tmp.rest);
	free((*line));
	if (tmp.var)
		free(tmp.var);
	if (tmp.rest)
		free(tmp.rest);
	(*line) = NULL;
	(*line) = tmp.new_line;
	return (size);
}

char	*check_all_string(char	*line, char **env)
{
	int		i;
	t_tmp	tmp;

	init_tmp(&tmp);
	i = 0;
	if (line)
	{
		while (line[i] != '\0')
		{
			if (line[i] == '\'')
				i = check_all_string_bis(&line, env, '\'', i);
			else if (line[i] == '\"')
				i = check_all_string_bis(&line, env, '\"', i);
			else if (line[i] == '$')
				i = check_all_string_bis(&line, env, 'N', i);
			if (i < (int)(ft_strlen(line)))
				i++;
		}
	}
	tmp.new_line = ft_strdup(line);
	free(line);
	line = NULL;
	return (tmp.new_line);
}
