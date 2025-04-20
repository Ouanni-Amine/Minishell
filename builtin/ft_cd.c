/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:45:04 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/20 12:05:56 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	ft_cd3(t_env **env, char *oldpwd, char *pwd)
{
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("cd");
		return (1);
	}
	else
	{
		set_env_value(env, "OLDPWD", oldpwd, 1);
		set_env_value(env, "PWD", pwd, 1);
	}
}

void	ft_cd2(t_env **env, char *oldpwd, char *pwd)
{
	char	*home;

	home = get_env_value(*env, "HOME");
	if (!home)
	{
		error("minishell: cd: HOME not set\n", NULL, NULL, NULL);
		return ;
	}
	if (chdir(home) == -1)
		perror("cd");
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			perror("cd");
		else
		{
			set_env_value(env, "PWD", pwd, 1);
			set_env_value(env, "OLDPWD", oldpwd, 1);
		}
	}
	return ;
}

void	ft_cd(char **cmd, t_env **env)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!cmd[1] && oldpwd)
	{
		ft_cd2(env, oldpwd, pwd);
		return ;
	}
	else
	{
		if (!oldpwd && (!strcmp(cmd[1], "../") || !strcmp(cmd[1], "./")))
		{
			error("cd: error retrieving current directory: getcwd:",
				" cannot access parent directories: No such file or directory",
				NULL, NULL);
			return ;
		}
		if (chdir(cmd[1]) == -1)
			error("minishell: cd: ", cmd[1], ": ", "No such file or directory");
		else
			ft_cd3(env, oldpwd, pwd);
	}
}
