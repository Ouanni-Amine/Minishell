/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:23:30 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/20 11:36:03 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	run_builtins(t_main *main, t_env **env)
{
	if (!strcmp("echo", main->cmd[0]))
		ft_echo(main->cmd);
	else if (!strcmp("cd", main->cmd[0]))
		ft_cd(main->cmd, env);
	else if (!strcmp("pwd", main->cmd[0]))
		ft_pwd();
	else if (!strcmp("unset", main->cmd[0]))
		ft_unset(env, main->cmd);
	else if (!strcmp("env", main->cmd[0]))
		ft_env(main->cmd, *env);
	else if (!strcmp("export", main->cmd[0]))
		ft_export(env, main->cmd);
	else if (!strcmp("exit", main->cmd[0]))
		ft_exit(main->cmd, 88);
}

int

int	handle_builtins(t_main *main, t_env **env)
{
	int	stdin_cpy;
	int	stdout_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	if (stdin_cpy == -1)
	{
		perror("dup");
		return (1);.....
	}
	stdout_cpy = dup(STDOUT_FILENO);
	if (stdin_cpy == -1)
	{
		perror("dup");
		close (stdin_cpy);
		return (1);
	}
	if (main->redir && handle_redir(main))
	{
		handle_dup(stdin_cpy, stdout_cpy);
		return (1);
	}
	run_builtins(main, env);
	handle_dup(stdin_cpy, stdout_cpy);
	return (0);
}

int	run_single_cmd(t_main *main, t_env **env)
{
	pid_t	pid;
	char	*path;

	if (main->is_builtin)
	{
		int stdin_cpy = dup(STDIN_FILENO);
		int stdout_cpy = dup(STDOUT_FILENO);
		if (main->redir)
		{
			if (handle_redir(main))
			{
				dup2(stdin_cpy, STDIN_FILENO);
				dup2(stdout_cpy, STDOUT_FILENO);
				close(stdin_cpy);
				close(stdout_cpy);
				exit(1);
			}
		}
		run_builtins(main, env);
		dup2(stdout_cpy, STDOUT_FILENO);
		dup2(stdin_cpy, STDIN_FILENO);
		close(stdin_cpy);
		close(stdout_cpy);
	}
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			if (main->redir)
				if (handle_redir(main))
					exit(1);
			path = command_founder(*env, main->cmd);
			char **new_env=env_convertor(*env);
			execve(path, main->cmd, new_env);
		}
		else
			wait(NULL);
	}
}
