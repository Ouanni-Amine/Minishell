/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:00:55 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/03 13:56:36 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	update_env_vars(t_shell *shell, char *oldpwd, int free_oldpwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_value(&shell->env, "OLDPWD", oldpwd, 1);
		set_env_value(&shell->env, "PWD", new_pwd, 1);
		free(shell->pwd_emergcy);
		shell->pwd_emergcy = env_strdup(new_pwd, '\0');
		free(new_pwd);
	}
	else
	{
		perror("minishell: cd");
		if (free_oldpwd)
			free(oldpwd);
		return (1);
	}
	if (free_oldpwd)
		free(oldpwd);
	return (0);
}

int	cd_to_home(t_shell *shell, char *oldpwd, int free_oldpwd)
{
	char	*home;
	int		res;

	home = get_env_value(shell->env, "HOME");
	if (!home)
	{
		error("minishell: cd: HOME not set", NULL, NULL, NULL);
		if (free_oldpwd)
			free(oldpwd);
		return (1);
	}
	if (chdir(home) == -1)
	{
		res = permission_denied(home, oldpwd, free_oldpwd, shell);
		if (res != -1)
			return (res);
		perror("minishell: cd");
		if (free_oldpwd)
			free(oldpwd);
		return (1);
	}
	return (update_env_vars(shell, oldpwd, free_oldpwd));
}

int	special_case(t_shell *shell, char *arg)
{
	char	*pwd;
	char	*res;

	set_env_value(&shell->env, "OLDPWD", shell->pwd_emergcy, 1);
	res = getcwd(NULL, 0);
	if (res)
	{
		set_env_value(&shell->env, "PWD", res, 1);
		free(shell->pwd_emergcy);
		shell->pwd_emergcy = env_strdup(res, '\0');
		return (free(res), 0);
	}
	pwd = ft_strdup(shell->pwd_emergcy, '\0');
	if (pwd[ft_strlen(pwd) - 1] != '/')
		pwd = ft_strjoin(pwd, "/");
	pwd = ft_strjoin(pwd, arg);
	set_env_value(&shell->env, "PWD", pwd, 1);
	free(shell->pwd_emergcy);
	shell->pwd_emergcy = env_strdup(pwd, '\0');
	error("minishell: cd: error retrieving current directory: getcwd:",
		" cannot access parent directories: ",
		strerror(errno), NULL);
	return (0);
}

int	cd_to_dir(t_shell *shell, char *dir, char *oldpwd, int free_oldpwd)
{
	int	res;

	if (chdir(dir) == -1)
	{
		res = permission_denied(dir, oldpwd, free_oldpwd, shell);
		if (res != -1)
			return (res);
		error("minishell: cd: ", dir, ": ", strerror(errno));
		if (free_oldpwd)
			free(oldpwd);
		return (1);
	}
	if (free_oldpwd)
		return (update_env_vars(shell, oldpwd, free_oldpwd));
	return (special_case(shell, dir));
}

int	ft_cd(char **cmd, t_shell *shell)
{
	char	*oldpwd;
	int		dir_exists;

	oldpwd = getcwd(NULL, 0);
	dir_exists = (oldpwd != NULL);
	if (!cmd[1])
	{
		if (dir_exists)
			return (cd_to_home(shell, oldpwd, 1));
		return (cd_to_home(shell, shell->pwd_emergcy, 0));
	}
	if (dir_exists)
		return (cd_to_dir(shell, cmd[1], oldpwd, 1));
	return (cd_to_dir(shell, cmd[1], shell->pwd_emergcy, 0));
}
