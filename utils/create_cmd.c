#include "../srcs/minishell.h"

char	**create_cmd(t_exc command)
{
	char	**to_ret;
	int		i;

	i = 0;
	to_ret = (char **)malloc(sizeof(char *) * 4);
	if (!to_ret)
		return (NULL);
	if (command.cmd)
		to_ret[i++] = command.cmd;
	if (command.opt)
		to_ret[i++] = command.opt;
	if (command.arg)
		to_ret[i++] = command.arg;
	to_ret[i] = NULL;
	while (--i >= 0)
	{
		if (!to_ret[i])
			return (NULL);
	}
	return (to_ret);
}
