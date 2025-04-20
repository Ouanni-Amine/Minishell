/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:46:23 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/19 13:46:33 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char	*check_path(t_env *env, char **cmd_args)
{
	char *path=get_env_value(env, "PATH");
	if (!path)
		printf("%s:  No such file or directory\n ", cmd_args[0]);
	return (path);
}

char	*command_with_path(char **cmd_args, int exit)
{
	char	*res;

	if (access(cmd_args[0], X_OK) != 0)
	{
		printf("%s: No such file or directory\n", cmd_args[0]);
		my_exit();
	}
	res = ft_strdup(cmd_args[0], '\0');
	return (res);
}

char	*command_without_path2(char **args, char **solo, char *cmd_s, int e)
{
	char	*res;
	int		i;

	i = 0;
	while (solo[i])
	{
		res = ft_strjoin(solo[i], cmd_s);
		if (access(res, X_OK) == 0)
			break ;
		i++;
	}
	if (!solo[i])
	{
		printf("%s : command not found\n", args[0]);
		exit(e);
	}
	return (res);
}

char	*command_without_path(t_env *env, char **cmd_args, int exit)
{
	char	*cmd_slash;
	char	*path_env;
	char	**path_solo;
	int		i;

	path_env= check_path(env, cmd_args);
	cmd_slash = ft_strjoin("/", cmd_args[0]);
	path_solo = ft_split(path_env, ':');
	return (command_without_path2(cmd_args, path_solo, cmd_slash, exit));
}

char	*command_founder(t_env *env, char **cmd_args)
{
	if (ft_strchr(cmd_args[0], '/'))
		return (command_with_path(cmd_args, 1));
	else
		return (command_without_path(env, cmd_args, 1));
}
