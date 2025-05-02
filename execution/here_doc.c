/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:48:10 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/27 16:58:01 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	handle_redir_heredoc(t_main *main, t_env *env)
{
	int		fd;
	t_file	*current;

	while (main)
	{
		current = main->redir;
		while (current)
		{
			if (current->token == 5)
			{
				fd = heredoc_inputfd(current, env);
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

int	fill_tempfile(int input_fd, char *limiter, t_file *current, t_env *env)
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
		if (current->expand && line[0] == '$')
		{
			new_line = ft_strjoin(get_env_value(env, line + 1), "\0");
			new_line = ft_strjoin(new_line, "\n");
		}
		else
			new_line = ft_strjoin(line, "\n");
		free(line);
		if (write(input_fd, new_line, env_strlen(new_line, '\0')) < 0)
			return (perror("minishell: write"), -1);
	}
	return (close(input_fd), 1);
}

int	heredoc_inputfd(t_file *current, t_env *env)
{
	int		input_fd;
	char	*limiter;

	limiter = current->file;
	unlink("temp.txt");
	input_fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (input_fd < 0)
	{
		error("minishell: temp.txt: ", strerror(errno), 0, 0);
		perror("minishell: open");
		return (-1);
	}
	if (fill_tempfile(input_fd, limiter, current, env) == -1)
		return (-1);
	input_fd = open("temp.txt", O_RDONLY);
	if (input_fd < 0)
	{
		error("minishell: temp.txt: ", strerror(errno), 0, 0);
		return (-1);
	}
	unlink("temp.txt");
	return (input_fd);
}
