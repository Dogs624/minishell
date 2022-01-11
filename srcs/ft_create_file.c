#include "minishell.h"

static int	ft_create_file(char *name)
{
	char	*file_name;
	int		fd;

	file_name = ft_strdup(name);
	if (!file_name)
	{
		g_global.exit_code = EXIT_FAILURE;
		perror("malloc");
		return (g_global.exit_code);
	}
	fd = open(file_name, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		g_global.exit_code = EXIT_FAILURE;
		free(file_name);
		return (g_global.exit_code);
	}
	if (close(fd) == -1)
	{
		perror("close");
		g_global.exit_code = EXIT_FAILURE;
		free(file_name);
		return (g_global.exit_code);
	}
	free(file_name);
	g_global.exit_code = EXIT_SUCCESS;
	return (g_global.exit_code);
}

static int	ft_create_redirect(t_exc exc)
{
	char	*current;
	int		i;

	i = 0;
	if (!exc.redirect || !ft_tabsize(exc.redirect))
		return (-2);
	current = exc.redirect[i];
	while (current)
	{
		if (ft_strncmp(current, ">>", 2) == 0)
			g_global.exit_code = ft_create_file(current + 2);
		else if (ft_strncmp(current, ">", 1) == 0)
			g_global.exit_code = ft_create_file(current + 1);
		current = exc.redirect[++i];
	}
	return (EXIT_SUCCESS);
}

void	ft_create_all_redirect(t_exc *exc, int size)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i <= size)
	{
		ret = ft_create_redirect(exc[i]);
		i++;
	}
	(void)ret;
}
