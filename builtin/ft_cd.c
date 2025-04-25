/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:45:04 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/25 13:07:42 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	ft_cd3(t_env **env, char *oldpwd, char *pwd)
{
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("cd"), 1);
	else
	{
		set_env_value(env, "OLDPWD", oldpwd, 1);
		set_env_value(env, "PWD", pwd, 1);
		free(pwd);
	}
	return (0);
}

int	ft_cd2(t_env **env, char *oldpwd, char *pwd)
{
	char	*home;

	home = get_env_value(*env, "HOME");
	if (!home)
	{
		error("minishell: cd: HOME not set", NULL, NULL, NULL);
		return (1);
	}
	if (chdir(home) == -1)
		return (perror("cd"), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("cd"), 1);
	set_env_value(env, "PWD", pwd, 1);
	set_env_value(env, "OLDPWD", oldpwd, 1);
	free(pwd);
	return (0);
}

int	ft_cd(char **cmd, t_env **env)
{
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!cmd[1])
	{
		if (ft_cd2(env, oldpwd, pwd))
		{
			free(oldpwd);
			return (1);
		}
	}
	else
	{
		if (!oldpwd)
		{
			error("cd: error retrieving current directory: getcwd:",
				" cannot access parent directories: No such file or directory",
				NULL, NULL);
			return (1);
		}
		if (chdir(cmd[1]) == -1)
		{
			error("minishell: cd: ", cmd[1], ": ", "No such file or directory");
			free(oldpwd);
			return (1);
		}
		else
		{
			if (ft_cd3(env, oldpwd, pwd))
			{
				free(oldpwd);
				return (1);
			}
		}
	}
	free(oldpwd);
	return (0);
}
