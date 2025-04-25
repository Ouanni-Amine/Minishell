/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:46:23 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/24 16:47:11 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char *check_path(t_env *env, char **cmd_args, char *cmd_s)
{
    char *path = get_env_value(env, "PATH");
    char *pwd_path;

    if (!path)
    {
        pwd_path = ft_strjoin(get_env_value(env, "PWD"), cmd_s);
        if (!access(pwd_path, F_OK))
        {
            char *result = ft_strdup(get_env_value(env, "PWD"), '\0');
            return (result);
        }
        return (NULL);
    }
    return (ft_strdup(path, '\0'));
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
	close (fd);
	if (access(cmd_args[0], F_OK) != 0)
	{
		error("minishell: ", cmd_args[0], ": No such file or directory", NULL);
		exit(127);
	}
	if (access(cmd_args[0], X_OK) != 0)
	{
		error("minishell: ", cmd_args[0], ": Permission denied", NULL);
		exit(126);
	}
	res = ft_strdup(cmd_args[0], '\0');
	return (res);
}

char	*command_without_path2(char **args, char **solo, char *cmd_s)
{
	char	*res;
	int		i;
	int		fd;

	i = 0;
	while (solo[i])
	{
		res = ft_strjoin(solo[i], cmd_s);
		if (access(res, F_OK) == 0)
		{
			fd = open(res, O_DIRECTORY);
			if (fd != -1)
			{
				error("minishell: ", args[0], ": is a directory", NULL);
				exit(126);
			}
			close (fd);
			if (access(res, X_OK) != 0)
			{
				error("minishell: ", args[0], ": Permission denied", NULL);
				exit(126);
			}
			break;
		}
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

	cmd_slash = ft_strjoin("/", cmd_args[0]);
	path_env= check_path(env, cmd_args, cmd_slash);
	if (!path_env)
		return (command_with_path(cmd_args));
	path_solo = ft_split(path_env, ':');
	return (command_without_path2(cmd_args, path_solo, cmd_slash));
}

char	*command_founder(t_env *env, char **cmd_args)
{
	char	*path;

	path = get_env_value(env, "PATH");
	if (path && (!strcmp(".", cmd_args[0] )|| !strcmp("..", cmd_args[0])))
	{
		error("minishell: ", cmd_args[0], ": command not found", NULL);
		exit(127);
	}
	if (ft_strchr(cmd_args[0], '/'))
		return (command_with_path(cmd_args));
	else
		return (command_without_path(env, cmd_args));
}
