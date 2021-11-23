#include "../minishell.h"

extern int	g_exit_code;

static char	*parse_arg(char *arg)
{
	char	*res;
	int		i;

	res = ft_strtrim_modified(arg, "\"");
	free(arg);
	arg = NULL;
	i = -1;
	while (res[++i])
	{
		if (!ft_isalpha(res[0]) || !ft_isalnum(res[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", res);
			g_exit_code = 1;
			return (NULL);
		}
	}
	return (res);

}

void	ft_unset(t_exc exc, char ***env)
{
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	if (exc.arg)
	{
		while (exc.arg[++i])
		{
			exc.arg[i] = parse_arg(exc.arg[i]);
			if (exc.arg[i] && find_var_in_env(exc.arg[i], *env))
			{
				new_env = ft_calloc(sizeof(char *), (ft_tabsize(*env) + 1));
				if (!new_env)
					exit(EXIT_FAILURE);
				j = -1;
				while ((*env)[++j])
				{
					if (j == find_var_in_env(exc.arg[i], *env))
						j++;
					new_env[j] = ft_strdup((*env)[j]); //reste un leak ici
					if (!new_env[j])
						exit(EXIT_FAILURE);
				}
				new_env[j] = NULL;
				ft_free(*env, ft_tabsize(*env));
				*env = new_env;
			}
			// new_env = (char **)malloc(sizeof(char *) * (ft_tabsize(*env) + 1));

		}

	}
}