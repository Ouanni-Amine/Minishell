/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_founder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:46:23 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/26 16:06:29 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	exit_with_error(int flag, char *cmd)
{
	if (flag == 1 || flag == 2 || flag == 5)
	{
		if (flag == 1)
			error("minishell: ", cmd, ": is a directory", NULL);
		else if (flag == 2)
			error("minishell: ", cmd, ": Permission denied", NULL);
		else
			error("minishell: ", cmd, ": Not a directory", NULL);
		exit(126);
	}
	else
	{
		if (flag == 3)
			error("minishell: ", cmd, ": No such file or directory", NULL);
		else
			error("minishell: ", cmd, ": command not found", NULL);
		exit(127);
	}
}

void	check_file_acces(char *cmd)
{
	int	fd;

	fd = open(cmd, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		exit_with_error(1, cmd);
	}
	if (access (cmd, F_OK) != 0)
	{
		if (errno == 2)
			exit_with_error(3, cmd);
		else if (errno == 20)
			exit_with_error(5, cmd);
	}
	if (access(cmd, X_OK) != 0)
		exit_with_error(2, cmd);
}

char	*path_cheker(char *cmd, char *path, int i)
{
	char	*cmd_slash;
	char	*res;
	char	**path_solo;
	int		fd;

	cmd_slash = ft_strjoin("/", cmd);
	path_solo = env_split(path, ':');
	while (path_solo[i])
	{
		res = ft_strjoin(path_solo[i], cmd_slash);
		fd = open(res, O_DIRECTORY);
		if (fd != -1)
			exit_with_error(4, cmd);
		if (access(res, F_OK) == 0)
		{
			if (access(res, X_OK) != 0)
				exit_with_error(2, res);
			break ;
		}
		i++;
	}
	if (!path_solo[i])
		exit_with_error(4, cmd);
	return (res);
}

char	*command_founder(char **cmd_args, t_env *env)
{
	char	*path;

	path = get_env_value(env, "PATH");
	if (!path || !path[0])//NOTE: add this when merging
		return (check_file_acces(cmd_args[0]), cmd_args[0]);
	if (ft_strchr(cmd_args[0], '/'))
		return (check_file_acces(cmd_args[0]), cmd_args[0]);
	return (path_cheker(cmd_args[0], path, 0));
}
