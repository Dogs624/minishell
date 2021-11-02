/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_pwd_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:17:33 by rgelin            #+#    #+#             */
/*   Updated: 2021/11/02 22:52:57 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_pwd(char **cmd)
// {
// 	char	*pwd;

// 	if (cmd[1]) //pour l'instant protecion comme ca mais a voir avec les pipes pour plusieurs arguments
// 	{
// 		write (2, "pwd: too many arguments\n", 24); //faire une fonction de gestion d'erreur (avec perror je pense)
// 		return ;
// 	}
// 	pwd = getenv("PWD"); //attention a ne pas modifier la valeur de pwd --> si on veut chipoter avec il faut faire une copie
// 	printf("%s\n", pwd);
// }

void	ft_pwd(char **cmd)
{
	char	pwd[200]; //redefinir la taille en mode bien

	if (cmd[1]) //pour l'instant protecion comme ca mais a voir avec les pipes pour plusieurs arguments
	{
		write (2, "pwd: too many arguments\n", 24); //faire une fonction de gestion d'erreur (avec perror je pense)
		return ;
	}
	printf("%s\n", getcwd(pwd, 200));
	
}

static void	go_to_final_path(char **cmd)
{
	char	*final_path;
	char	*path;
	
	path = malloc(sizeof(char) * 200); //voir pour la taille du buffer --> le chemin peut faire 6 octets max sinon getcwd renvoie null
	if (!path)
	{
		ft_free(cmd, ft_tabsize(cmd));
		exit(EXIT_FAILURE);
	}
	getcwd(path, 200);
	final_path = ft_strjoin(path, "/"); //path est free dans le strjoin
	final_path = ft_strjoin(final_path, cmd[1]);
	if (chdir(final_path) == -1)
		printf("cd: no such file or directory: %s\n", cmd[1]);
	free(final_path);
	final_path = NULL;
}

//a voir si on recoit d'office cd ou il peut y avoir cd..
void	ft_cd(char **cmd) // il y a un leak de plus a chaque commande
{
	char	*home;
	
	home = getenv("HOME");
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "..", 3))
			chdir("..");
		else if (cmd[1][0] == '~' && !cmd[1][1])
			chdir(home);
		else
			go_to_final_path(cmd);
		ft_free(cmd, ft_tabsize(cmd));
		// system("leaks minishell");
	}
	else if (!ft_strncmp(cmd[0], "cd", 3))
	{
		
		chdir(home);
		ft_free(cmd, ft_tabsize(cmd));
		// system("leaks minishell");
	}
	else
		return ;
}
