/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multi_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:41:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/23 11:02:14 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	cleanup_exit_process(int *pipe_fd, int prev_fd, int pipe_created, int i)
{
	if (prev_fd > -1 && prev_fd != STDIN_FILENO)
		close (prev_fd);
	if (pipe_created)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	perror("minishell: dup2");
	if (i)
		exit(1);
}

void	run_multi_cmd(t_main *main, t_shell *shell)
{
	t_pipex	pipex;
	int  i= 0;
	int status;
	t_main *current = main;
	int	diff;
	char *path;
	char **new_env;

pipex.prev_fd = STDIN_FILENO;
pipex.nb_cmd = 0;
while (current)
{
	pipex.nb_cmd++;
	current = current->next;
}
current = main;
while (i < pipex.nb_cmd)
{
	diff = i < pipex.nb_cmd - 1;
	if (diff)
	{
		if (pipe(pipex.pipe_fd) < 0)
		{
			cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, 0, 0);
			shell->last_status = 1;
			return ;
		}
	}
	pipex.pid = fork();
	if (pipex.pid < 0)
	{
		cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 0);
		shell->last_status = 1;
		return ;
	}
	if (pipex.pid == 0)
	{
		if (i > 0)
		{
			if (dup2(pipex.prev_fd, STDIN_FILENO) < 0)
				cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 1);
			close(pipex.prev_fd);
		}
		if (diff)
		{
			if (dup2(pipex.pipe_fd[1], STDOUT_FILENO) < 0)
				cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 1);
			close(pipex.pipe_fd[0]);
			close(pipex.pipe_fd[1]);

		}
		if (handle_redir(current))
			cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 1);
		if (!current->is_builtin)
		{
			path = command_founder(shell->env, current->cmd);
			new_env=env_convertor(shell->env);
			execve(path, current->cmd, new_env);
		error("minishell: ", current->cmd[0], " : ", strerror(errno));
		exit(126);
		}
		else
		{
			if (run_builtins(current, shell))
				exit(1);
			exit(0);
		}
	}
	else
	{
		if (pipex.prev_fd != STDIN_FILENO)
			close (pipex.prev_fd);
		if (diff)
		{
			close (pipex.pipe_fd[1]);
			pipex.prev_fd = pipex.pipe_fd[0];
		}
		if (i == pipex.nb_cmd - 1)
			pipex.last_pid = pipex.pid;
		current = current->next;
		i++;
	}
}
i = 0;
while (i < pipex.nb_cmd)
{
	int wpid = wait(&status);
	if (wpid == pipex.last_pid && WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	i++;
}
}
