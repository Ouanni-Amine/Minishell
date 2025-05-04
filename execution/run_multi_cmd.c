/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multi_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:41:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/03 13:45:41 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	cleanup_exit_process(int *pipe_fd, int prev_fd, int pipe_created, int i)
{
	if (prev_fd > -1 && prev_fd != STDIN_FILENO)
		close (prev_fd);
	if (pipe_created)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	if (i)
		exit(1);
}

int	run_multi_cmd(t_main *main, t_shell *shell)
{
	t_pipex	pipex;
	int  i= 0;
	int status;
	t_main *current = main;
	int	diff;
	char *path;
	char **new_env;
	int last_status;

if (handle_redir_heredoc(main, shell->env))
	return (heredoc_cleanup(main), 1);//TODO: fork for the here_docs to handle the signal problem
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
			while (wait(NULL) > 0)
			;
			cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, 0, 0);
			return (perror("minishell: pipe"), heredoc_cleanup(main), 1);
		}
	}
	signal(SIGINT, cntrlC_child);
	signal(SIGQUIT, cntrlslash);
	pipex.pid = fork();
	if (pipex.pid < 0)
	{
		while (wait(NULL) > 0)
			;
		cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 0);
		return (perror("minishell: fork"), heredoc_cleanup(main), 1);
	}
	if (pipex.pid == 0)
	{
		if (i > 0)
		{
			if (dup2(pipex.prev_fd, STDIN_FILENO) < 0)
			{
				perror("minishell: dup2");
				cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 1);
			}
			close(pipex.prev_fd);
		}
		if (diff)
		{
			if (dup2(pipex.pipe_fd[1], STDOUT_FILENO) < 0)
			{
				perror("minishell: dup2");
				cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 1);
			}
			close(pipex.pipe_fd[0]);
			close(pipex.pipe_fd[1]);

		}
		if (handle_redir(current))
			cleanup_exit_process(pipex.pipe_fd, pipex.prev_fd, diff, 1);
		if (!current->is_builtin && current->cmd[0])
		{
			path = command_founder(current->cmd, shell->env);
			new_env=env_convertor(shell->env);
			execve(path, current->cmd, new_env);
			perror("minishell: execve");
			exit(1);
		}
		else if (current->is_builtin && current->cmd[0])
		{
			status = run_builtins(current, shell);
				exit(status);
		}
		puts("after builtin");
	exit(0);
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
	if (wpid == pipex.last_pid)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
	}
	i++;
}
return (heredoc_cleanup(main), last_status);
}
