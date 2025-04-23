/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:14:45 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/22 13:28:24 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"


int	handle_redir_heredoc(t_main *main)
{
	int		fd;
	t_file	*current;

	current = main->redir;
	while (current)
	{
		if (current->token == 5)
		{
			fd = heredoc_inputfd(current->file);
			if (fd < 0)
				return (1);
			current->here_doc = fd;
		}
		current = current->next;
	}
	return (0);
}

void	heredoc_cleanup(t_file *redir)
{
	t_file	*current;

	current = redir;
	while (current)
	{
		if (current->token == 5 && current->here_doc > -1)
		{
			close (current->here_doc);
			current->here_doc = -1;
		}
		current = current->next;
	}
}

int	handle_redir(t_main *main)
{
	int		fd;
	t_file	*current;

	current = main->redir;
	if (handle_redir_heredoc(main))
	{
		heredoc_cleanup(main->redir);
		return (1);
	}
	while (current)
	{
		if (current->token == 2)
		{
			fd = open(current->file, O_RDONLY);
			if (fd < 0)
			{
				error("minishell: ", current->file, ": ", strerror(errno));
				return (1);
			}
			if (dup2(fd, 0) == -1)
			{
				perror("minishell: dup2");
				close (fd);
				return (1);
			}
			close (fd);
		}
		else if (current->token == 5)
		{
			if (dup2(current->here_doc, 0) == -1)
			{
				perror("minishell: dup2");
				close (current->here_doc);
				heredoc_cleanup(current);
				return (1);
			}
			close (current->here_doc);
		}
		else if (current->token == 3)
		{
			fd = open (current->file, O_CREAT | O_WRONLY | O_TRUNC , 0644);
			if (fd < 0)
			{
				error("minishell: ", current->file, ": ", strerror(errno));
				return (1);
			}
			if (dup2(fd, 1) == -1)
			{
				perror("minishell: dup2");
				close (fd);
				return (1);
			}
			close (fd);
		}
		else if (current->token == 4)
		{
			fd = open(current->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				error("minishell: ", current->file, ": ", strerror(errno));
				return (1);
			}
			if (dup2(fd, 1) == -1)
			{
				perror("minishell: dup2");
				close(fd);
				return (1);
			}
			close (fd);
		}
		current = current->next;
	}
	return (0);
}
