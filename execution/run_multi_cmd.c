/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multi_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:41:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/26 16:13:51 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	cleanup_exit_process(int *pipe_fd, int prev_fd, int is_pipe, int code)
{
	if (prev_fd > -1 && prev_fd != STDIN_FILENO)
		close (prev_fd);
	if (is_pipe)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	if (code)
		exit(1);
}

void	pipex_cleanup(t_pipex *pipex, int is_pipe, int code, char *message)
{
	while (wait(NULL) > 0)
		;
	cleanup_exit_process(pipex->pipe_fd, pipex->prev_fd, is_pipe, code);
	perror(message);
}

int	pipex_logique(t_pipex *pipex, t_main *main, t_shell *shell, int i)
{
	t_main	*current;

	current = main;
	while (i < pipex->nb_cmd)
	{
		pipex->diff = i < pipex->nb_cmd - 1;
		if (pipex->diff)
		{
			if (pipe(pipex->pipe_fd) < 0)
				return (heredoc_cleanup(main),
					pipex_cleanup(pipex, 0, 0, "minishell: pipe"), 1);
		}
		signal(SIGINT, cntrlc_child);
		signal(SIGQUIT, cntrlslash);
		pipex->pid = fork();
		if (pipex->pid < 0)
			return (heredoc_cleanup(main),
				pipex_cleanup(pipex, pipex->diff, 0, "minishell: fork"), 1);
		if (pipex->pid == 0)
			childs_process(pipex, current, shell, i);
		else
			parent_process(pipex, &current, i);
		i++;
	}
	return (parent_exit(pipex, main));
}

int	run_multi_cmd(t_main *main, t_shell *shell)
{
	t_pipex	pipex;
	t_main	*current;
	int		status;

	current = main;
	status = handle_redir_heredoc(main, shell);//NOTE: prototype changed
	if (status)
		return (heredoc_cleanup(main), status);
	pipex.prev_fd = STDIN_FILENO;
	pipex.nb_cmd = 0;
	while (current)
	{
		pipex.nb_cmd++;
		current = current->next;
	}
	return (pipex_logique(&pipex, main, shell, 0));
}
