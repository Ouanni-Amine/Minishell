/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:48:10 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/30 11:25:14 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	handle_redir_heredoc(t_main *main, t_shell *shell)
{
	int		fd;
	t_file	*current;

	if (!here_doc_count(main))
	{
		ft_putstr_fd("Minishell: maximum here-document count exceeded\n", 2);
		my_exit(2);
	}
	while (main)
	{
		current = main->redir;
		while (current)
		{
			if (current->token == 5)
			{
				fd = heredoc_inputfd(current, shell);
				if (fd < 0)
					return (1);
				current->here_doc = fd;
			}
			current = current->next;
		}
		main = main->next;
	}
	return (0);
}

void	heredoc_cleanup(t_main *main)
{
	t_file	*current;

	while (main)
	{
		current = main->redir;
		while (current)
		{
			if (current->token == 5 && current->here_doc > -1)
			{
				close (current->here_doc);
				current->here_doc = -1;
			}
			current = current->next;
		}
		main = main->next;
	}
}

int	fill_tempfile(int input_fd, char *limiter, int expand, t_shell *shell)
{
	char	*line;
	char	*new_line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (expand)
			new_line = ft_strjoin(ft_add_val_in(line, shell->env, shell),
					"\n");
		else
			new_line = ft_strjoin(line, "\n");
		free(line);
		if (write(input_fd, new_line, env_strlen(new_line, '\0')) < 0)
			return (perror("minishell: write"), -1);
	}
	return (1);
}

int	prepare_heredoc_files(int fd[2])
{
	int		count;
	char	*res;

	count = 0;
	while (1)
	{
		res = ft_itoa(count);
		res = ft_strjoin("/tmp/heredoc_", res);
		if (access(res, F_OK))
			break ;
		count++;
	}
	fd[0] = open(res, O_CREAT | O_WRONLY, 0644);
	if (fd[0] < 0)
		return (-1);
	fd[1] = open(res, O_RDONLY);
	if (fd[1] < 0)
		return (close(fd[0]), -1);
	if (unlink(res) == -1)
		return (close(fd[0]), close(fd[1]), perror("minishell: unlink"), -1);
	return (1);
}

int	heredoc_inputfd(t_file *current, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (prepare_heredoc_files(fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(fd[0]), close(fd[1]), perror("minishell: fork"), -1);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_cntrlc);
		if (fill_tempfile(fd[0], current->file, current->expand, shell) == -1)
			exit(1);
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(fd[0]);
	signal(SIGINT, cntrlc);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		return (close(fd[1]), -1);
	return (fd[1]);
}
