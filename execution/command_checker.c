/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:46:23 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/22 11:34:31 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char	*check_path(t_env *env, char **cmd_args)
{
	char *path=get_env_value(env, "PATH");
	if (!path)
	{
		error("minishell: ", cmd_args[0], ": No such file or directory", NULL);
		exit(127);
	}
	return (path);
}

char	*command_with_path(char **cmd_args)
{
	char	*res;
	int		fd;

	fd = open(cmd_args[0], O_DIRECTORY);
	if (fd != -1)
	{
		error("minishell: ", cmd_args[0], ": is a directory", NULL);
		exit(126);
	}
	if (access(cmd_args[0], F_OK) != 0)
	{
		error("minishell: ", cmd_args[0], ": No such file or directory", NULL);
		exit(127);
	}
	res = ft_strdup(cmd_args[0], '\0');
	return (res);
}

char	*command_without_path2(char **args, char **solo, char *cmd_s)
{
	char	*res;
	int		i;

	i = 0;
	while (solo[i])
	{
		res = ft_strjoin(solo[i], cmd_s);
		if (access(res, F_OK) == 0)
			break ;
		i++;
	}
	if (!solo[i])
	{
		error("minishell: ", args[0], ": command not found", NULL);
		exit(127);
	}
	return (res);
}

char	*command_without_path(t_env *env, char **cmd_args)
{
	char	*cmd_slash;
	char	*path_env;
	char	**path_solo;
	int		i;

	path_env= check_path(env, cmd_args);
	cmd_slash = ft_strjoin("/", cmd_args[0]);
	path_solo = ft_split(path_env, ':');
	return (command_without_path2(cmd_args, path_solo, cmd_slash));
}

char	*command_founder(t_env *env, char **cmd_args)
{
	if (ft_strchr(cmd_args[0], '/'))
		return (command_with_path(cmd_args));
	else
		return (command_without_path(env, cmd_args));
}
