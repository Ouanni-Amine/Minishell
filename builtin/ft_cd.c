/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:45:04 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/29 16:31:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	ft_update_env(t_env **env, char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 1);
	if (!pwd)
		return (perror("minishell: cd"), free(oldpwd), 1);
	set_env_value(env, "OLDPWD", oldpwd, 1);
	set_env_value(env, "PWD", pwd, 1);
	free(pwd);
	free(oldpwd);
	return (0);
}

int	cd_alone(t_env **env, char *oldpwd)
{
	char	*home;

	home = get_env_value(*env, "HOME");
	if (!home)
	{
		error("minishell: cd: HOME not set", NULL, NULL, NULL);
		return (free(oldpwd), 1);
	}
	if (chdir(home) == -1)
		return (perror("minishell : cd"), free(oldpwd), 1);
	return (ft_update_env(env, oldpwd));
}

int is_dot_arg(char *arg)
{
	if (!arg)
		return (0);
	if (strcmp(arg, "..") == 0)
		return (1);
	if (strcmp(arg, ".") == 0)
		return (1);
	if (strcmp(arg, "../") == 0)
		return (1);
	if (strcmp(arg, "./") == 0)
		return (1);
	return (0);
}

int	ft_cd(char **cmd, t_env	**env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd && is_dot_arg(cmd[1]))
	{
		error("minishell: cd: error retrieving current directory: getcwd:",
			" cannot access parent directories: No such file or directory",
			NULL, NULL);
		return (1);
	}
	if (!cmd[1])
		return (cd_alone(env, oldpwd));
	else if (chdir(cmd[1]) == -1)
	{
		error("minishell: cd: ", cmd[1], ": ", "No such file or directory");
		return (free(oldpwd), 1);
	}
	return (ft_update_env(env, oldpwd));
}
