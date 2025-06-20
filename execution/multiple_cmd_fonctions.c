/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd_fonctions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:47:59 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/17 16:37:26 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	dup_input(t_pipex *pipex)
{
	if (dup2(pipex->prev_fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		cleanup_exit_process(pipex->pipe_fd, pipex->prev_fd, pipex->diff, 1);
	}
	close(pipex->prev_fd);
}

void	dup_output(t_pipex *pipex)
{
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2");
		cleanup_exit_process(pipex->pipe_fd, pipex->prev_fd, pipex->diff, 1);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

void	childs_process(t_pipex *pipex, t_main *main, t_shell *shell, int i)
{
	char	*path;
	char	**new_env;
	int		status;

	change_handler(1);
	if (i > 0)
		dup_input(pipex);
	if (pipex->diff)
		dup_output(pipex);
	if (handle_redir(main))
		cleanup_exit_process(pipex->pipe_fd, pipex->prev_fd, pipex->diff, 1);
	if (!main->is_builtin && main->cmd[0])
	{
		path = command_founder(main->cmd, shell->env);
		new_env = env_convertor(shell->env);
		execve(path, main->cmd, new_env);
		perror("minishell: execve");
		my_exit(1);
	}
	else if (main->is_builtin && main->cmd[0])
	{
		status = run_builtins(main, shell);
		my_exit(status);
	}
	my_exit(0);
}

void	parent_process(t_pipex *pipex, t_main **main, int i)
{
	if (pipex->prev_fd != STDIN_FILENO)
		close (pipex->prev_fd);
	if (pipex->diff)
	{
		close (pipex->pipe_fd[1]);
		pipex->prev_fd = pipex->pipe_fd[0];
	}
	if (i == pipex->nb_cmd - 1)
		pipex->last_pid = pipex->pid[i];
	*main = (*main)->next;
}

int	parent_exit(t_pipex *pipex, t_main *main)
{
	int	i;
	int	status;
	int	last_status;
	int	wpid;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		wpid = wait(&status);
		check_exit(status);
		if (wpid == pipex->last_pid)
			last_status = check_exit(status);
		i++;
	}
	check_signal(last_status);
	return (heredoc_cleanup(main), last_status);
}
