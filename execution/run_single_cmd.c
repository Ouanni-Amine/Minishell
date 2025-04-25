/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:23:30 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/24 23:30:46 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	run_builtins(t_main *main, t_shell *shell)
{
	int	res;

	if (!strcmp("echo", main->cmd[0]))
		res = ft_echo(main->cmd);
	else if (!strcmp("cd", main->cmd[0]))
		res = ft_cd(main->cmd, &shell->env);
	else if (!strcmp("pwd", main->cmd[0]))
		res = ft_pwd();
	else if (!strcmp("unset", main->cmd[0]))
		res = ft_unset(&shell->env, main->cmd);
	else if (!strcmp("env", main->cmd[0]))
		res = ft_env(main->cmd, shell->env);
	else if (!strcmp("export", main->cmd[0]))
		res = ft_export(&shell->env, main->cmd);
	else if (!strcmp("exit", main->cmd[0]))
		res = ft_exit(main->cmd, shell->last_status);
	return (res);
}

int	handle_dup(int stdin_cpy, int stdout_cpy)
{
	int	status;

	status = 0;
	if (dup2(stdin_cpy, STDIN_FILENO) == -1)
	{
		perror("dup");
		status = 1;
	}
	if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
	{
		perror("dup");
		status = 1;
	}
	close(stdin_cpy);
	close(stdout_cpy);
	return (status);
}

int	handle_builtins(t_main *main, t_shell *shell)
{
	int	stdin_cpy;
	int	stdout_cpy;
	int	status;
	t_file *tmp;

	if (main->redir)
	{
		stdin_cpy = dup(0);
		stdout_cpy = dup(1);
		if (stdin_cpy == -1 || stdout_cpy == -1)
		{
			perror("dup");
			if (stdin_cpy != -1)
				close (stdin_cpy);
			if (stdout_cpy != -1)
				close (stdout_cpy);
			return (1);
		}
		if (handle_redir(main))
		{
			handle_dup(stdin_cpy, stdout_cpy);
			return (1);
		}
	}
	else
		return (run_builtins(main, shell));
	status = run_builtins(main, shell);
	if (handle_dup(stdin_cpy, stdout_cpy))
		status = 1;
	return (status);
}

void	update_underscore(t_env *env, t_main *main)
{
	int	i;

	i = 0;
	if (!main->next)
	{
		while (main->cmd[i])
			i++;
		set_env_value(&env, "_", main->cmd[i - 1], 1);
	}
	else
		set_env_value(&env, "_", "", 1);
}

void	run_single_cmd(t_main *main, t_shell *shell)
{
	pid_t	pid;
	char	*path;
	int		status;

	update_underscore(shell->env, main);
	if (main->is_builtin)
		shell->last_status = handle_builtins(main, shell);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			shell->last_status = 1;
			return ;
		}
		if (pid == 0)
		{
			if (main->redir)
			{
				if (handle_redir(main))
					exit(1);
			}
			path = command_founder(shell->env, main->cmd);
			char **new_env=env_convertor(shell->env);
			execve(path, main->cmd, new_env);
			error("minishell: ", main->cmd[0], " : ", strerror(errno));
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				shell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_status = WTERMSIG(status) + 128;
		}
	}
}

