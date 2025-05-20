/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:23:30 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/16 12:12:43 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	run_builtins(t_main *main, t_shell *shell)
{
	int	res;

	if (!strcmp("echo", main->cmd[0]))
		res = ft_echo(main->cmd);
	else if (!strcmp("cd", main->cmd[0]))
		res = ft_cd(main->cmd, shell);
	else if (!strcmp("pwd", main->cmd[0]))
		res = ft_pwd(shell);
	else if (!strcmp("unset", main->cmd[0]))
		res = ft_unset(&shell->env, main->cmd);
	else if (!strcmp("env", main->cmd[0]))
		res = ft_env(main->cmd, shell->env);
	else if (!strcmp("export", main->cmd[0]))
		res = ft_export(&shell->env, main->cmd);
	else if (!strcmp("exit", main->cmd[0]))
		res = ft_exit(main->cmd, shell);
	return (res);
}

int	handle_dup(int stdin_cpy, int stdout_cpy)
{
	int	status;

	status = 0;
	if (dup2(stdin_cpy, STDIN_FILENO) == -1)
	{
		perror("minishell: dup");
		status = 1;
	}
	if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup");
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

	if (!main->redir)
		return (run_builtins(main, shell));
	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	if (stdin_cpy == -1 || stdout_cpy == -1)
	{
		perror("minishell: dup");
		if (stdin_cpy != -1)
			close (stdin_cpy);
		if (stdout_cpy != -1)
			close (stdout_cpy);
		return (1);
	}
	if (handle_redir(main))
		return (handle_dup(stdin_cpy, stdout_cpy), 1);
	if (main->cmd[0])
		status = run_builtins(main, shell);
	if (handle_dup(stdin_cpy, stdout_cpy))
		status = 1;
	return (status);
}

int	run_single_external(t_main *main, t_shell *shell)
{
	char	*path;
	char	**new_env;

	if (main->redir && handle_redir(main))
		exit(1);
	path = command_founder(main->cmd, shell->env);
	new_env = env_convertor(shell->env);
	execve(path, main->cmd, new_env);
	// if(errno != ENOEXEC)//NOTE: any error except the execformat show it
	perror("minishell: execve");
	exit(1);
}

int	run_single_cmd(t_main *main, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (handle_redir_heredoc(main, shell->env))
		return (heredoc_cleanup(main), 1);
	if (main->is_builtin || (!main->cmd[0] && main->redir))
	{
		status = handle_builtins(main, shell);
		return (heredoc_cleanup(main), status);
	}
	signal_part(main);
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), heredoc_cleanup(main), 1);
	if (pid == 0)
		run_single_external(main, shell);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (heredoc_cleanup(main), status);
}
